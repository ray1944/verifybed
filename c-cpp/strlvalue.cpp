#include <iostream>
#include <string>

using std::cout;
using std::string;

void foo(string& name) {
    name += "End";
}

int main(int argc, const char* argv[]) {
    string name;
    foo("ABC");   // 字符串常量就是右值。

    return 0;        
}