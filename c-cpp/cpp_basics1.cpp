#include<iostream>
#include<string>
/*
 * string::size_type 
 * const 变量进行初始化的数值本身无需是一个常量
 * 
 */
using std::cout;
using std::cin;
using std::string;
using std::endl;

int main(int argc, const char* argv[]) {
    string name;
    cin >> name;
    const string greeting = "Hello, " + name + "!";
    string::size_type size = greeting.size();
    cout << "size: " << size << endl;

    return 0;
}