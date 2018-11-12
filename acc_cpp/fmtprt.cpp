#include <iostream>
using namespace std;
int main() {
    string name;

    cout<< "Please input your name: " << endl;
    cin >> name;
    string greeting = "Hello " + name;
    string second(greeting.size(), ' ');
    string first(greeting.size() + 4, '*');

    second = "* " + second + " *";
    greeting = "* " + greeting + " *";

    cout << first << endl;
    cout << second << endl;
    cout << greeting << endl;
    cout << second << endl;
    cout << first << endl;


    return 0;
}