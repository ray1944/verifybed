#ifndef __SERVER_H__
#define __SERVER_H__

#include "service.h"
#include "Acceptor.h"
class Server
{
public:
    Server()
    {
        m_work.reset(new asio::io_service::work(m_ios));
    }

    void Start(unsigned short port_num, unsigned int thread_pool_size)
    {
        acc.reset(new Acceptor(m_ios, port_num));
        acc->Start();

        for (unsigned int i = 0; i < thread_pool_size; i++)
        {
            std::unique_ptr<std::thread> th(
                new std::thread([this] () {
                    m_ios.run();
                }));
            m_thread_pool.push_back(std::move(th));
        }
    }

    void Stop()
    {
        acc->Stop();
        m_ios.stop();

        for (auto& th: m_thread_pool)
        {
            th->join();
        }
    }

private:
    asio::io_service m_ios;
    std::unique_ptr<asio::io_service::work> m_work;
    std::unique_ptr<Acceptor> acc;
    std::vector<std::unique_ptr<std::thread>> m_thread_pool;
};

#endif