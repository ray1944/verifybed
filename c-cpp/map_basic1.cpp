#include <iostream>
#include <map>
#include <string>


using std::endl;
using std::cout;
using std::map;
using std::string;

void foo(map<string, string>& m) {
    m.clear();
    m["name1"] = "name 1";
    m["name2"] = "name 2";
    m["name3"] = "name 3";
}
int main(int argc, const char* argv[]) {
    map<string, string> tst;
    map<string, string>::const_iterator cit;
    map<string, string>::iterator it;

    foo(tst);

    for (it = tst.begin(); it != tst.end(); ) {
        if (it->first == "name1") {
            it = tst.erase(it);
        } else {
            ++it;
        }
    }

    //print last result
    cout << "First method:" << endl;
    for (cit = tst.begin(); cit != tst.end(); cit++) {
        cout << cit->first << " = " << cit->second << endl;
    }

    foo(tst);
    cout << "Second method with find algorithm: " << endl;
    it = tst.begin();
    if ((it = tst.find("name1")) != tst.end()) {
        tst.erase(it);
    }
    for (cit = tst.begin(); cit != tst.end(); cit++) {
        cout << cit->first << " = " << cit->second << endl;
    }

    return 0;
}