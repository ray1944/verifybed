#ifndef __LS_CMD__
#define __LS_CMD__ 1
#include "cmd.h"

#include <string>
#include <boost/program_options.hpp>

/*
 * class ClsCommand is to hold ls subcommand options
 * and values
 * */
class ClsCommand : public CCmd {
public:
    // Constructors
    ClsCommand() {}

    // Destructors
    ~ClsCommand() {}

    virtual int Run(int argc, const char *argv[]);

protected:
    virtual bool _processOptions(int argc, const char *argv[]);

private:
    bool _hidden;
    std::string _path;
};
#endif // __LS_CMD__ 