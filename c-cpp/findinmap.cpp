#include <iostream>
#include <map>
#include <string>
#include <algorithm>

using std::cout;
using std::endl;
using std::map;
using std::string;
using std::pair;
using std::find_if;

/*
 * given a map<enum, string>
 * I want to find a string whether and where in the map
 */

typedef enum {
    ALLSUBCMD = 0,
    BACKUPCMD,
    RESTORECMD,
    INVALIDCMD
}ESUB_CMD;

const string cmd_str[] = {
    "*ALL",
    "backup",
    "restore",
    "invalid"
};

typedef map<ESUB_CMD, string> ACCmdMap;
typedef pair<ESUB_CMD, string> ACCmdMapPair;

static ACCmdMap cmdmap;

class CheckCmd {
private:
    string _cmd;
public:
    CheckCmd(string cmd): _cmd(cmd) {}
    bool operator() (const ACCmdMapPair& v) const
    {
        return v.second == _cmd;
    }

};
void init() {
    for (int idx = 0; idx < INVALIDCMD; idx++) {
        ACCmdMapPair pair(ESUB_CMD(idx), cmd_str[idx]);
        cmdmap.insert(pair);
    }
}

int main(int argc, const char* argv[]) {
    string subcmd;
    init();
    if (argc < 2) {
        cout << "Invalid command arguments count" << endl;
    }
    subcmd = argv[1];
    ACCmdMap::iterator it = find_if(cmdmap.begin(), cmdmap.end(), CheckCmd(subcmd));
    if (it != cmdmap.end()) {
        cout << "Command: " << subcmd << " is valid" << endl;
    } else {
        cout << "Command: " << subcmd << " is invalid" << endl;
    }
    return 0;
}