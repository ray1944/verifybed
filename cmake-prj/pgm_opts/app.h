#ifndef __APP__
#define __APP__
#include <string>
#include <boost/program_options.hpp>

namespace app
{
    const int ERROR_IN_COMMAND_LINE = 1;
    const int SUCCESS = 0;
    const int ERROR_UNHANDLED_EXCEPTION = 2;
}

/*
 * CApp is the top level class for this application
 * It saves global help message, handle unexpected exception
 * */
class CApp
{
public:
    //Constructors
    CApp():Verbose(false) {}

    /*
     * The main entry for application
     * */
    int Main(int argc, const char* argv[]);

    std::string GetGlobalHelpMessage() const;

public:
    /*
     * option -v|--verbose
     * */
    bool Verbose;

    /*
     * program name
     * */
    std::string ProgramName;

private:
    
    /*
     * Check command global level options and subcommand validity
     * */
    bool _checkUnrecognizedOptions(
        const boost::program_options::parsed_options& t_parsed) const;

    /*
     * Handle global options
     * Global options include: --help|-h, --verbose|-v
     * @int argc: argument count
     * @const char* argv[]: arguments value
     * @return: true if option is  correct, false if not.
     * */
    int _processOptions(int argc, const char* argv[]);

    void _printInvalidOptions(
        const std::vector<std::string>& t_opts) const;

private:
    boost::program_options::variables_map _argvm;
};
#endif