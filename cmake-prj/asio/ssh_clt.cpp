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
        : CSshCltBase(t_ios, t_ssh_dir, t_user, t_host, t_port)
{}
