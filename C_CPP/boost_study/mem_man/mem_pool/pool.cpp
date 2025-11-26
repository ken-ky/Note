#define BOOST_POOL_NO_MT

#include <boost/pool/object_pool.hpp>    // object_pool
#include <boost/pool/pool.hpp>           // pool
#include <boost/pool/singleton_pool.hpp> // singleton_pool
#include <cassert>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using namespace boost;

/* pool类型 */
// 基本用法
void test1() {
    pool<> p1(sizeof(int)); // 一个可分配int的内存池

    int *p = static_cast<int *>(p1.malloc()); // 需要将void*转换为需要的类型
    if (p == nullptr) {
        cout << "test1: "
             << "内存分配失败" << endl;
    }

    assert(p1.is_from(p)); // 确认是否p为p1分配的对象

    p1.free(p);                     // 释放内存池所在的块
    for (int i = 0; i < 100; i++) { // 连续分配大量内存
        p1.ordered_malloc(10);
    }
} // 内存池对象析构，所有分配内存在此释放

/* object_pool类型 */
// 基本用法
void test2() {
    cout << "test2:" << endl;

    struct demo_class {
      public:
        int a, b, c;
        demo_class(int x = 1, int y = 2, int z = 3) : a(x), b(y), c(z) {}
    };

    {
        /* 第一种分配方式 */
        object_pool<demo_class> p1; // 对象内存池

        auto p = p1.malloc(); // 分配一个原始内存块
        assert(p1.is_from(p));

        // p指向的内存未经过初始化
        assert(p->a != 1 || p->b != 2 || p->c != 3);

        p = p1.construct(7, 8, 9); // 构造一个对象，可以传递参数
        assert(p->a == 7);

        /* 第二种分配方式 */
        object_pool<string> pls;       // 定义一个string对象的内存池
        for (int i = 0; i < 10; i++) { // 构建一个对象，可以传递参数
            string *ps = pls.construct("hello object_pool");
            cout << *ps << endl;
        }
    }
}

// 可变参数模板构造
template <typename P, typename... Args> // 可变参数模板
inline typename P::element_type *construct(P &p, Args &&... args) {
    typename P::element_type *mem = p.malloc();

    assert(mem != 0); // 检查不为空指针
    new (mem) typename P::element_type(std::forward<Args>(args)...); // 完美转发
    return mem;
}

void test3() {
    struct demo_class {
        demo_class(int, int, int, int) { // 构造函数接收4个参数
            cout << "demo_class ctor" << endl;
        }
        ~demo_class() { cout << "demo_class dtor" << endl; }
    };

    {
        object_pool<demo_class> p1;
        auto d = construct(p1, 1, 2, 3, 4);
    }
}

/* singleton_pool类型 */
// 基本用法
void test4() {
    struct pool_tag {};
    typedef singleton_pool<pool_tag, sizeof(int)> sp1; // 内存池定义

    {
        int *p = (int *)sp1::malloc(); // 分配一个整数内存块
        assert(sp1::is_from(p));
        sp1::release_memory(); // 释放所有未被分配的内存
    } // sp1的内存直至程序结束才完全释放，而不是退出作用域
}

int main() {
    /* pool类型 */
    test1(); // pool基本用法

    /* object_pool类型 */
    test2(); // object_pool基本用法
    test3();
    return 0;
}