#include <iostream>
#include <memory>

using namespace std;

// 删除左值的测试
void test1() {
    unique_ptr<int> p1 = make_unique<int>(1);
    int *a = p1.release(); // 释放左指针
    cout << *a << endl;
    delete a; // 需要手动删除
}

// 重置所有权，指向空指针
void test2() {
    unique_ptr<int> p1 = make_unique<int>(1);
    p1.reset();
    cout << p1.get() << endl;
}

int main() {
    test1();
    test2();
    return 0;
}