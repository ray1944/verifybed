#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

namespace asio = boost::asio;
using namespace std;

int main(int argc, char* argv[])
{   
    try 
    {
        if (argc != 2)
        {
            cerr << "Usage: client <host>" << endl;
            return 1;
        }

        asio::io_service ios;
        asio::ip::tcp::resolver resolver(ios);
        /*
         * We need to turn the server name that was specified as a 
         * parameter to the application, into a TCP endpoint. To do 
         * this we use an ip::tcp::resolver object.
         */
        asio::ip::tcp::resolver::iterator ep = 
            resolver.resolve(argv[1], "8080");
        for (auto epitr = ep; epitr != asio::ip::tcp::resolver::iterator(); epitr++)
        {
            asio::ip::tcp::endpoint endpoint = *epitr;
            cout << "IP: " << endpoint.address().to_string() << " ";
            cout << "Port: " << endpoint.port() << endl;
        }
        
        asio::ip::tcp::socket socket(ios);
        asio::connect(socket, ep);

        for (;;)
        {
            boost::array<char, 128> buf;
            boost::system::error_code error;
            size_t len = socket.read_some(asio::buffer(buf), error);

            if (error == boost::asio::error::eof)
            {
                break;
            }
            else
            {
                throw boost::system::system_error(error);
            }
            cout.write(buf.data(), len);
        }
    }
    catch (std::exception& e)
    {
        cerr << "got exception: ";
        cerr << e.what() << endl;
    }

    return 0;
}