#include <boost/filesystem.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <string>
#include <iostream>
#include <pwd.h>
#include <sys/types.h>
#include <sys/stat.h>

using namespace boost::gregorian;
using namespace boost::filesystem;
using namespace std;

void foo()
{
    std::ifstream is("abc.txt", std::ios::binary);

    if (is)
    {
        cout << "open fine" << endl;
    }
    else
    {
        cout << "open failed" << endl;
    }
}

bool getUIDByName(string t_uname, uid_t& t_uid, gid_t& t_gid)
{
    struct passwd *p = nullptr;

    if ((p = getpwnam(t_uname.c_str())) == nullptr)
    {
        cout << "get " << t_uname <<  " uid failed" << endl;

        return false;
    }
    cout << t_uname << " uid: " << static_cast<uid_t>(p->pw_uid)
         << " gid: " << static_cast<gid_t>(p->pw_gid) << endl;
    t_uid = static_cast<uid_t>(p->pw_uid);
    t_gid = static_cast<gid_t>(p->pw_gid);

    return true;
}

bool chgOwnAuth(string t_name, uid_t t_uid, gid_t t_gid)
{
    if (!chown(t_name.c_str(), t_uid, t_gid))
    {
        if (!chmod(t_name.c_str(), S_IRWXU))
        {
            cout << "change succeeded" << endl;
            return true;
        }
    }
    cout << "change failed" << endl;

    return false;
}

int main()
{
    date weekstart(2019, Feb, 1);
    date weekend = weekstart + weeks(1);
    uid_t uid;
    gid_t gid;

    to_simple_string(weekstart) == "2019-Feb-01";
    to_simple_string(weekend) == "2019-Feb-08";

    foo();
    getUIDByName("ray1944", uid, gid);
    getUIDByName("ray19441", uid, gid);
    if (getUIDByName("pin1944", uid, gid))
    {
        chgOwnAuth("/Users/ray1944/pin1944.pdf", uid, gid);
    }
    path apath = "/home/pcheng/igittest/altst71ai1";

    cout << apath.filename() << endl;

    return 0;
}