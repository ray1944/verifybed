#include <iostream>

using std::cout;
using std::endl;

class Base {};

int main(int argc, const char * argv[]) {
    int a = 1;
    int& r = a;
    Base c;
    Base& rc = c;
    cout << "a address: " << &a << endl;
    cout << "r address: " << &r << endl;

    cout << "c address: " << &c << endl;
    cout << "rc address: " << &rc << endl;

    return 0;
}