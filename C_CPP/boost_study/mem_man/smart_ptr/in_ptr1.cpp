#include <boost/smart_ptr/intrusive_ptr.hpp>

using namespace std;

struct counted_data {
    int m_count; //  引用计数
    int *data;

    counted_data() : data(new int(-1)), m_count(0) {}
    counted_data(int x) : data(new int(x)), m_count(0) {}
    ~counted_data() {
        m_count = 0;
        delete data;
    }
};

void intrusive_ptr_add_ref(counted_data *p) { // 增加引用计数
    ++p->m_count;
}

void intrusive_ptr_release(counted_data *p) { // 减少引用计数
    if (--p->m_count == 0) {                  // 引用计数为0则删除指针
        delete p;
    }
}

int main() {
    typedef boost::intrusive_ptr<counted_data> counted_ptr; // 类型定义
    counted_ptr p(new counted_data); // 创建智能指针
    assert(p);                       // bool转型
    assert(p->m_count == 1);         // operator->

    counted_ptr p2(p);       // 指针拷贝构造
    assert(p->m_count == 2); // 引用计数增加

    counted_ptr weak_p(p.get(), false); // 弱引用
    assert(weak_p->m_count == 2);       // 引用计数不增加

    p2.reset();              // 复位指针
    assert(!p2);             // p2不持有指针
    assert(p->m_count == 1); // 引用计数减少
    return 0;
}