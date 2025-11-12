#include <cstdio>
#include <iostream>
#include <memory>

using namespace std;

void test1() {
    // 通过指针进行构造
    auto_ptr<int> aptr(new int(3));

    // 一个取地址，一个取内容 *aptr作为最原始的对象使用
    printf("aptr-%p: %d\r\n", aptr.get(), *aptr);
}

void test2() {
    int *p = new int(3);

    {
        // 通过指针进行构造
        auto_ptr<int> aptr1(p);
        auto_ptr<int> aptr2(p);

        /*
        free(): double free detected in tcache 2
        Aborted (core dumped)
        */
    }
}

void test3() {
    {
        // 通过指针进行构造
        auto_ptr<int> aptr1(new int(3));
        auto_ptr<int> aptr2(new int(111));
        aptr2 = aptr1;
        printf("aptr1-%p: %d\r\n", aptr1.get(), *aptr1);
        printf("aptr2-%p: %d\r\n", aptr2.get(), *aptr2);

        /*
        Segmentation fault (core dumped)
        */
    }
}

void test4() {
    // 释放
    int *pNew = new int(3);
    {
        auto_ptr<int> aptr(pNew);
        int *p = aptr.release();

        // printf("aptr-%p: %d\r\n", aptr.get(), *aptr);   // 已经销毁
        // release 放弃了内部指针的使用权
    }
}

void test5() {
    int *pNew = new int(3);
    int *p = new int(5);

    {
        auto_ptr<int> aptr(pNew);
        aptr.reset(p); // 释放内部指针的内存资源，将其更新为nullptr
    }
}

int main(int argc, char *argv[]) {
    test1(); // 定义一个auto_ptr下的模板类对象

    /* auto_ptr 的两个缺陷 */
    // test2(); // 两个对象指向同一地址
    // test3(); // 赋值后丢失右值
    test4();
    test5();
    return 0;
}