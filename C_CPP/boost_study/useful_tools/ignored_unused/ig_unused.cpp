#include <boost/core/ignore_unused.hpp>
#include <functional>

using namespace boost;
using std::function;

// 参数使用方法
void test1() {
    function<int(int, int)> func = [&](int x, int y) -> int {
        int i; // 未使用的变量i

        ignore_unused(i, x); // 解除未使用内容警告
        return y;            // 未使用参数x
    };
}

// 模板用法
void test2() {
    typedef int result_type;      // 暂未使用的类型定义
    ignore_unused<result_type>(); // 解除未使用类型警告
}

int main() {
    test1();
    test2();
    return 0;
}