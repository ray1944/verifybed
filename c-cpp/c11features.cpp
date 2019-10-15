#include <iostream>
#include <vector>
#include <stdio.h>
using namespace std;

void rvalueref() 
{
    int i = 42;
    int &r = i;
    
}

int main(int argc, const char *argv[]) 
{
    int a = 10;

    auto au_a = a; // auto 类型可以在编译器推导出变量的类型
    cout << typeid(au_a).name() << endl;

    vector<int> iv;
    auto itr = iv.begin();
    cout << typeid(itr).name() << endl; //typeid是 RTTI，影响性能，可访问 type_info

    printf("%-10s/%-10s", "QSYS", "QSYSINC");

    return 0;
}