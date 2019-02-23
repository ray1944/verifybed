#include <iostream>
#include <string>

using std::cin;
using std::string;
using std::cout;
using std::endl;

int main(int argc, const char * argv[]) {
    string name; // 缺省初始化 string 类对象的内容为空字符串

    cout << name.size() << endl; 
    while(cin >> name) { //ctrl + d 表示 EOF，cin 状态被设为错误。
                         //ctrl + c, 表示 cancel，也会设 cin 的状态为错误。
        cout << name << endl; /* 观察输入后得到的内容。cin 接受输入的规则：
        首先会略去输入的空字符，然后连续将字符读入 name 中 直到遇到 EOF
        */
    }
    return 0;
}