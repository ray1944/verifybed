#include <memory>
#include <iostream>
#include <string>

using namespace std;

void basic_init()
{
    shared_ptr<int> aptr = nullptr;
    
    cout << "basic_init" << endl;
    if (aptr)
    {
        cout << "not null pointer" << endl;
    }
    else
    {
        cout << "null pointer" << endl;
    }

    shared_ptr<int> bptr;
    if (bptr)
    {
        cout << "not null pointer" << endl;
    }
    else
    {
        cout << "null pointer" << endl;
    }
    
    aptr.reset(new int(10));
    if (aptr)
    {
        cout << "not null pointer" << endl;
    }
    else
    {
        cout << "null pointer" << endl;
    }

    shared_ptr<int> cptr;

    //cptr = new int(10); shared_ptr has no assignemnt operator
    
}

struct CRcd
{
    string name;
    shared_ptr<int> opptr;
};

void init_struct()
{
    CRcd rcd{"tmp", nullptr};

    cout << "init_struct" << endl;
    if (rcd.opptr)
    {
        cout << "not null pointer" << endl;
    }
    else
    {
        cout << "null pointer" << endl;
    }
}

int main()
{
    basic_init();
    init_struct();

    return 0;
}