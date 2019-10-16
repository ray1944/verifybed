#include <libssh2.h>
#include <boost/asio.hpp>
#include <boost/filesystem.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "ssh_clt.h"

namespace asio = boost::asio;
namespace fs = boost::filesystem;
namespace ptm = boost::posix_time;
using namespace std;

void test_connect()
{
   asio::io_service ios;
   fs::path ssh_dir = "/Users/ray1944/.ssh";
   CSshClientPtr sshcltptr(
      CSshClient::create(ios, ssh_dir, "pcheng", "aldev73a"));
   asio::deadline_timer::duration_type connect_timeout = ptm::seconds(30);

   sshcltptr->async_connect(connect_timeout);
   ios.reset();
   ios.run();

   if (sshcltptr->is_connected())
   {
      cout << "ssh client is connected to aldev73a" << endl;
   }
   sshcltptr->disconnect();
   if (!sshcltptr->is_connected())
   {
      cout << "ssh connection is closed" << endl;
   }

   sshcltptr = CSshClient::create(ios, ssh_dir, "pin", "aldev73a");
   sshcltptr->async_connect(connect_timeout);
   ios.reset();
   ios.run();
   if (sshcltptr->is_connected())
   {
      cout << "ssh client is connected to aldev73a" << endl;
   }
   sshcltptr->disconnect();
   if (!sshcltptr->is_connected())
   {
      cout << "ssh connection is closed" << endl;
   }
}

void test_cltsshshell()
{
   asio::io_service ios;
   fs::path ssh_dir = "/Users/ray1944/.ssh";
   CSshClientPtr sshcltptr(
      CSshClient::create(ios, ssh_dir, "pcheng", "aldev73a"));
   asio::deadline_timer::duration_type connect_timeout = ptm::seconds(30);

   sshcltptr->async_connect(connect_timeout);
   ios.reset();
   ios.run();

   if (sshcltptr->is_connected())
   {
      cout << "ssh client is connected to aldev73a" << endl;
   }
   asio::deadline_timer::duration_type create_shell_timeout = ptm::seconds(30);
   sshcltptr->async_exec("uname", create_shell_timeout);
   ios.reset();
   ios.run();
   cout << sshcltptr->GetResult();
   sshcltptr->disconnect();
   if (!sshcltptr->is_connected())
   {
      cout << "ssh connection is closed" << endl;
   }
}

int main()
{
   test_cltsshshell();

   return 0;
}