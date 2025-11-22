#include "free_list.hpp"

class user {
    int s;
    double s1;
    double s3;

  public:
    user(int x) : s(x) {
        cout << endl << "--------调用 user 构造函数--------" << endl;
    }

    int get() { return s; }

    ~user() { cout << endl << "--------调用 user 析构函数--------" << endl; }
};

void block_test() {
    cout << "------------内存块测试------------" << endl;

    int num = 3;

    // 分配对象测试
    cout << "-----------分配对象测试-----------" << endl;
    MemoryBlock<user> *block =
        new (sizeof(user), num) MemoryBlock<user>(sizeof(user), num);

    /* 等同于下述分配方式 */
    // void *memory = MemoryBlock<user>::operator new(sizeof(MemoryBlock<user>),
    //                                                sizeof(user), 3);
    // 使用new的空间作为user
    // MemoryBlock<user> *block =
    //     new (sizeof(user), 3) MemoryBlock<user>(sizeof(user), 3);

    cout << "内存块大小: " << block->nsize << " 字节" << endl;
    cout << "剩余空闲块: " << block->nfree << endl;
    cout << "第一个可分配序号: " << block->nfirst << endl;

    // 在MemoryBlock中构造user对象
    cout << "-----------构造对象测试-----------" << endl;
    cout << "id\taddress\t\tval" << endl;
    for (int i = 0; i < num; i++) {
        void *mem = static_cast<void *>(block->adata + i * sizeof(user));
        user *tmp = new (mem) user(i * 100);
        cout << i << "\t" << tmp << "\t" << tmp->get() << endl;
    }

    // 释放内存块
    delete block;
    cout << "-----------测试内容完成-----------" << endl;
}

int main() {
    block_test();
    return 0;
}