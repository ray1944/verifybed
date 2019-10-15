#ifndef __CHMOD_CMD__
#define __CHMOD_CMD__ 1
#include "cmd.h"

#include <string>

/*
 * class CchmodCommand is subcommand chmod
 * */
class ChmodCommand: public CCmd {
public:
    // Constructors
    ChmodCommand() {}

    // Destructor
    ~ChmodCommand() {}

    virtual int Run(int argc, const char *argv[]);

protected:
    virtual bool _processOptions(int argc, const char *argv[]);

private:
  bool recurse_;
  std::string perms_;
  std::string path_;

};
#endif // __CHMOD_CMD__