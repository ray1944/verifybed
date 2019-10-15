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

struct Ssh2Init
{
    Ssh2Init()
    {
        int rc = libssh2_init(0);
        if (rc != 0)
        {
            throw CSshInitException();
        }
    }

    ~Ssh2Init()
    {
        libssh2_exit();
    }
};

//setup global static environment initialization and 
//cleanup variable for libssh2
static Ssh2Init gInit;

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
    const std::string &t_port) : _ssh_dir(t_ssh_dir), _user(t_user),
    _host(t_host), _port(t_port), _socket(t_ios), 
    _timeout_timer(t_ios), _retry_timer(t_ios), _retry_count(0)
{
    boost::system::error_code ec;
    fs::file_status st = fs::status(_ssh_dir, ec);

    if (!fs::exists(st))
    {
        throw CSshCltCfgDirNonExist(_ssh_dir.string());
    }
    if (!_ssh_dir.is_absolute())
    {
        throw CSshCltCfgDirNotAbs(_ssh_dir.string());
    }
}

void CSshClient::async_connect(
    const asio::deadline_timer::duration_type& t_timeout)
{
    try_connect(sys::error_code());
    _req_timeout = t_timeout;
    _timeout_timer.expires_from_now(_req_timeout);
    _timeout_timer.async_wait(boost::bind(&CSshClient::on_timeout, this, _1));
}

void CSshClient::try_connect(const sys::error_code& t_ec)
{
    if (!t_ec)
    {
        asio::ip::tcp::resolver resolver(_socket.get_executor());
        asio::ip::tcp::resolver::query query(_host, _port);
        sys::error_code ec;
        asio::ip::tcp::resolver::iterator itr = resolver.resolve(query, ec);
        
        if (ec)
        {
            throw CSshCltResolvFailed(_host, ec);
        }
        else
        {
            asio::ip::tcp::endpoint ep = *itr;
            cout << "connect to " << ep.address().to_string() << endl;
            asio::async_connect(
                _socket, 
                itr, 
                boost::bind(&CSshClient::handle_connect, this, _1));
        }
    }
}

void CSshClient::handle_connect(const sys::error_code& t_ec)
{
    if (t_ec)
    {
        cout << "connect with error " << endl;
        // re-try connect
        if (_retry_count < 8)
        {
            _retry_count++;
            _retry_timer.expires_at(
                _retry_timer.expires_at() + ptm::milliseconds(100));
            _retry_timer.async_wait(
                boost::bind(&CSshClient::try_connect, this, _1));
        }
        else 
        {
            cout << "Connect failed " << t_ec.message() << endl;
        }
    }
    else
    {
        // connected
        cout << "connected to the endpoint" << endl;
        _retry_count = 0;
        _ssh_session.reset(libssh2_session_init(), libssh2_session_free);
        // set session non-blocking
        libssh2_session_set_blocking(_ssh_session.get(), 0); 
        try_ssh_handshake(sys::error_code());
    }
}

void CSshClient::try_ssh_handshake(const sys::error_code &t_ec)
{
    if (!t_ec)
    {
        cout << "start to ssh handshake " << endl;
        int rc = libssh2_session_handshake(
            _ssh_session.get(), 
            _socket.native_handle());
        if (rc == LIBSSH2_ERROR_EAGAIN)
        {
            if (_retry_count < 10)
            {
                cout << "handshake continue receive again " << endl;
                _retry_count++;
                _retry_timer.expires_from_now(ptm::seconds(1));
                _retry_timer.async_wait(
                    boost::bind(&CSshClient::try_ssh_handshake, this, _1));
            }
            else
            {
                cout << "SSH handshake failed." << endl;
            }
        }
        else if (!rc)
        {
            // to next step
            cout << "handshake success" << endl;
            _retry_count = 0;
            try_authenticate(sys::error_code());
        }
        else 
        {
            reset();
        }
    }
}

void CSshClient::try_authenticate(const sys::error_code &t_ec)
{
    if (!t_ec)
    {
        cout << "start to authenticate " << endl;
        int rc = libssh2_userauth_publickey_fromfile(
            _ssh_session.get(), 
            _user.c_str(), 
            (_ssh_dir / "id_rsa.pub").c_str(),
            (_ssh_dir / "id_rsa").c_str(),
            0 /*no password*/);
        if (rc == LIBSSH2_ERROR_EAGAIN)
        {
            if (_retry_count < 10)
            {
                cout << "authenticate waiting for again " << endl;
                _retry_count++;
                _retry_timer.expires_at(
                    _retry_timer.expires_at() + ptm::seconds(1));
                _retry_timer.async_wait(
                    boost::bind(&CSshClient::try_authenticate, this, _1));
            }
            else
            {
                cout << "User authenticate failed." << endl;
            }
        }
        else if (!rc)
        {
            //try next step
            cout << "authenticate success " << endl;
            try_create_channel(sys::error_code());
        }
        else
        {
            _retry_count = 0;
            cout << "try authenticate with password " << endl; 
            try_userauth_password(sys::error_code());
        }
    }
}

