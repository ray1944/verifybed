#include "app.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, const char* argv[])
{
    try
    {
        CApp app;

        app.Main(argc, argv);
    }
    catch (std::exception& e)
    {
        cerr << "Unhandled Exception reached the top of main: "
            << e.what() << ", application will now exit" << endl;
        
        return app::ERROR_UNHANDLED_EXCEPTION;
    }

    return app::SUCCESS;
}