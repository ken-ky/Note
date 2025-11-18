#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

// 基本使用
void test1() {
    shared_ptr<int> sp(new int(10));
    assert(sp.unique());

    shared_ptr<int> sp2 = sp;
    assert(sp == sp2 && sp.use_count() == 2);

    *sp2 = 100; // 解引用操作符修改被指对象
    assert(*sp2 == 100);

    sp.reset();
    assert(!sp);
}

// 较复杂用法
void test2() {
    class shared {
      private:
        shared_ptr<int> p;

      public:
        shared(shared_ptr<int> p_) : p(p_) {}
        void print() {
            cout << "count:" << p.use_count() << " v=" << *p << endl;
        }
    };

    function<void(shared_ptr<int>)> print_func = [&](shared_ptr<int> p) {
        cout << "count:" << p.use_count() << " v=" << *p << endl;
    };

    cout << "test2:" << endl;
    shared_ptr<int> p = make_shared<int>(100);
    shared s1(p), s2(p);

    s1.print();
    s2.print();

    *p = 20;
    print_func(p); // 内部拷贝了一个p，因此引用计数加一
    // 结束函数时析构，因此引用计数减一

    s1.print();
}

// make_shared用法
void test3() {
    auto sp = make_shared<string>("make_shared"); // 创建string共享指针
    auto spv = make_shared<vector<int>>(10, 2);
    assert(spv->size() == 10);
}

// 标准容器内应用
void test4() {
    cout << "test4: " << endl;

    typedef vector<shared_ptr<int>> vs; // 持有shared_ptr的标准容器类型
    vs v(10);                           // 声明10个元素的容器

    int i = 0;
    for (auto pos = v.begin(); pos != v.end(); ++pos) {
        (*pos) = make_shared<int>(++i); // 使用工厂函数赋值
        cout << *(*pos) << ", ";
    }
    cout << endl;

    shared_ptr<int> p = v[9];
    *p = 100;
    cout << *v[9] << endl;
}

// 删除器样例
void test5() {
    cout << "test5: " << endl;

    class socket_t {
      private:
        int id;

      public:
        socket_t() : id(-1) {}
        socket_t(int x) : id(x) {}
    };

    function<socket_t *()> open_socket = [&]() -> socket_t * {
        cout << "open_socket" << endl;
        return new socket_t;
    };

    function<void(socket_t * s)> close_socket = [&](socket_t *s) {
        cout << "close_socket" << endl;
    };

    {
        socket_t *s = open_socket();
        shared_ptr<socket_t> p(s, close_socket); // 传入删除器
        // 这里传递删除器函数或者取地址的 &close_socket() 都可以
    }
}

/* 高级议题 */
// 显示布尔转换
// if、assert、for等逻辑判断语境，shared_ptr可以隐式转换
// 但其他情况（函数参数或返回值）必须显式转换
void test6() {
    cout << "test6: " << endl;

    auto bool_test = [&]() -> bool {
        auto p = make_shared<int>(776);

        assert(p);
        if (p) {
            cout << "explicit cast: ";
        }
        return static_cast<bool>(p);
    };

    cout << bool_test() << endl;
}

int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    return 0;
}