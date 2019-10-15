#include <boost/filesystem.hpp>
#include <string>
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <iostream>
#include <stdint.h>


namespace fs = boost::filesystem;
namespace pt = boost::posix_time;
using namespace std;

void test_time()
{
    using namespace boost::posix_time;
    // using namespace boost::gregorian;
    ptime ptNow( second_clock::local_time() );
    std::cout << to_simple_string( ptNow ) << std::endl;
    // 转换成time_t
    tm tm1 = to_tm( ptNow );
    time_t tt = mktime( &tm1 );
    
    tm* tm2 = localtime( &tt );
    ptime ptt = pt::from_time_t( tt );
    ptime pttm = ptime_from_tm( *tm2 );
    std::cout << to_simple_string( ptt ) << std::endl << to_simple_string( pttm ) << std::endl;
}

int main(int argc, char* argv[])
{
    string path = "traveltree";
    if (fs::exists(path))
    {
        cout << path << " exists" << endl;
    }
    else 
    {
        cout << path << " not exists" << endl;
    }
    test_time();

    return 0;
}