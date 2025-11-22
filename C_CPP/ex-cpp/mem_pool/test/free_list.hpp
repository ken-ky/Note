#pragma once

#include <cstdint>
#include <iostream>

using std::cout;
using std::endl;

/* 内存块 */
// 内存块管理表
template <typename T> struct MemoryBlock {
    int nsize; // 内存块大小
    int nfree; // 剩余空闲块

    int nfirst; // 当前可分配的第一序号

    unsigned char adata[1]; // 标记分配单位开始的位置
    MemoryBlock *next;      // 下一块内存块

    MemoryBlock(int nUnitSize, int nUnitAmount)
        : nsize(nUnitSize * nUnitAmount), nfree(nUnitAmount) {
        nfirst = 1; // 第一个可分配的序号为1

        // unsigned char *pdata = adata; // 首地址所在
        // for (int i = 1; i < nUnitAmount; i++) {
        //     pdata += nUnitSize; //
        //     每次向后延申nUnitSize便是对应存储空间首地址
        // }
    }

    void *operator new(size_t, int nUnitSize, int nUnitAmount);

    void operator delete(void *pblock);
};

template <typename T>
void *MemoryBlock<T>::operator new(size_t, int nUnitSize, int nUnitAmount) {
    // 这里主要新分配大小：内存块管理表+存储区
    return ::operator new(sizeof(MemoryBlock) + nUnitSize * nUnitAmount);
}

template <typename T> void MemoryBlock<T>::operator delete(void *pblock) {
    return ::operator delete(pblock);
}

/* 内存池 */
#define MEMPOOL_ALIGNMENT 8

// 内存池管理表
template <typename T> struct MemoryPool {
    int nInitSize;            // 首块长度
    int nGrowSize;            // 可扩展长度
    int nUnitSize;            // 存储单位大小
    MemoryBlock<T> *memBlock; // 链表头的内存块

    MemoryPool(int nISize = 3, int nGSize = 10)
        : nInitSize(nISize), nGrowSize(nGSize) {
        memBlock = nullptr;
        nUnitSize = sizeof(T);

        if (nUnitSize > 4) {
            // 对齐操作，返回8的倍数
            nUnitSize = (sizeof(T) + (MEMPOOL_ALIGNMENT - 1) &
                         ~(MEMPOOL_ALIGNMENT - 1));
        } else if (nUnitSize < 2) {
            nUnitSize = 2;
        } else {
            nUnitSize = 4;
        }
    }

    ~MemoryPool() { // [修改过]
        MemoryBlock<T> *blockPtr = memBlock;
        while (blockPtr != nullptr) {
            blockPtr = blockPtr->next;
            delete (blockPtr);
        }
        delete memBlock;
    }

    void *allocate(size_t num);
    void free(void *pfree);
};

template <typename T> void *MemoryPool<T>::allocate(size_t num) {
    return nullptr;
}

template <typename T> void MemoryPool<T>::free(void *pfree) {}