void CSshClient::try_userauth_password(const sys::error_code& t_ec)
{
    if (!t_ec)
    {
        cout << "start to authenticate by password " << endl;
        if (_passwd.size() == 0)
        {
            getpass("Please input password: ");
        }
        int rc = libssh2_userauth_password(
            _ssh_session.get(), _user.c_str(), _passwd.c_str());
        if (rc == LIBSSH2_ERROR_EAGAIN)
        {
            if (_retry_count < 5)
            {
                cout << "authenticate with password retry " << endl; 
                try_userauth_password(sys::error_code());
                _retry_timer.expires_from_now(ptm::seconds(1));
                _retry_timer.async_wait(
                    boost::bind(&CSshClient::try_userauth_password, this, _1));
            }
            else
            {
                cout << "User password authentication failed." << endl;
                reset();
            }
        }
        else if (!rc)
        {
            cout << "start to create channel " << endl;
            try_create_channel(sys::error_code());
        }
        else 
        {
            cout << "authenticate failed " << endl;
            reset();
        }
    }
}

string CSshClient::getpass(const std::string &prompt)
{
    const char BACKSPACE = 8;
    const char RETURN = 0xd;
    unsigned char ch = 0;

    _timeout_timer.cancel();
    cout << prompt << endl;
    while ((ch = getch()) != RETURN)
    {
        if (ch == BACKSPACE)
        {
            if (_passwd.size() != 0)
            {
                _passwd.resize(_passwd.size() - 1);
            }
            else if (ch == 0 || ch == 224)
            {
                getch();
                continue;
            }
            else 
            {
                _passwd += ch;

            }
        }
    } // while
    cout << endl;
    // restart timeout timer
    _timeout_timer.expires_from_now(_req_timeout);
    _timeout_timer.async_wait(boost::bind(&CSshClient::on_timeout, this, _1));

    return _passwd;
}

void CSshClient::try_create_channel(const sys::error_code& t_ec)
{
    if (!t_ec)
    {
        cout << "create channel" << endl; 
        _ssh_channel.reset(
            libssh2_channel_open_session(_ssh_session.get()),
            libssh2_channel_free);
        if (_ssh_channel)
        {
            cout << "start to start shell channel" << endl;
            try_create_shell(sys::error_code());
        }
        else 
        {
            int rc = libssh2_session_last_error(_ssh_session.get(), 0, 0, 0);
            if (rc == LIBSSH2_ERROR_EAGAIN)
            {
                waitsocket(boost::bind(&CSshClient::try_create_channel, this, _1));
            }
            else
            {
                reset();
            }
        }
    }
}

void CSshClient::try_create_shell(const boost::system::error_code &t_ec)
{
    if (!t_ec)
    {
        int rc = libssh2_channel_shell(_ssh_channel.get());

        if (!rc)
        {
            cout << "ssh connected" << endl;
            _timeout_timer.cancel();
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

template<typename Handler>
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

void CSshClient::on_timeout(const sys::error_code &t_ec)
{
    if (!t_ec)
    {
        cout << "time out. reset all " << endl;
        reset();
    }
}

bool CSshClient::is_connected() const
{
    return _socket.is_open();
}

void CSshClient::reset()
{
    sys::error_code ec;
    _timeout_timer.cancel(ec);
    _retry_timer.cancel(ec);
    _socket.cancel(ec);
    _buffer.clear();
    _ssh_channel.reset();
    _ssh_session.reset();
    _socket.close();
    _retry_count = 0;
    _passwd.clear();
}

void CSshClient::disconnect()
{
    boost::system::error_code ec;
    _retry_timer.cancel(ec);
    _timeout_timer.cancel(ec);
    _socket.cancel(ec);
    _buffer.clear();
    if (_ssh_channel)
    {
        libssh2_channel_send_eof(_ssh_channel.get());
        libssh2_channel_close(_ssh_channel.get());
        _ssh_channel.reset();
    }
    if (_ssh_session)
    {
        libssh2_session_disconnect(_ssh_session.get(), "disconnect");
        _ssh_session.reset();
    }
    _socket.shutdown(asio::ip::tcp::socket::shutdown_both, ec);
    if (ec)
    {
        cout << ec.message() << endl;
    }
    _socket.close(ec);
}
