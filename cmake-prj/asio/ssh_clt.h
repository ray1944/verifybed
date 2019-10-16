#ifndef __SSH_CLT_H__
#define __SSH_CLT_H__
#include "ssh_clt_base.h"

#include <libssh2.h>
#include <memory>
#include <boost/asio.hpp>
#include <boost/filesystem.hpp>
#include <string>

class CSshClient;
typedef std::shared_ptr<CSshClient> CSshClientPtr;

/*
 * CSshClient is a class to execute shell
 * command on remote IBMi host and copy/write 
 * some specific files to or from peer
 * */
class CSshClient: public CSshCltBase
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

    // void async_create_shell(
    //     const boost::asio::deadline_timer::duration_type& t_timeout);
 
    /*
     * async execute command on endpoint
     * returns command output 
     * */
    void async_exec(
        const CCmd& t_cmd,
        const boost::asio::deadline_timer::duration_type& t_timeout);
    
    void try_free_channel(const boost::system::error_code& t_ec);

    std::string GetLastResult()
    {
        std::string ret = _in_buffer;
        _in_buffer.clear();

        return ret;
    }

private:
    //try to create exec channel
    void try_create_shell(const boost::system::error_code& t_ec);

    void try_send_command(const boost::system::error_code& t_ec);

    void try_read_reply(const boost::system::error_code& t_ec);

    void try_create_channel(const boost::system::error_code& t_ec);

    void on_timeout(const boost::system::error_code &t_ec);

    template <typename Handler>
    void waitsocket(Handler handler);

    int wsocket(int socket, LIBSSH2_SESSION* session);

    void reset();

private:
    std::string _in_buffer;  // internal receive buffer
    std::string _out_buffer; // internal write buffer
    std::string::iterator _buffer_curr; // buffer pointer
    bool _shell_channel_config; // shell channel configured
    char _reply_delimiter;      // peer reply end of delimiter
};

#endif // __SSH_CLT_H__