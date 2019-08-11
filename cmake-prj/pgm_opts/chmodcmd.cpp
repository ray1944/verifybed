#include "chmodcmd.h"

#include "app.h"

bool ChmodCommand::_processOptions(int argc, const char *argv[])
{
    return true;
}

int ChmodCommand::Run(int argc, const char *argv[])
{
    if (_processOptions(argc, argv))
    {
        //TODO: chmod command function
    }

    return app::SUCCESS;
}