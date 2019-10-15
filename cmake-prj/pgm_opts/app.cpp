#include "app.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

#include "cmd.h"

using namespace std;
namespace po = boost::program_options;

int CApp::Main(int argc, const char* argv[])
{
    int ret = app::ERROR_IN_COMMAND_LINE;

    //Get program name
    ProgramName = argv[0];

    // handle global options
    if (_processOptions(argc, argv) == app::SUCCESS)
    {
        // --help, --verbose
        if (_argvm.count("help"))
        {
            cout << GetGlobalHelpMessage() << endl;

            return app::SUCCESS;
        }
        //TODO: other global options
        if (_argvm.count("verbose"))
        {
            //increase to remove "verbose" option
            argc--;
            argv++;
        }
        // increase to remove program name
        argc --; 
        argv ++;
    }
    else
    {
        cout << "Error: options is not correct." << endl;
        cout << GetGlobalHelpMessage() << endl;

        return ret;
    }

    std::shared_ptr<CCmd> pcmd(
        CCmd::CreateCommand(_argvm["command"].as<string>()));
    if (pcmd != nullptr)
    {
        ret = pcmd->Run(argc, argv);
    }
    else
    {
        // Subcommand is empty
        cout << GetGlobalHelpMessage() << endl;
    }

    return ret;
}

int CApp::_processOptions(int argc, const char *argv[])
{
    /*
     * Setting up global options
     * */
    po::options_description global("Global options");
    global.add_options()
        ("help", "Help message")
        ("verbose", "Turn on verbose output")
        ("command", po::value<std::string>(), "Command to execute")
        ("subargs", po::value<std::vector<std::string> >(), "Arguments for command");

    po::positional_options_description pos;
    //only one command, infinity subargs
    pos.add("command", 1).add("subargs", -1);

    /*
     * Parse global options
     * the applicaton accepts the following command pattern
     * app [--help|-h] [--verbose|-v] sub-command [options]
     */
    po::parsed_options parsed = po::command_line_parser(argc, argv)
        .options(global)
        .positional(pos)
        .allow_unregistered()
        .run();
    po::store(parsed, _argvm);
    po::notify(_argvm);

    /*
     * Check if command line arguments have unrecognized global options
     * */
    if (_checkUnrecognizedOptions(parsed))
    {
        return app::SUCCESS;
    }
    else
    {
        return app::ERROR_IN_COMMAND_LINE;
    }
}

bool CApp::_checkUnrecognizedOptions(
    const po::parsed_options& t_parsed) const
{
    /*
     * Check all command provided arguments, there are
     * three possible status: all valid, all invalid, partial valid
     * */
    vector<string> opts =
        po::collect_unrecognized(t_parsed.options, po::include_positional);
    
    if (_argvm.count("help") 
        || _argvm.count("verbose") 
        || _argvm.count("command")
        || _argvm.count("subargs"))
    {
        // all valid options but sometime they are mutual exclusive
        if (_argvm.count("help") && _argvm.count("verbose"))
        {
            // --help and --verbose are mutual exclusive
            cout << "--help and --verbose are mutual exclusive." << endl;

            return false;
        }
        // --verbose option need subcommand
        if (_argvm.count("verbose") && !_argvm.count("command"))
        {
            cout << "No subcommand provided" << endl;

            return false;
        }
        // have invalid options not plus subcommand and subcommand options
        if (_argvm.count("command"))
        {
            string subcmd = _argvm["command"].as<std::string>();
            vector<string> remain;
            vector<string>::iterator result = 
                find(opts.begin(), opts.end(), subcmd);

            copy(opts.begin(), result, back_inserter(remain));
            if (remain.size() > 0)
            {
                _printInvalidOptions(remain);

                return false;
            }
            //no invalid options no include subcommand's
            return true;
        }
        // have invalid options and no subcommand
        if ((opts.size() > 0) && !_argvm.count("command"))
        {
            // has invalid options
            _printInvalidOptions(opts);

            return false;
        }

        // all valid, good arguments
        return true;

    }
    else
    {
        // all invalid, no recognized arguments
        //TODO: print all invalid options
        return false;
    }

    return false;    
}

void CApp::_printInvalidOptions(
    const vector<string>& t_opts) const
{
    vector<string>::const_iterator itr = t_opts.begin();
    for (; itr != t_opts.end(); ++itr)
    {
        cout << *itr << " ";
    }
    cout << "option invalid." << endl;
}

std::string CApp::GetGlobalHelpMessage() const 
{
  return "Command help message, version info";
}

/*
 * test cases
 * $cmd abc "unknown subcommand"
 * $cmd --version --help "unknown option"
 * $cmd --help "help message printed"
 * $cmd --verbose "No subcommand provided"
 * $cmd --verbose --help "mutual exclusive options"
 * $cmd --aaaa  "unknown option"
 * $cmd -s -b abc "unknown subcommand invalid options"
 * */