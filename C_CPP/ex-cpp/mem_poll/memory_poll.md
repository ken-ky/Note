### 内存池
+ 参考链接：
  + [内存池（Memory Pool）详解和完整示例](https://blog.csdn.net/qq_36812406/article/details/150490286)
  + [万字详解C++内存池：提高内存分配效率的利器](https://www.cnblogs.com/blizzard8204/p/17804694.html)
  + [手把手教你实现C++高性能内存池，相比 malloc 性能提升7倍！](https://segmentfault.com/a/1190000047269811)
<br>

#### 什么是内存池
+ 内存池（Memory Poll/Poll Allocator）：是一种内存管理机制，提前向系统申请一大块内存，再在这块内存里切分、分配和回收
+ 相当于在用户空间建立了一层“**小型堆管理器**”，避免频繁分配管理系统空间
<br>

#### 内存池的基本设计

##### 数据结构
+ 大块（Chunk）：一次从系统申请的大内存，比如1MB
+ 小块（Block）：Chunk中切分的固定大小单位，比如64字节
+ 空闲链表（Free List）：回收的块串成的单链表，下次分配直接取链表头
```plain-text
[Chunk1: 64B|64B|64B|64B|...] -> FreeList
[Chunk2: 64B|64B|64B|64B|...] -> FreeList
```
<br>

##### 分配流程
+ 时间复杂度 $\Omicron(1)$
1. 申请时，先看`FreeList`是否有空闲块
2. 有`->`直接返回`FreeList`头部
3. 没有`->`，就新申请一个`Chunk`，把其中的块串起来，返回其中一个
<br>

##### 释放流程
+ 时间复杂度 $\Omicron(1)$
1. 将释放的块头插回`FreeList`
<br>

#### 内存池分类
+ **固定大小内存池**（Fixed-size Memory Poll）
  + 每次分配固定大小的对象，比如链表节点、树节点、点云点
  + 常用方法：空闲链表（Free List）
  + 优点：简单高效、零碎片
+ **可变大小内存池**（Variable-size Memory Pool）
  + 允许不同大小的分配，但通常会限制在某些对齐粒度（如8字节对齐）
  + 常见算法：
    + Slab Allocator（`Linux`内核）
    + Buddy System（伙伴系统）
    + RCMalloc/Jemalloc（现代高性能内存分配器）
<br>

#### 内存池实现关键点
实现一个高效、安全的内存池（特别是固定大小对象池），核心就在于**数据结构的选择、边界处理、并发与可扩展性**。
<br>
