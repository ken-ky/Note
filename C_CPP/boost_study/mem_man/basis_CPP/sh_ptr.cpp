#include <cassert>
#include <iostream>
#include <memory>
using namespace std;

/* shared_ptr的应用 */
void test1() {
    shared_ptr<int> sptr = make_shared<int>(200);
    assert(sptr.use_count() == 1); // 引用计数为 1
    {
        shared_ptr<int> sptr1 = sptr;
        assert(sptr.get() == sptr1.get()); // sptr和sptr1共享资源，引用计数为 2
    }
    assert(sptr.use_count() == 1); // sptr1已经被释放
}

void test2() {
    cout << "test2:\t";
    {
        // C++20 开始支持 make_shared<int[]>
        shared_ptr<int[]> sptr(new int[10]);
        shared_ptr<int[]> sptr1 = make_shared<int[]>(100);

        for (int i = 0; i < 10; i++) {
            sptr[i] = i * i;
        }
        for (int i = 0; i < 10; i++) {
            cout << sptr[i] << " ";
        }
        cout << endl;
    }

    {
        shared_ptr<FILE> sptr(fopen("test_file.txt", "w"), [](FILE *fp) {
            cout << "close " << fp << endl;
            fclose(fp);
        });
    }
}

int main() {
    test1(); // shared_ptr计数的例子
    test2();
    return 0;
}