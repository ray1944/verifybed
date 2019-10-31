#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>

using namespace std;
namespace asio = boost::asio;
namespace ptm = boost::posix_time;

int shared_i = 0;

void do_inc()
{
    asio::io_service ios;
    asio::deadline_timer timer1(ios);

    for(size_t i = 0; i < 700; ++i)
    {
        timer1.expires_from_now(ptm::milliseconds(1));
        timer1.wait();
        const int i_snapshot = ++shared_i;
        cout << "thread 1: " << i_snapshot << endl;
    }
}

void do_dec()
{
    asio::io_service ios;
    asio::deadline_timer timer1(ios);

    for (size_t i = 0; i < 700; ++i)
    {
        timer1.expires_from_now(ptm::milliseconds(1));
        timer1.wait();
        const int i_snapshot = --shared_i;
        cout << "thread 1: " << i_snapshot << endl;
    }
}

void run()
{
    boost::thread t1(boost::bind(do_inc));
    boost::thread t2(boost::bind(do_dec));
    t1.join();
    t2.join();

    cout << "shared_i == " << shared_i;
}

int main()
{
    run();

    return 0;
}