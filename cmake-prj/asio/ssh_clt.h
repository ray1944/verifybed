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
};

#endif // __SSH_CLT_H__