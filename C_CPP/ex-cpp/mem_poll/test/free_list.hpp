#include <cstddef>

// 内存块信息表
template <typename T> struct memoryblock {
    int nsize;              // 该内存的大小
    int nfree;              // 剩余可分配的单位
    int nfirst;             // 当前可分配的第一个单位序号
    memoryblock *next;      // 下一个内存块
    unsigned char adata[1]; // 用于标记分配单元开始的位置

    memoryblock(int n_unit_size, int n_unit_amount);

    void *operator new(std::size_t, int nUnitSize, int nUnitAmount);
    void operator delete(void *pblock);
};

// 链表头memorypool
template <typename T> struct memorypool {
    int n_init_size;           // 首块长度
    int n_grow_size;           // 后续块长度
    int n_unit_size;           // 定义存储单位大小
    memoryblock<T> *block_ptr; // 指向内存块链表的指针

    memorypool(int nGrowSize = 10, int nInitSize = 3);
    ~memorypool();

    void *allocate(size_t num);
};