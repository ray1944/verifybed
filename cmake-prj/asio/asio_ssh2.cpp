#include <libssh2.h>
#include <boost/asio.hpp>
#include <boost/filesystem.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "ssh_clt.h"

namespace asio = boost::asio;
namespace fs = boost::filesystem;
namespace ptm = boost::posix_time;
using namespace std;

int main()
{
   asio::io_service ios;
   fs::path ssh_dir = "/Users/ray1944/.ssh";
   CSshClientPtr sshcltptr(
      CSshClient::create(ios, ssh_dir, "pcheng", "aldev73a"));
   asio::deadline_timer::duration_type connect_timeout = ptm::seconds(10);

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

   return 0;
}