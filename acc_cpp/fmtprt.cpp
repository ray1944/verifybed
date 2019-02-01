#include <iostream>
using namespace std;
int main() {
    string name;

    cout<< "Please input your name: " << endl;
    cin >> name;
    const string greeting = "Hello " + name + "!";
    const string spaces(greeting.size(), ' ');
    const string second = "* " + spaces + " *";
    const string first(second.size(), '*');

    cout << first << endl;
    cout << second << endl;
    cout << "* " << greeting << " *" << endl;
    cout << second << endl;
    cout << first << endl;


    return 0;
}