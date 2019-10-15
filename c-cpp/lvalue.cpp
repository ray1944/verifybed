#include <iostream>
#include <string>
#include <stdio.h>
using std::cout;
using std::endl;
using std::string;

void foo(int &a) { return; }

int nonlvalue() 
{
    int a;

    return a;
}

int main(int argc, const char *argv[]) 
{
    int a, b;

    a = b = 1;
    // foo(nonlvalue()); nonlvalue() is non-lvalue
    printf("%-10s/-10s", "QSYS", "QSYSINC");

    return 0;
}