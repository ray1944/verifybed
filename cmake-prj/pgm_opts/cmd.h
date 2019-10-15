#ifndef __CMD__
#define __CMD__ 1
#include <boost/program_options.hpp>

/*
 * class CCmd is the root class to hold 
 * top level command options and value
 * */
class CCmd {
public:
    //Constructors
    CCmd(){}

    //Destructor
    virtual ~CCmd() {}

    /*
     * Run() method is the main entry of the
     * command
     * @int argc: command arguments count
     * @const char* argv: command arguments value
     * @return int: 0 if Success, others if failed
     * */
    virtual int Run(int argc, const char *argv[]) = 0;

    /*
     * CreateCommand is a static factory to return 
     * concrete CCmd object correspond specific 
     * subcommand
     * */
    static CCmd* CreateCommand(std::string);

protected:
    /*
     * _processOptions method is to parse options
     * @int argc: command arguments count
     * @const char* argv: command arguments value
     * @return bool: true if option is correct
     *               false if option is not correct
     * */
    virtual bool _processOptions(int argc, const char *argv[]) = 0;

protected:
    boost::program_options::variables_map _argvm;
};
#endif //__CMD_OPTIONS__