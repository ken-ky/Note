#include <boost/pool/object_pool.hpp> // object_pool
#include <boost/pool/pool.hpp>        // pool
#include <cassert>
#include <iostream>

using std::cout;
using std::endl;
using namespace boost;

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

int main() {
    /* pool类型 */
    test1(); // pool基本用法
    return 0;
}