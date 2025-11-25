#pragma once

#include <cstdint>
#include <iostream>

using std::cout;
using std::endl;

/* 内存块 */
// 内存块信息表
template <typename T> struct MemoryBlock {
    int nsize; // 内存块大小
    int nfree; // 剩余空闲块

    int nfirst; // 当前可分配的第一序号

    unsigned char adata[1]; // 标记分配区域开始的位置
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
    int nInitSize;            // 首块长度【基本分配单位长度】
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
    for (int i = 0; i < num; i++) {
        if (memBlock == nullptr) { // 为块管理信息表分配空间
            memBlock = (MemoryBlock<T> *)new (nUnitSize, nInitSize)
                MemoryBlock<T>(nUnitSize, nInitSize);
            return (void *)memBlock->adata;
        }

        // 寻找符合要求的内存块【第一个有剩余块的】
        MemoryBlock<T> *blockPtr = memBlock;
        while (blockPtr != nullptr && blockPtr->nfree == 0) {
            blockPtr = blockPtr->next;
        }

        if (blockPtr != nullptr) {
            // 进行内存分配
            unsigned char *pfree =
                blockPtr->adata + blockPtr->nfirst * nUnitSize;
            blockPtr->nfirst = *((unsigned char *)pfree); // 改变空闲块的首地址
            blockPtr->nfree--;                            // 分配了一块

            return (void *)pfree;
        } else {
            if (nGrowSize == 0) { // 无法继续扩展
                return nullptr;
            }

            // 分配后续内存块
            blockPtr = (MemoryBlock<T> *)new (nUnitSize, nGrowSize)
                MemoryBlock<T>(nUnitSize, nGrowSize);
            if (blockPtr == nullptr) { // 扩展空间失败
                return nullptr;
            }

            blockPtr->next = memBlock; // 倒插到队首
            memBlock = blockPtr;
            return (void *)blockPtr->adata;
        }
    }
    return nullptr;
}

template <typename T> void MemoryPool<T>::free(void *pfree) {
    MemoryBlock<T> *blockPtr = memBlock;
    MemoryBlock<T> *preBlock = nullptr;

    // [修改过]
    // 寻找到需要删除块前的指针
    while (blockPtr != nullptr && (blockPtr->adata > pfree ||
                                   blockPtr->adata + blockPtr->nsize > pfree)) {
        preBlock = blockPtr;
        blockPtr = blockPtr->next;
    }

    // 该内存块在内存池 blockPtr 所指向的内存池中
    if (blockPtr != nullptr) {
        // 1.修改内存块链表
        *((unsigned short *)pfree) =
            blockPtr->nfirst; // 这一内存块的第一可分配地址
        blockPtr->nfirst = (unsigned short)((unsigned long)pfree -
                                            (unsigned long)blockPtr->adata) /
                           nInitSize; // 这个块相当于1多少的nInitSize
        blockPtr->nfree++;            // 空闲内存块递增

        // 2.当该内存块中的空闲资源数与分配空间相等时，释放内存
        if (blockPtr->nsize == blockPtr->nfree * nUnitSize) {
            delete (blockPtr);
        } else {
            // 将block的前一内存块链至内存池头
            preBlock = blockPtr->next;
            blockPtr->next = blockPtr;
            memBlock = blockPtr;
        }
    }
}