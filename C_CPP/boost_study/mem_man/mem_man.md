### 内存管理

#### smart_ptr库概要

##### RAII机制
+ RAII机制（`Resource Acquisition is Initialization`，资源获取即初始化）：在类的构造函数里申请资源，然后使用资源，最终在析构函数中释放资源
+ 两种内存分配方式：
  + 对象是用声明的方式在栈上创建（一个局部对象），那么`RAII`机制会正常工作，离开作用域时，该对象会自动销毁，从而调用析构函数释放资源
  + 但如果对象是用`new`（或`malloc`）在堆上创建的，**那么它的析构函数无法自动调用**，需要对应调用`delete`（或`free`）销毁，才能释放资源
<br>

##### 智能指针（smart pointer）
+ 智能指针：智能指针可以在退出作用域时（无论是正常流程还是因异常而离开）总调用`delete`来析构在堆上动态分配的对象
  + `auto_ptr`：最早的智能指针，见于`C++98`，解决了自动释放获取资源的部分问题
    ```c++
    {
        auto_ptr<class_name> p1(new class_name);
        
        auto_ptr<demo_class> p2(factory.create());
    }   // 离开作用域，p1 和 p2 自动析构
    ```
    + 实际上`auto_ptr`是个对象，但是由于其重载了`operator*`和`operator->`，行为类似指针，因此可以将其使用在大多数普通指针可用的地方
    + 但`auto_ptr`存在缺陷，所以新的 C++ 标准提供了更完善的`unique_ptr`、`shared_ptr`和`weak_ptr`【[具体内容](https://blog.csdn.net/Dasis/article/details/121663794)】
      + 不能有两个`auto_ptr`对象拥有同一个内部指针的所有权，因为有可能在某个时机，两者均会尝试析构这个内部指针
      + 两个`auto_ptr`对象发生赋值操作时，右者对象会丧失该所有权
  + C++ 标准提供了更完善的智能指针，这些指针都基于`boost.smart_ptr`库，参考【[一文读懂智能指针](https://zhuanlan.zhihu.com/p/150555165)、[万字长文详解智能指针](https://zhuanlan.zhihu.com/p/672745555)】
    + 这些指针位于`<boost/smart_ptr.hpp>`，并且都是异常安全的（`exception safe`）
      + `unique_ptr`
      + `shared_ptr`
      + `weak_ptr`
      这些指针内容在`../../ex-cpp/smart_ptr`中会有更详细的内容
    + 另外还有以下智能指针类型：
      + `scoped_ptr`
      + `intrusive-ptr`
<br>

##### `scoped_ptr`
+ `scoped_ptr`与`auto_ptr/unique_ptr`类似，它包装了`new`操作符在堆上分配的动态对象，能够保证动态创建的对象在任何时候都可以被正确地删除。
+ 但是`scoped_ptr`的所有权更严格，**无法转让，甚至无法收回**
+ 标准容器也无法容纳管理`scoped_ptr`
<br>

###### 操作函数
|成员函数|描述|备注|
|---|---|---|
|`scoped_ptr(T* p)`|构造函数|`p`必须是由`new`操作符分配空间|
|`reset(T* p=0)`|重置|删除原本保存的指针，更新新指针`p`|
|`get()`|——|可以返回原指针内容|
+ 外部函数：
  + `swap()`可以交换两个`scoped_ptr`的原始指针
  + `scoped_ptr`支持有限的比较（是否相等）
+ 特殊部分：
  + `reset(T* p)`中，若`p=nullptr`，那么`scoped_ptr`不持有任何指针
  + 若`scoped_ptr`保存了空指针，那么重载的`*`与`()`都会认为未定义
  + `scoped_ptr`可以自动转换为`bool`，用于判断是否持有有效指针（非空）
  + `scoped_ptr`将拷贝构造函数和赋值函数都声明为私有，保证指针绝对安全
<br>

##### `intrusive_ptr`
+ `intrusive_ptr`也是一种引用计数型智能指针
  + 实际上它并不一定要“侵入”代理对象的内部修改数据
  + 如果现存代码已经有了引用计数机制管理的对象，那么`intrusive_ptr`是一个非常好的选择
  + 它可以包装已有对象从而得到`shared_ptr`类似的智能指针
<br>

###### 用法
+ 调用以下两个函数来**间接管理**引用计数：
  ```cpp
  void intrusive_ptr_add_ref(T* p); // 增加引用计数
  void intrusive_ptr_release(T* p); // 减少引用计数
  ```
  + `instrusive_ptr_release()`函数中必须检查引用计数，因为`instrusive_ptr`不负责销毁实例
+ 包装已有类：引入头文件`<boost/smart_ptr/intrusive_ptr.hpp>`
  + 假设已经实现了引用计数类
  + 为了让`instrusive_ptr`正常工作，需要实现它要求的两个回调函数：
    + `void instrusive_ptr_add_ref(counted_data* p)`增加引用计数
    + `void intrusive_ptr_release(counted_data* p)`减少引用计数
+ 引用计数器：为了简化引用计数的工作，在头文件`<boost/smart_ptr/intrusive_ref_counter.hpp>`定义了一个辅助类`intrusive_ref_counter`
<br>

#### `pool` 库概要
+ `boost.pool`库基于简单分隔存储的思想实现了一个快速、紧凑的内存池库，不仅可以管理大量的对象，还可以用作STL的内存分配器
+ `pool`库包含4个组成部分：最简单的`pool`、分配类实例的`object_pool`、单件内存池`singleton_pool`和可用于标准库的`pool_alloc`【最后一个组件详见`ex-cpp`】
<br>

##### `pool`
+ `pool`池只能分配一些基本类型的对象，比如：`int`、`double`等
+ `pool`模板类型参数`UserAllocator`是一个用户定义的内存分配器
  + 通常可以直接用默认的`default_user_allocator_new_delete`，它使用`new []`和`delete []`分配内存
<br>

###### 操作函数
+ 构造函数：`pool`的构造函数可以接收`size_t`类型的整数，代表每次分配内存块的大小（而非内存池大小）
  ```c++
  pool<> p(sizeof(int));
  ```
+ 分配函数：
  + `malloc(void*)`：用`void*`指针返回内存池中分配的内存块，大小为之前指定的内存块大小
  + `ordered_malloc(void*, size_t)`：所带的参数表示连续分配的n块内存，分配时会合并空闲块链表
+ 释放块函数：与`malloc`操作基本对应
  + `free(void*)`：释放指向的内存块
  + `ordered_free(void*, size_t)`：释放指向的连续内存
+ `is_from()`：测试分配后的内存块是否从属于某一内存池
  ```c++
  p.is_from(p1);  // p1是否来自p
  ```
+ 释放内存函数：
  + `release_memory()`：让内存池释放所有未被分配的内存
  + `purge_memory()`：强制释放`pool`持有的所有内存【`pool`析构函数就是使用这一函数实现】
<br>

##### `object_pool`