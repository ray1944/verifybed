#include <iostream>
#include <vector>
using std::vector;
using std::cout;
using std::endl;
using std::cin;
/*
 * 容器里放的对象是加入对象的拷贝
 * 容器销毁时会负责销毁他里面的对象
 */
class Obj {
public:
    Obj() {
        cout << "construct Object: " << this << endl;
    }
    Obj(const Obj& other) {
        cout << "Copy construct Object: " << this << endl;
    }
    ~Obj() {
        cout << "Destruct Object: " << this << endl;
    }
};
int main(int argc, const  char * argv[] ) {
    Obj o;
    char c;
    vector<Obj> vec;
    
    vec.push_back(o);
    while (cin >> c);
    cin.clear();

    return 0;

}