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

void CSshClient::try_create_shell(const boost::system::error_code& t_ec)
{
    cout << "configure shell channel" << endl;
    if (!t_ec && _ssh_channel)
    {
        int rc = 0;
        if (!_shell_channel_config)
        {
            rc =libssh2_channel_shell(_ssh_channel.get());
        }

        if (!rc)
        {
            cout << "shell channel configured" << endl;
            _shell_channel_config = true;
            // _timeout_timer.cancel();
            _socket.async_write_some(
                asio::null_buffers(),
                boost::bind(&CSshClient::try_send_command, this, _1));
        }
        else if (rc == LIBSSH2_ERROR_EAGAIN)
        {
            waitsocket(boost::bind(&CSshClient::try_create_shell, this, _1));
        }
        else
        {
            reset();
        }
    }
}

void CSshClient::on_timeout(const boost::system::error_code &t_ec)
{
    CSshCltBase::on_timeout(t_ec);
}

void CSshClient::try_send_command(const sys::error_code& t_ec)
{
    if (!t_ec)
    {
        ssize_t nwritten = libssh2_channel_write(
            _ssh_channel.get(),
            &*_buffer_curr,
            std::distance(_buffer_curr, std::end(_buffer)));
        bool eom = false;
        while (nwritten >= 0 && !eom)
        {
            std::advance(_buffer_curr, nwritten);
            eom = (_buffer_curr == std::end(_buffer));
            if (!eom)
            {
                nwritten = libssh2_channel_write(
                    _ssh_channel.get(), 
                    &*_buffer_curr, 
                    std::distance(_buffer_curr, std::end(_buffer)));
            }
        }
        if (nwritten < 0 || !eom)
        {
            cout << "send data failed" << endl;

            return;
        }
        if (eom)
        {
            cout << "command(" << _buffer << ") sent to peer " << endl;
            _buffer.clear();
            _socket.async_receive(
                asio::null_buffers(),
                boost::bind(&CSshClient::try_read_reply, this, _1));
        }
        else if (nwritten == LIBSSH2_ERROR_EAGAIN)
        {
            waitsocket(boost::bind(&CSshClient::try_send_command, this, _1));
        }
        else
        {
            reset();
        }
    }
}

void CSshClient::try_read_reply(const boost::system::error_code& t_ec)
{
    if (!t_ec)
    {
        typedef std::array<char, 4096> buffer_type;
        buffer_type data;
        ssize_t len = libssh2_channel_read(
            _ssh_channel.get(),
            data.data(),
            data.size());
        bool eom = false;
        while(len >= 0 && !eom)
        {
            buffer_type::iterator data_begin = std::begin(data);
            buffer_type::iterator data_end = std::begin(data) + len;
            _buffer.insert(std::end(_buffer), data_begin, data_end);
            cout << _buffer << endl;
            cout << "eof: " << libssh2_channel_eof(_ssh_channel.get()) << endl;
            if (!eom)
            {
                len = libssh2_channel_read(
                    _ssh_channel.get(), 
                    data.data(), 
                    data.size());
            }
            cout << "len: " << len << endl;
        }
        if (eom)
        {
            _timeout_timer.cancel();
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
    else
    {
        cout << t_ec.message() << endl;
    }
}

template <typename Handler>
void CSshClient::waitsocket(Handler handler)
{
    int direction = libssh2_session_block_directions(_ssh_session.get());

    if (direction & LIBSSH2_SESSION_BLOCK_INBOUND)
    {
        _socket.async_read_some(asio::null_buffers(), handler);
    }
    if (direction & LIBSSH2_SESSION_BLOCK_OUTBOUND)
    {
        _socket.async_write_some(asio::null_buffers(), handler);
    }
}

void CSshClient::async_exec(
    const string& t_cmd,
    const boost::asio::deadline_timer::duration_type& t_timeout)
{
    _timeout_timer.cancel();
    _timeout_timer.expires_from_now(t_timeout);
    _buffer = t_cmd;
    _buffer_curr = std::begin(_buffer);

    try_create_shell(sys::error_code());
    _timeout_timer.async_wait(boost::bind(&CSshClient::on_timeout, this, _1));
}

void CSshClient::reset()
{
    CSshCltBase::reset();
    _buffer.clear();
}