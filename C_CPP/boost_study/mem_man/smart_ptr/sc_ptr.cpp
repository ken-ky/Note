#include <iostream>
using namespace std;

#include <boost/smart_ptr/scoped_ptr.hpp>
using namespace boost;

void test1() {
    cout << "test1: " << endl;
    scoped_ptr<string> sp(new string("text")); // 构造一个scoped_ptr对象

    assert(sp); // 使用显式 bool 转型
    assert(sp != nullptr);

    // 不能对scoped_ptr进行delete，否则会编译错误
    cout << "str: " << *sp << endl;
    cout << "size: " << sp->size() << endl;
    cout << endl;
}

void test2() {
    class ptr_owned final { // 一个持有scoped_ptr成员变量的类不可拷贝和赋值
        scoped_ptr<int> m_ptr;
    };

    ptr_owned p;
    // ptr_owned p2(p); // 编译错误
}

void test3() {
    cout << "test3: " << endl;

    struct posix_file {                     // 示范性质文件夹类
        posix_file(const char *file_name) { // 构造函数打开文件
            cout << "open file: " << file_name << endl;
        }

        ~posix_file() { // 析构函数关闭文件
            cout << "close file" << endl;
        }
    };

    // 文件类的scoped_ptr，将在离开作用域时自动析构
    scoped_ptr<posix_file> fp(new posix_file("./basis_CPP/test_file.txt"));
    scoped_ptr<int> p(new int); // 一个 int 指针的scoped_ptr

    if (p) { // 可以显式的转换为bool
        *p = 100;
        cout << *p << endl;
    }

    p.reset(); // 置空

    assert(p == 0);

    if (!p) { // 在显示转换bool时，逻辑运算也与bool类似
        cout << "scoped_ptr == nullptr" << endl;
    }
    cout << endl;
}

int main() {
    test1();
    test2();
    test3();
    return 0;
}