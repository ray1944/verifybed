#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

void testistream()
{
    ifstream inputfile("test.txt");
    char buf[100];
    int  line = 0;

    while (inputfile.read(buf, 100))
    {
        cout << line++ << ":" << buf;
    }     
}

void testsstream()
{
    std::ostringstream out;
    unsigned char buf[10] = {
        0xa, 0xc, 0x12, 0xf, 0x9,
        0xe, 0x1, 0x2, 0x89, 0x19
    };
    for (int i = 0; i < 10; i++)
    {
        out.width(2);
        out.fill('0');
        out << std::hex << static_cast<int>(buf[i]); //不加类型转换就是按"字符输出"
    }
    std::cout << out.str() << std::endl;
}

int main()
{
    ofstream outfile("test.txt", ios::out|ios::trunc);

    int i = 0;
    for (int n = 0; n < 4096; n++)
    {
        outfile << (i++)%10;
        if (i % 99 == 0 && i > 0)
        {
            outfile << "\n";
            i = 0;
            continue;
        }
        
    }
    outfile.close();
    cout << "Read file ..." << endl;
    testistream();
    testsstream();

    return 0;
}