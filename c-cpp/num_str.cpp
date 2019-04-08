#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>

using namespace std;

int main(int argc, const char* argv[]) {
   string str1 = "750";

   try {
      cout << boost::lexical_cast<int>(str1) << endl;
   } catch (boost::bad_lexical_cast& e) {
      cerr << "Bad cast: " << e.what() << endl;
   }
}