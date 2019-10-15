#include <iostream>
#include <string>

using std::string;
using std::iostream;
using std::cout;
using std::endl;

int main(int argc, const char* argv[]) {
   string str = "Hello world";
   string::reverse_iterator ritr;
   string str1 = "1////////2";

   ritr = str.rbegin();
   cout << "Reverse iterator: " << *ritr << endl;
   string::iterator itr;
   itr = ritr.base();
   cout << "back to iterator: " << *itr << endl;
   
   return 0;
}