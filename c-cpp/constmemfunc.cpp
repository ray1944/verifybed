#include <iostream>

using std::cout;
using std::endl;

/*
 * 常量成员函数可以被非常量对象调用
 * 常量对象只能调用常量成员函数
 */
class B {
private:
    int _c;
public:
    B():_c(1) {

    }

    int calc() const {
        return _c;
    }

    int getc() {
        return _c;
    }
};

int main(int argc, const char* argv[]) {
    const B b;
    b.calc();
    // b.getc();
    B b1;

    b1.calc();

    return 0;
}