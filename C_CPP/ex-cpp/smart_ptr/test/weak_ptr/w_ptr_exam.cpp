#include <boost/enable_shared_from_this.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/weak_ptr.hpp>
#include <cassert>
#include <iostream>
#include <memory>

using namespace std;

// weak_ptr的基本使用
void test1() {
    boost::shared_ptr<int> sp(new int(10)); // 一个shared_ptr
    assert(sp.use_count() == 1);

    boost::weak_ptr<int> wp(sp); // 从shared_ptr创建weak_ptr
    assert(wp.use_count() == 1); // weak_ptr不影响引用计数
    assert(!wp.empty());         // weak_ptr此时非空指针

    if (!wp.expired()) { // 判断wp指向内容是否失效
        boost::shared_ptr<int> sp2 = wp.lock(); // 上锁获得一个新shared_ptr
        *sp2 = 100;
        assert(wp.use_count() == 2);
    } // 退出作用域，sp2自动析构，引用计数减1

    assert(wp.use_count() == 1);
    sp.reset(); // shared_ptr失效
    assert(wp.expired());
    assert(!wp.lock()); // wp指向的内容变为空指针了
}

// 对象自我管理
void test2() {
    cout << "test2:" << endl;

    // 一个需要用shared_ptr进行自我管理的类
    class self_shared : public enable_shared_from_this<self_shared> {
      public:
        int x;
        self_shared(int n) : x(n) {}
        void print() { cout << "self_shared:" << x << endl; }
    };

    {
        auto sp = make_shared<self_shared>(313);
        sp->print();

        auto p = sp->shared_from_this(); // 返回this指针的shared_ptr
        p->x = 1000;
        p->print();
    }
}

// 循环引用问题
void test3() {
    class node { // 一个用于链表节点的类
      public:
        ~node() { // 析构输出信息
            cout << "deleted" << endl;
        }
        typedef shared_ptr<node> ptr_type; // 指针类型使用shared_ptr
        ptr_type next;                     // 后继指针
    };

    {
        auto p1 = make_shared<node>(); // 两个节点对象
        auto p2 = make_shared<node>();

        p1->next = p2;
        p2->next = p1;

        assert(p1.use_count() == 2);
        assert(p2.use_count() == 2);
    } // 退出作用域，shared_ptr无法正常析构
}

void test4() {
    cout << "test4" << endl;

    class node {
      public:
        ~node() { // 析构输出信息
            cout << "deleted" << endl;
        }
        typedef weak_ptr<node> ptr_type; // 指针类型使用shared_ptr
        ptr_type next;                   // 后继指针
    };

    {
        auto p1 = make_shared<node>(); // 两个节点对象
        auto p2 = make_shared<node>();

        p1->next = p2;
        p2->next = p1;

        assert(p1.use_count() == 1);
        assert(p2.use_count() == 1);

        if (!p1->next.expired()) { // 检查“弱”引用是否有效
            auto p3 = p1->next.lock();
        }
    }
}

int main() {
    test1();
    test2();

    // test3();    // 循环引用
    test4();
    return 0;
}