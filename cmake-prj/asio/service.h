#ifndef __SERVICE_H__
#define __SERVICE_H__
#include <boost/asio.hpp>
#include <thread>
#include <atomic>
#include <memory>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace boost;
class Service
{
public: 
    Service(std::shared_ptr<asio::ip::tcp::socket> t_sock): m_sock(t_sock)
    {}

    void StartHandling()
    {
        asio::async_read_until(
            *m_sock.get(),
            m_request, 
            '\n', 
            [this] (const boost::system::error_code& ec,
                std::size_t bytes_transferred)
            {
                std::cout << "start handling request" << std::endl;
                onRequestReceived(ec, bytes_transferred);
            });
    }

private:
    void onRequestReceived(
        const boost::system::error_code& t_ec, 
        std::size_t bytes_transferred)
    {
        if (t_ec)
        {
            std::cout << "Error occured! Error code= "
                      << t_ec.value()
                      << ". Message: " << t_ec.message();
            
            onFinish();
            return;
        }

        m_response = ProcessRequest(m_request);
        boost::asio::streambuf::const_buffers_type cbt = m_request.data();        
        std::string s(boost::asio::buffers_begin(cbt), boost::asio::buffers_end(cbt));
        std::cout << "received: " << s << std::endl;
        asio::async_write(
            *m_sock.get(), 
            asio::buffer(m_response), 
            [this] (const boost::system::error_code& ec,
                std::size_t bytes_transferred)
                {
                    onResponseSent(ec, bytes_transferred);
                });
    }
    
    void onResponseSent(
        const boost::system::error_code& t_ec, size_t bytes_transferred)
    {
        if (t_ec)
        {
            std::cout << "Error occured! Error code = " << t_ec.value() 
                      << ". Message: " << t_ec.message();
        }

        onFinish();
    }
    

    void onFinish()
    {
        delete this;
    }

    std::string ProcessRequest(asio::streambuf& request)
    {
        int i = 0;
        while( i != 10000)
        {
            i++;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::string response = "Response\n";

        return response;
    }

private:
    std::shared_ptr<asio::ip::tcp::socket> m_sock;
    std::string m_response;
    asio::streambuf  m_request;
};

#endif //__SERVICE_H__