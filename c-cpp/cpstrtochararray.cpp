#include <algorithm>
#include <string>
#include <iostream>

using namespace std;
int main(int argc, const char* argv[])
{
    string from = "abc1234";
    char* inbuf = new char[from.size() + 1];

    copy(from.begin(), from.end(), inbuf);
    inbuf[from.size()] = '\0';
    cout << from << "[" << from.size() << "]"<< endl;
    cout << inbuf << "[" << sizeof(inbuf) << "]"<< endl;
    
    return 0;
}