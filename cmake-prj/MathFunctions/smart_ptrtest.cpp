#include <memory>
#include <iostream>

class Base
{
public:
    Base() 
    {
        std::cout << "Base ctor" << std::endl;
    }

    ~Base()
    {
        std::cout << "Base destructor" << std::endl;
    }
};

void foo() 
{
    std::shared_ptr<Base> ptr1(new Base);
}

int main()
{
    foo();

    return 0;
}