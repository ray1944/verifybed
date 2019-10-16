#include "ssh_clt.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind.hpp>
#include <curses.h>
// #include <cstring>

namespace fs = boost::filesystem;
namespace ptm = boost::posix_time;
namespace asio = boost::asio;
namespace sys = boost::system;
using namespace std;

//static
CSshClientPtr CSshClient::create(
    boost::asio::io_service& t_ios,
    const boost::filesystem::path& t_ssh_dir,
    const std::string& t_user,
    const std::string& t_host,
    const std::string& t_port)
{
    return CSshClientPtr(
        new CSshClient(t_ios, t_ssh_dir, t_user, t_host, t_port));
}

//ctor.
CSshClient::CSshClient(
    boost::asio::io_service &t_ios,
    const fs::path &t_ssh_dir,
    const std::string &t_user,
    const std::string &t_host,
    const std::string &t_port)
        : CSshCltBase(t_ios, t_ssh_dir, t_user, t_host, t_port),
        _shell_channel_config(false)
{}

void CSshClient::on_timeout(const boost::system::error_code &t_ec)
{
    if (!t_ec)
    {
        cout << "global timeout timer is out" << endl;
        reset();
    }
    else
    {
        cout << "timeout timer cancelled" << endl;
    }
}

void CSshClient::try_send_command(const sys::error_code& t_ec)
{
    if (!t_ec)
    {
        // libssh2_trace(_ssh_session.get(), ~0);
        // cout << "exec command: " << _buffer << endl;
        int rc = libssh2_channel_exec(_ssh_channel.get(), _out_buffer.c_str());
        // cout << rc << endl;
        if (rc == LIBSSH2_ERROR_EAGAIN)
        {
            waitsocket(boost::bind(&CSshClient::try_send_command, this, _1));
        }
        else if (!rc)
        {
            cout << "command sent to peer and wait for reply" << endl;
            try_read_reply(sys::error_code());
        }
        else
        {
            cout << "failed to exec, reset" << endl;
            reset();
            _timeout_timer.cancel();
        }
    }
    else
    {
        cout << t_ec.message() << endl;
    }
}

void CSshClient::try_create_channel(const boost::system::error_code &t_ec)
{
    if (!t_ec)
    {
        cout << "open channel" << endl;
        _ssh_channel.reset(
            libssh2_channel_open_session(_ssh_session.get()),
            libssh2_channel_free);
        if (!_ssh_channel)
        {
            int rc = libssh2_session_last_error(_ssh_session.get(), 0, 0, 0);
            if (rc == LIBSSH2_ERROR_EAGAIN)
            {
                cout << "conitnue open channel" << endl;
                waitsocket(boost::bind(&CSshClient::try_create_channel, this, _1));
            }
            else
            {
                
                cout << "last error rc: " << rc << endl;
                reset();
            }
        }
        else
        {
            cout << "SSH connection channel was open" << endl;
            try_send_command(sys::error_code());
        }
    }
    else
    {
        cout << "channel open failed " << t_ec.message() << endl;
    }
}

void CSshClient::try_read_reply(const boost::system::error_code& t_ec)
{
    if (!t_ec)
    {
        typedef std::array<char, 4096> buffer_type;
        buffer_type data;
        bool haserror = false;

        ssize_t len = libssh2_channel_read_stderr(
            _ssh_channel.get(), 
            data.data(), 
            data.size());
        if (len > 0)
        {
            haserror = true;
        }
        
        if (!haserror)
        {
            len = libssh2_channel_read(
            _ssh_channel.get(),
            data.data(),
            data.size());
        }
        bool eom = false;
        while(len >= 0 && !eom)
        {
            buffer_type::iterator data_begin = std::begin(data);
            buffer_type::iterator data_end = std::begin(data) + len;
            if (*(data_end - 1) == _reply_delimiter)
            {
                // cout << "eom to true" << endl;
                eom = true;
                --data_end;
            }
            _in_buffer.insert(std::end(_in_buffer), data_begin, data_end);
            // cout << _in_buffer << ": len : " << _in_buffer.size() << endl;
            // cout << "eof: " << libssh2_channel_eof(_ssh_channel.get()) << endl;            
            if (!eom)
            {
                if (haserror)
                {
                    len = libssh2_channel_read_stderr(
                        _ssh_channel.get(), 
                        data.data(), 
                        data.size());
                }
                else
                {
                    len = libssh2_channel_read(
                        _ssh_channel.get(), 
                        data.data(), 
                        data.size());
                }
            }
            // cout << "len: " << len << endl;
        }
        if (eom)
        {
            cout << "global timeout timer cancelled" << endl;
            cout << _in_buffer << ": len : " << _in_buffer.size() << endl;
            _timeout_timer.cancel();
            try_free_channel(sys::error_code());
        }
        else if (len == LIBSSH2_ERROR_EAGAIN)
        {
            waitsocket(boost::bind(&CSshClient::try_read_reply, this, _1));
        }
        else
        {
            reset();
        }
    }
}

void CSshClient::try_free_channel(const sys::error_code& t_ec)
{
    if (!t_ec)
    {
        cout << "try to free channel" << endl;
        int rc = libssh2_channel_close(_ssh_channel.get());

        if (rc == LIBSSH2_ERROR_EAGAIN)
        {
            waitsocket(boost::bind(&CSshClient::try_free_channel, this, _1));
        }
        else if (!rc)
        {
            _ssh_channel.reset();
            cout << "channel freed" << endl;
            // cout << _ssh_channel.get() << endl;
        }
        else
        {
            cout << "rc: " << rc << endl;
            reset();
        }
    }
}

template <typename Handler>
void CSshClient::waitsocket(Handler handler)
{
    int direction = libssh2_session_block_directions(_ssh_session.get());

    if (direction & LIBSSH2_SESSION_BLOCK_INBOUND)
    {
        // cout << "inbound" << endl;
        _socket.async_read_some(asio::null_buffers(), handler);
    }
    if (direction & LIBSSH2_SESSION_BLOCK_OUTBOUND)
    {
        // cout << "outbound" << endl;
        _socket.async_write_some(asio::null_buffers(), handler);
    }
}

void CSshClient::async_exec(
    const CCmd& t_cmd,
    const asio::deadline_timer::duration_type& t_timeout)
{
    _timeout_timer.cancel();
    _timeout_timer.expires_from_now(t_timeout);
    _out_buffer = t_cmd.str();
    // _buffer_curr = std::begin(_buffer);
    _reply_delimiter = t_cmd.reply_delimiter();

    try_create_channel(sys::error_code());
    _timeout_timer.async_wait(boost::bind(&CSshClient::on_timeout, this, _1));
}

void CSshClient::reset()
{
    CSshCltBase::reset();
    _in_buffer.clear();
    _out_buffer.clear();
}