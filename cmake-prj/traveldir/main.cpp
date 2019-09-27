#include <iostream>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;
using namespace std;

bool isLibrary(string library)
{
    fs::path p = "/QSYS.LIB/" + library + ".LIB";
    bool ret = false;

    try
    {
        if (fs::is_directory(p))
        {
            ret = true;
        }
    }
    catch (const fs::filesystem_error& e)
    {
        cout << e.what() << endl;
        ret = false;
    }

    return ret;
}

void recursive_traverse_dir()
{
    string library = "pcheng";
    fs::path p;

    /*
     * Check the library existence
     */
    if (isLibrary(library))
    {
        p = "/QSYS.LIB/" + library + ".LIB";
        //traverse the p directory
        fs::recursive_directory_iterator end;
        try {
            fs::recursive_directory_iterator itr(p);
            for (; itr != end; ++itr)
            {
                if (fs::is_directory(*itr))
                {
                    cout << "Library: " << *itr << endl; 
                    cout << "level: " << itr.level() << endl;
                }
            }
        }
        catch (const fs::filesystem_error& e)
        {
            cout << e.what() << endl;
        }
    }
    else 
    {   
        cout << "Not a library" << endl;
    }
}

void traverse_directory()
{
    fs::path lib_level(fs::current_path());
    for (fs::directory_iterator itr(lib_level); itr != fs::directory_iterator(); itr++)
    {
        fs::path sub_entry = *itr;
        if (fs::is_regular_file(itr->path()))
        {
            cout << "regular file: " << *itr << endl; 
            cout << "basename: " << fs::basename(*itr) << endl;
            cout << "extension: " << fs::extension(*itr) << endl;
        }
        if (fs::is_directory(itr->path()))
        {
            cout << "directory: " << *itr << endl;
            cout << "basename: " << fs::basename(*itr) << endl;
            cout << "extension: " << fs::extension(*itr) << endl;
        }
    }
    fs::current_path("./");
}

int main()
{
    traverse_directory();
    
    return 0;
}