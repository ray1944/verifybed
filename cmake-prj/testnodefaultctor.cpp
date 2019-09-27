#include <string>
#include <iostream>

class Base
{
public:
   Base(int t_i) {
      _i = t_i;
   }
   void foo() {
      std::cout << _i << std::endl;
   }
private:
   int _i;
};

class A 
{
public:
   A(int t_i):_b(t_i) {
      _b.foo();
   }
private:
   Base _b;
};

int main() {
   A a(1);

   return 0;
}
