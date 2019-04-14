#include <iostream>
#include <unistd.h>
using namespace std;


int main(int argc, const char* argv[]) {
   int count = 10;
   cerr << "I am error." << endl;
   clog <<  "I am log." << endl;

   while (count) {
      sleep(1);
      count--;
   }

   return 0;
}