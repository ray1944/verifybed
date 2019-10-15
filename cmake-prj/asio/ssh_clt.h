#ifndef __SSH_CLT_H__
#define __SSH_CLT_H__

#include <libssh2.h>
#include <memory>
#include <boost/asio.hpp>
#include <boost/filesystem.hpp>
#include <string>

class CSshClient;
typedef std::shared_ptr<CSshClient> CSshClientPtr;

class CSshException : public std::runtime_error
{
public:
    CSshException() : runtime_error("") {}

    virtual ~CSshException() throw() {}

    virtual const char *what() const throw()
    {
        return _msg.c_str();
    }

protected:
    std::string _msg;
};

class CSshInitException : public CSshException
{
public:
    CSshInitException()
    {
        std::stringstream ss;

        ss << "Libssh2 init failed";
        _msg = ss.str();
    }
};

class CSshCltInitException: public CSshException
{
public:
    CSshCltInitException()
    {
        std::stringstream ss;

        ss << "Ssh client init failed";
        _msg = ss.str();
    }
};

class CSshCltCfgDirNonExist: public CSshException
{
public:
    CSshCltCfgDirNonExist(const std::string& t_sshdir)
    {
        std::stringstream ss;

        ss << "SSH dir not existed(" << t_sshdir << ")";
        _msg = ss.str(); 
    }
};

class CSshCltCfgDirNotAbs: public CSshException
{
public:
    CSshCltCfgDirNotAbs(const std::string& t_sshdir)
    {
        std::stringstream ss;

        ss << "SSH dir is not absolute path(" << t_sshdir << ")";
        _msg = ss.str();
    }
};

class CSshCltResolvFailed: public CSshException
{
public:
    CSshCltResolvFailed(
        const std::string& t_host, 
        boost::system::error_code& ec)
    {
        std::stringstream ss;

        ss << "Can not resolve host(" << t_host << "\n"
           << "Error: " << ec.message();
        _msg = ss.str();
    }
};

// class CSshCltSessionInit: public CSshException
// {
// public:
//     CSshCltSessionInit()
// }

/*
 * CSshClient is a class to execute shell
 * command on remote IBMi host and copy/write 
 * some specific files to or from peer
 * */
class CSshClient
{
public:
    // instance factory method
    static CSshClientPtr create(
        boost::asio::io_service& t_ios,
        const boost::filesystem::path& t_ssh_dir,
        const std::string& t_user,
        const std::string& t_host,
        const std::string& t_port = "22");

    //ctor.
    CSshClient(
        boost::asio::io_service &t_ios,
        const boost::filesystem::path &t_ssh_dir,
        const std::string &t_user,
        const std::string &t_host,
        const std::string &t_port);

    // forbiden copy ctor. and assignment
    CSshClient(const CSshClient& t_oths) = delete;
    CSshClient& operator=(const CSshClient& t_oths) = delete;

    //asynchronized connect to endpoint, if timeout
    void async_connect(
        const boost::asio::deadline_timer::duration_type& t_timeout);

    bool is_connected() const;

    void disconnect();

// private methods
private:
    // try to connect to destination endpoint
    void try_connect(const boost::system::error_code& t_ec);

    void handle_connect(const boost::system::error_code& t_ec);

    void on_timeout(const boost::system::error_code& t_ec);

    void reset();

    void try_ssh_handshake(const boost::system::error_code& t_ec);

    void try_authenticate(const boost::system::error_code& t_ec);

    void try_userauth_password(const boost::system::error_code& t_ec);

    void try_create_channel(const boost::system::error_code& t_ec);

    template <typename Handler>
    void waitsocket(Handler handler);

    void try_create_shell(const boost::system::error_code& t_ec);

    std::string getpass(const std::string& prompt);

    // private members
private: 
    boost::filesystem::path _ssh_dir; // user homd ssh config directory
    std::string _user;   // user name
    std::string _host;   // destination host name/IP
    std::string _port;   // dest port
    std::string _passwd; // user input password
    boost::asio::deadline_timer::duration_type _req_timeout;

    boost::asio::ip::tcp::socket _socket;       // client socket
    boost::asio::deadline_timer _timeout_timer; // timeout timer
    boost::asio::deadline_timer _retry_timer;
    int _retry_count;    // retry counter
    std::string _buffer; // internal write and receive buffer
    
    std::shared_ptr<LIBSSH2_SESSION> _ssh_session; // libssh2 session
    std::shared_ptr<LIBSSH2_CHANNEL> _ssh_channel; // libssh2 channel
};

#endif // __SSH_CLT_H__