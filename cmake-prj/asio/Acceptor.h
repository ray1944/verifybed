#ifndef __ACCEPTOR_H__
#define __ACCEPTOR_H__
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "service.h"

using namespace boost;
class Acceptor
{
public:
    Acceptor(asio::io_service& t_ios, unsigned short t_port_num):
        m_ios(t_ios), m_acceptor(
                        m_ios, 
                        asio::ip::tcp::endpoint(
                            asio::ip::address_v4::any(), t_port_num)),
        m_isStopped(false)
    {}

    void Start()
    {
        m_acceptor.listen();
        InitAccept();
    }

    void Stop()
    {
        m_isStopped.store(true);
    }

private:
    void InitAccept()
    {
        std::shared_ptr<asio::ip::tcp::socket> sock(
            new asio::ip::tcp::socket(m_ios));
        m_acceptor.async_accept(
            *sock.get(), 
            [this, sock](const boost::system::error_code& error) {
                std::cout << "connection comming " 
                          << sock->remote_endpoint().address().to_string() << ":"
                          << sock->remote_endpoint().port()<< std::endl;
                onAccept(error, sock);
            });
        
    }

    void onAccept(
        const boost::system::error_code& t_ec, 
        std::shared_ptr<asio::ip::tcp::socket> t_sock)
    {
        if (!t_ec)
        {   
        //    std::shared_ptr<Service> sptr(new Service(t_sock));
        //    sptr->StartHandling();
            (new Service(t_sock))->StartHandling();
        }
        else
        {
            std::cout << "Error occured! Error code = "
                      << t_ec.value()
                      << ". Message: " << t_ec.message();
            
        }
        if (!m_isStopped.load())
        {
            InitAccept();
        }
        else
        {
            m_acceptor.close();
        }
    }

private:
    asio::io_service& m_ios;
    asio::ip::tcp::acceptor m_acceptor;
    std::atomic<bool> m_isStopped;
};

#endif