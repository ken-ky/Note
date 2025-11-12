#include <cassert>
#include <iostream>
#include <memory>

using namespace std;

// unique_ptr的使用
void test1() {
    unique_ptr<int> uptr = make_unique<int>(200);
    cout << "uptr-" << uptr.get() << ": " << *uptr << "\r" << endl;
}

void test2() {
    unique_ptr<int> uptr = make_unique<int>(200);
    // unique_ptr<int> uptr1 = uptr;   // 编译错误
    unique_ptr<int> uptr2 = move(uptr);
    assert(uptr == uptr2); // uptr 是 move-only 的
}

void test3() {
    unique_ptr<int[]> uptr = make_unique<int[]>(10);
    for (int i = 0; i < 10; i++) {
        uptr[i] = i * i;
    }
    for (int i = 0; i < 10; i++) {
        cout << uptr[i] << endl;
    }
}

void unique_ptr_exam() {
    test1(); // 创建智能指针
    test2();
    test3(); // 指向数组
}

int main() {
    unique_ptr_exam();
    return 0;
}