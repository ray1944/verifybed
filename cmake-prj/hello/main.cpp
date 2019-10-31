#include <boost/filesystem.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <string>
#include <iostream>

using namespace boost::gregorian;
using namespace boost::filesystem;
using namespace std;

void foo()
{
    std::ifstream is("abc.txt", std::ios::binary);

    if (is)
    {
        cout << "open fine" << endl;
    }
    else
    {
        cout << "open failed" << endl;
    }
}

int main()
{
    date weekstart(2019, Feb, 1);
    date weekend = weekstart + weeks(1);

    to_simple_string(weekstart) == "2019-Feb-01";
    to_simple_string(weekend) == "2019-Feb-08";

    foo();

    return 0;
}