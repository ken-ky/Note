#include <functional>
#include <iostream>
#include <memory>

using namespace std;

/* unique_ptr的使用 */
void test1() {
    unique_ptr<int> uptr = make_unique<int>(200);
    cout << "test1:\tuptr-" << uptr.get() << ": " << *uptr << "\r" << endl;
}

void test2() {
    unique_ptr<int> uptr = make_unique<int>(200);
    // unique_ptr<int> uptr1 = uptr;   // 编译错误
    unique_ptr<int> uptr2 = move(uptr); // 转移了所有权，到uptr2上【勘误这里】
    cout << "test2:\tuptr2-" << uptr2.get() << ": " << *uptr2 << "\r" << endl;
}

void test3() {
    cout << "test3:\t";
    unique_ptr<int[]> uptr = make_unique<int[]>(10);
    for (int i = 0; i < 10; i++) {
        uptr[i] = i * i;
    }
    for (int i = 0; i < 10; i++) {
        cout << uptr[i] << " ";
    }
    cout << endl;
}

void test4() {
    struct FileCloser {
        void operator()(FILE *fp) const {
            if (fp != nullptr) {
                fclose(fp);
            }
        }
    };
    unique_ptr<FILE, FileCloser> uptr(fopen("test_file.txt", "w"));
    /* 构造阶段 */
    // fopen() 打开文件，返回了FILE*指针
    // unique_ptr 的构造函数接管此指针，之后封装在uptr中

    /* 析构阶段 */
    // 结束 test4() 作用域时，uptr的析构函数被调用
    // 析构函数又调用 FileCloser::operator()
}

void test5() {
    unique_ptr<FILE, function<void(FILE *)>> uptr(
        fopen("test_file.txt", "w"),
        [](FILE *fp) { // 这个构造方法分别对应了构造时机与析构时机
            fclose(fp);
        });
}

int main() {
    test1(); // 创建智能指针
    test2();
    test3(); // 指向数组
    test4(); // 自定义deleter
    test5(); // 嵌套lambda表达式
    return 0;
}