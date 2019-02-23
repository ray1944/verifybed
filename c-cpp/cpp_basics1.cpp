#include<iostream>
#include<string>
#include<cstddef>
#include<iomanip>
/*
 * string::size_type 
 * const 变量进行初始化的数值本身无需是一个常量
 * typedef string::size_type sz_t
 * size_t defined in <cstddef>
 * std::setprecision defined in <iomanip>, 设置 cout 流的数字的有效位
 * std::streamsize defined in <ios>, cout.precision() 的返回类型
 * 重置流
 */
using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::setprecision;
using std::streamsize;

int main(int argc, const char* argv[]) {
    string name;
    cin >> name;
    const string greeting = "Hello, " + name + "!"; //const 变量进行初始化的数值本身无需是一个常量
    string::size_type size = greeting.size(); // size_type
    cout << greeting << endl;
    cout << "size: " << size << endl;

    size_t sz = size;
    typedef string::size_type sz_t;
    const sz_t s = size;

    cout << "sz_t: " << s << endl;
    cout <<"size_t: "<< sz << endl;

    const streamsize prec = cout.precision();
    cout << "You find grade is " << setprecision(5) << 98.12345 
         << setprecision(prec) << " " << 98.123456 << endl;

    while(cin >> name) {
        cout << "Input name: " << name << endl;
    }
    if (cin) {
        cout << "cin in good state" << endl;
    } else {
        cout << "cin in bad state" << endl;
        cin >> name;
        cout << "continue use cin which is in bad state: " << name << endl;

        cin.clear();
        if (cin) {
            cout << "cin is in good state after clear()" << endl;
        } else {
            cout << "cin is still in bad state" << endl;
        }
    }
    
    

    return 0;
}