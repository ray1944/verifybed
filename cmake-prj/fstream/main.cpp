#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    string localf = "/Users/ray1944/aldev71a-sqlscript.sql";
    std::ifstream is(localf, std::ifstream::binary);
    char buf[1024];
    int nread;

    is.seekg(0, ios::beg);
    if (!is)
    {
        cout << "----------- Open local source file failed " << localf << endl;
    }
    do 
    {
        //read file
        if (is)
        {
            is.read(buf, sizeof(buf));
            nread = is.gcount();
            if (nread == 0)
            {
                // nothing to read
                cout << "----------- nothing to read" << endl;
                break;
            }
            cout << "----------- read file " <<  nread << endl;
            cout << "----------- content: " << endl << string(buf, nread) << endl;
        }
        else
        {
            cout << "----------- reach file EOF";
            break; //EOF
        }
    } while(nread > 0);

    return 0;
}