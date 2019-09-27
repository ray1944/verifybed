#include <iostream>
#include <map>
#include <string>


using std::endl;
using std::cout;
using std::map;
using std::string;
using std::cin;

class Base {
private:
    string name;
public:
    Base(string name = "temp") {
        this->name = name;
    }
    ~Base() {
        cout << "Destroy object " << name << endl;
    }
};
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
            tst.erase(it++);
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

    map<string, Base> objmap;
    Base obj1("obj1");
    Base obj2("obj2");
    objmap["obj1"] = obj1;
    objmap["obj2"] = obj2;
    map<string, Base>::iterator objit;
    map<string, Base>::const_iterator cobjit;

    objit = objmap.begin();
    if ((objit = objmap.find("obj1")) != objmap.end()) {
        objmap.erase(objit);
    }
    cout << "Remained objects: " << endl; 
    for (cobjit = objmap.begin(); cobjit != objmap.end(); cobjit++) {
        cout << cobjit->first << endl;
    }
    string end;
    cout << std::hex << 10 << endl;
    cin >> end;

    return 0;
}
