#include <boost/asio.hpp>
#include <string>
#include <boost/bind.hpp>
#include <iostream>

using namespace std;
namespace asio = boost::asio;

size_t read_complete(char* buf, const boost::system::error_code& err, size_t bytes)
{
   if (err) return 0;
   bool found = std::find(buf, buf + bytes, '\n') < buf + bytes;
   return found ? 0: 1;
}

void sync_echo(string t_msg, asio::io_service& t_ios, const asio::ip::tcp::resolver::iterator t_epitr)
{
   t_msg += "\n";
   asio::ip::tcp::socket sock(t_ios);
   bool conn = false;
   for (auto epitr = t_epitr; epitr != asio::ip::tcp::resolver::iterator(); epitr++)
   {
      asio::ip::tcp::endpoint ep = *epitr;
      // cout << "IP: " << ep.address().to_string() << " ";
      // cout << "Port: " << ep.port() << endl;

      asio::ip::tcp::endpoint ep1(asio::ip::address::from_string("127.0.0.1"), 9001);

      boost::system::error_code ec;
      sock.connect(ep, ec);
      if (!ec)
      {
         conn = true;
         break;
      }
      else
      {
         cout << ec.message() << endl;
      }
      
   }
   if (!conn)
   {
      return;
   }
   sock.write_some(asio::buffer(t_msg));
   char buf[1024];
   int bytes = read(sock, asio::buffer(buf), boost::bind(read_complete, buf, _1, _2));
   string copy(buf, bytes - 1);
   t_msg = t_msg.substr(0, t_msg.size() - 1);
   cout << "server echoed our " << t_msg << ": " << (copy == t_msg ? "OK": "FAIL") << endl;
   sock.close();
}

int main()
{
   asio::io_service ios;
   asio::ip::tcp::resolver resolver(ios);
   asio::ip::tcp::resolver::iterator ep = 
      resolver.resolve("localhost", "9001");
   sync_echo("I am client", ios, ep);
}
