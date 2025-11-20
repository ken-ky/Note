#include "free_list.hpp"
#include <iostream>
#include <new>

using namespace std;

/* memoryblock 方法定义 */
// 内存块的构造函数
template <typename T>
memoryblock<T>::memoryblock(int n_unit_size, int n_unit_amount) {
    // n_unit_size每个存储单位大小，n_unit_amount为内存块规模（数量）
    // nfree空闲单位存储单位为n_unit_amount-1块，
    // nfirst初值为1，pnext指向的下一内存块为NULL

    // 为空闲区编号
    unsigned char *ppdata = adata;
    cout << "存储区首指针 ppdata=" << (int *)ppdata << endl;
    for (int i = 1; i < n_unit_amount; i++) {
        // 当前存储单位存储下一个可分配单位的序号
        (*(unsigned short *)ppdata) = i;
        cout << "下一个可分配序号：" << (int)*ppdata << endl;
        ppdata += n_unit_size;
    }
    cout << "-------------调用内存块的构造函数-------------------" << endl;
}

// 重载new运算符
template <typename T>
void *memoryblock<T>::operator new(std::size_t, int nUnitSize,
                                   int nUnitAmount) {
    cout << "分配内存并创建 memoryblock 对象" << endl;
    return ::operator new(sizeof(memoryblock) +
                          nUnitSize *
                              nUnitAmount); // 内存空间长度为表对象+存储空间
}

// 重载delete运算符进行析构
template <typename T> void memoryblock<T>::operator delete(void *pblock) {
    ::operator delete(pblock);
    cout << "---------------调用内存块的析构函数----------------" << endl;
}

/* memorypool 方法定义 */
#define MEMPOOL_ALIGNMENT 4

// memorypool构造函数
template <typename T> memorypool<T>::memorypool(int nGrowSize, int nInitSize) {
    cout << "-----------------调用内存池的构造函数---------------" << endl;

    n_init_size = nInitSize; // 首块长度
    n_grow_size = nGrowSize; // 后续块长度

    block_ptr = nullptr;     // 指针置空
    n_unit_size = sizeof(T); // 定义存储块大小

    if (sizeof(T) > 4) { // 调整存储单位大小
        // 返回值为8的倍数 所谓的内存对齐
        n_unit_size =
            (sizeof(T) + (MEMPOOL_ALIGNMENT - 1) & ~(MEMPOOL_ALIGNMENT - 1));
    } else if (sizeof(T) < 2) {
        n_unit_size = 2;
    } else {
        n_unit_size = 4;
    }
}

// memorypool析构函数
template <typename T> memorypool<T>::~memorypool() {
    memoryblock<T> *my_block_p = block_ptr->next;
    while (my_block_p != nullptr) {
        delete my_block_p;
        my_block_p = block_ptr;
        block_ptr = my_block_p->next;
    }
    cout << "---------------调用内存池的析构函数----------------" << endl;
}

// 请求存储单位的函数
template <typename T> void *memorypool<T>::allocate(size_t num) {
    for (int i = 0; i < num; i++) {
        if (block_ptr == nullptr) {
            // 创建首内存块
            block_ptr = (memoryblock<T> *)new (n_unit_size, n_init_size)
                memoryblock<T>(n_unit_size, n_init_size);
            return (void *)block_ptr->adata;
        }

        // 为内存寻找符合条件的内存块
        memoryblock<T> *my_block_p = block_ptr;
        while (my_block_p != nullptr && my_block_p->nfree == 0) {
            // 链未寻访完成，且剩余空闲数为0
            my_block_p = my_block_p->next;
        }

        if (my_block_p != nullptr) {
            cout << "找到内存空间 first=" << my_block_p->nfirst << endl;

            // 进行内存分配
            unsigned char *pfree =
                my_block_p->adata + my_block_p->nfirst * n_unit_size;
            my_block_p->nfirst = *((unsigned short *)pfree);
            my_block_p->nfree--;

            // 返回找到的存储单位指针
            return (void *)pfree;
        } else {
            // 当前内存块已经使用完
            if (n_grow_size == 0) { // 不能继续扩展空间
                return nullptr;
            }

            // 分配后续内存块
            cout << "扩展新内存块" << endl;

            my_block_p = (memoryblock<T> *)new (n_unit_size, n_grow_size)
                memoryblock<T>(n_unit_size, n_grow_size);
            if (my_block_p == nullptr) { // 分配失败
                return nullptr;
            }

            my_block_p->next = block_ptr;
            block_ptr = my_block_p;
            return (void *)my_block_p->adata;
        }
    }
}