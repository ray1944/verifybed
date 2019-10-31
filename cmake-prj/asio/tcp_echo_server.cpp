#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <string>
#include <iostream>

using namespace std;
namespace asio = boost::asio;

size_t read_complete(
    char* t_buff, 
    const boost::system::error_code& t_ec, 
    size_t t_bytes)
{
    if (t_ec) return 0;
    bool found = std::find(t_buff, t_buff + t_bytes, '\n') < t_buff + t_bytes;
    return found? 0: 1;
}

void handle_connections(asio::io_service& t_ios)
{
    asio::ip::tcp::acceptor acceptor(
        t_ios, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 8001));
    char buff[1024];

    while(true)
    {
        try
        {
            asio::ip::tcp::socket sock(t_ios);
            acceptor.accept(sock);
            int bytes = asio::read(sock, asio::buffer(buff), boost::bind(read_complete, buff, _1, _2));
            string msg(buff, bytes);
            cout << "got: " << msg << endl;
            sock.write_some(asio::buffer(msg));
            sock.close();
        }
        catch (boost::system::system_error& e)
        {
            cout << "got exception: " << e.what() << endl;
        }
    }
}

int main()
{
    asio::io_service ios;
    handle_connections(ios);
}
