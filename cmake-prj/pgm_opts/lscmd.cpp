#include "lscmd.h"

#include <string>
#include <iostream>

#include "app.h"

using namespace std;
namespace po = boost::program_options;
int ClsCommand::Run(int argc, const char *argv[])
{
    if (_processOptions(argc, argv))
    {
        // TODO: functions of ls command
    }

    return app::SUCCESS;
}

bool ClsCommand::_processOptions(int argc, const char *argv[])
{
    po::options_description ls_desc("ls options");
    ls_desc.add_options()
        ("hidden", "Show hidden files")
        ("path", po::value<std::string>(), "Path to list");
    po::parsed_options parsed = po::command_line_parser(argc, argv)
        .options(ls_desc)
        .allow_unregistered()
        .run();
    po::store(parsed, _argvm);
    _path = _argvm["path"].as<string>();

    cout << "argument: " << _path << endl;

    return true;
}