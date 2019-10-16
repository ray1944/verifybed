#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind.hpp>
#include <iostream>

using namespace std;
namespace asio = boost::asio;
namespace ptm = boost::posix_time;
//blocking wait on a timer
void block_timer()
{
    /*
     * All programs that use asio need to have at least one 
     * boost::asio::io_service object. This class provides 
     * access to I/O functionality. We declare an object of 
     * this type first thing in the main function.
     * */
    asio::io_service ios;

    asio::deadline_timer t(ios, ptm::seconds(3));
    /*
     * we perform a blocking wait on the timer. That is, the call to 
     * deadline_timer::wait() will not return until the timer has expired, 
     * 5 seconds after it was created (i.e. not from when the wait starts).
     * A deadline timer is always in one of two states: 
     * "expired" or "not expired". If the deadline_timer::wait() function 
     * is called on an expired timer, it will return immediately.
     * */
    cout << "blocking wait" << endl;
    t.wait();
    cout << "Hello, world" << endl;
}

void print(const boost::system::error_code& ec)
{
    std::cout << "hello, world!" << endl;
}

void async_wait()
{
    asio::io_service ios;
    asio::deadline_timer t(ios, ptm::seconds(3));

    t.async_wait(&print);
    /*
     * we must call the io_service::run() member function on the 
     * io_service object.
     * The asio library provides a guarantee that callback handlers
     * will only be called from threads that are currently calling 
     * io_service::run(). Therefore unless the io_service::run() function 
     * is called the callback for the asynchronous wait completion will 
     * never be invoked.
     * The io_service::run() function will also continue to run while 
     * there is still "work" to do. In this example, the work is the 
     * asynchronous wait on the timer, so the call will not return until 
     * the timer has expired and the callback has completed.
     * It is important to remember to give the io_service some work to 
     * do before calling io_service::run(). For example, if we had omitted 
     * the above call to deadline_timer::async_wait(), the io_service would 
     * not have had any work to do, and consequently io_service::run() 
     * would have returned immediately.
     * */
    cout << "async wait" << endl;
    ios.run();
}

void print2(
    const boost::system::error_code& ec, 
    asio::deadline_timer* t, 
    int* count)
{
    if (*count < 5)
    {
        cout << *count << endl;
        ++(*count);
        /*
         * we move the expiry time for the timer along by one second 
         * from the previous expiry time. By calculating the new expiry 
         * time relative to the old, we can ensure that the timer does 
         * not drift away from the whole-second mark due to any delays 
         * in processing the handler.
         * */
        t->expires_at(t->expires_at() + ptm::seconds(1));
        /*
         * By not starting a new asynchronous wait on the timer 
         * when count reaches 5, the io_service will run out of 
         * work and stop running.
         * */
        /*
         * Then we start a new asynchronous wait on the timer. 
         * As you can see, the boost::bind() function is used to 
         * associate the extra parameters with your callback handler. 
         * The deadline_timer::async_wait() function expects a handler 
         * function (or function object) with the signature 
         * void(const boost::system::error_code&). Binding the additional 
         * parameters converts your print function into a function object 
         * that matches the signature correctly.
         * 
         * In this example, the boost::asio::placeholders::error argument 
         * to boost::bind() is a named placeholder for the error object 
         * passed to the handler. When initiating the asynchronous operation, 
         * and if using boost::bind(), you must specify only the arguments 
         * that match the handler's parameter list.
         * */
        t->async_wait(boost::bind(print2, asio::placeholders::error, t, count));
    }
}

void repeating_timer()
{
    /*
     * To implement a repeating timer using asio you need to 
     * change the timer's expiry time in your callback function, 
     * and to then start a new asynchronous wait. 
     * Obviously this means that the callback function will 
     * need to be able to access the timer object. To this end 
     * we add two new parameters to the print function:
     *  - a pointer to a timer object.
     *  - a counter so that we can stop the program when the timer
     *    fires for the 6 times.
     * */
    asio::io_service ios;
    asio::deadline_timer t(ios, ptm::seconds(1));
    int count = 0;

    t.async_wait(boost::bind(print2, asio::placeholders::error, &t, &count));
    ios.run();
    cout << "Final count is " << count << endl;
}

class printer
{
public:
    printer(asio::io_service& ios):_timer(ios, ptm::seconds(1)), _count(0)
    {
        _timer.async_wait(boost::bind(&printer::print, this, _1));
    }

    ~printer()
    {
        cout << "Final count is " << _count << endl;
    }

    void print(const boost::system::error_code& ec)
    {
        if (!ec)
        {
            if (_count < 5)
            {
                if (_count == 3)
                {
                    cout << "timer cancel ... " << endl;
                    _timer.cancel();
                    return;
                }
                int level = _count;
                cout << _count << endl;
                ++_count;
                _timer.expires_at(_timer.expires_at() + ptm::seconds(1));
                _timer.async_wait(boost::bind(&printer::print, this, _1));
                cout << "call stack " << level << endl; 
            }
        }
        else
        {
            cout << "timer called" << endl;
        }        
    }

    

private:
    asio::deadline_timer _timer;
    int _count;
};

int main()
{
    // block_timer();
    // async_wait();
    // repeating_timer();
    asio::io_service ios;
    printer p(ios);
    ios.run();

    return 0;
}