#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

void foo(int& a) {
    return;
}

int nonlvalue() {
    int a;
    return a; 
}
int main(int argc, const char* argv[]) {
    int a, b;

    a = b = 1;
    //foo(nonlvalue()); nonlvalue() is non-lvalue

    return 0;
}