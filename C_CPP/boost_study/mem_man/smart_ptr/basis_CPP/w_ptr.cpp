#include <iostream>
#include <memory>

using namespace std;

void Observe(weak_ptr<int> wptr) {
    // 如果wptr内部存在需要观察的对象（shared_ptr），则可以完成lock()变为shared_ptr
    if (auto sptr = wptr.lock()) {
        cout << "value: " << *sptr << endl;
    } else {
        cout << "wptr lock fail" << endl;
    }
}

void test1() {
    weak_ptr<int> wptr;
    {
        auto sptr = make_shared<int>(111);
        wptr = sptr; // 指向观察对象
        Observe(wptr);
    }
    Observe(wptr); // 观察对象结束生命周期，无法上锁
}

int main() {
    test1(); // weak_ptr基本使用
    return 0;
}