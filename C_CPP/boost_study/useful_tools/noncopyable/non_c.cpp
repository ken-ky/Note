#include <boost/noncopyable.hpp>

using boost::noncopyable;

void test1() {
    class do_not_copy : noncopyable {}; // 将拷贝构造方法设为私有

    do_not_copy d1;
    // do_not_copy d2(d1); // 编译出错，不允许拷贝
    do_not_copy d3;
    // d3 = d1; // 企图拷贝构造，不被允许
}

void test2() {
    // 禁止拷贝类实现
    class noncopyable0 {
      protected:
        noncopyable0() {}
        ~noncopyable0() {}

      private:
        noncopyable0(const noncopyable0 &); // 禁止拷贝构造
        const noncopyable0 &operator=(const noncopyable0 &); // 禁止赋值拷贝运算
    };

    // 禁止拷贝类的其它实现
    class noncopyable1 {
      protected:
        noncopyable1() = default;
        ~noncopyable1() = default;
        noncopyable1(const noncopyable1 &) = delete;
        const noncopyable1 &operator=(const noncopyable1 &) = delete;
    };

    class do_not_copy : noncopyable1 {};
    do_not_copy d1;
    // do_not_copy d2(d1); // 编译出错，不允许拷贝
    do_not_copy d3;
    // d3 = d1; // 企图拷贝构造，不被允许
}

int main() {
    test1();
    test2();
    return 0;
}