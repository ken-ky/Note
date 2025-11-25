#pragma once

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <memory>

using std::cout;
using std::endl;

using std::shared_ptr;
using std::weak_ptr;

/* 内存块 */
// 内存信息表
template <typename T> struct MemoryBlock {
    int nsize;
    int nfree;

    int nfirst;

    unsigned char adata[1];
    weak_ptr<MemoryBlock<T>> next;

    MemoryBlock(int nUnitSize, int nUnitAmount)
        : nsize(nUnitSize * nUnitAmount), nfree(nUnitAmount) {
        nfirst = 1;
    }

    void *operator new(size_t, int nUnitSize, int nUnitAmount);

    void operator delete(void *pblock);
};

template <typename T>
void *MemoryBlock<T>::operator new(size_t, int nUnitSize, int nUnitAmount) {
    return ::operator new(sizeof(MemoryBlock) + nUnitSize * nUnitAmount);
}