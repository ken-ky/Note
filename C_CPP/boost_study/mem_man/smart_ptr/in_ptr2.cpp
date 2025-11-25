#include <boost/smart_ptr/intrusive_ptr.hpp>
#include <boost/smart_ptr/intrusive_ref_counter.hpp>
#include <cassert>

using namespace std;

struct counted_data : public boost::intrusive_ref_counter<counted_data> {
    int data;
};

int main() {
    typedef boost::intrusive_ptr<counted_data> counted_ptr; // 类型定义

    counted_ptr p(new counted_data); // 创建智能指针
    assert(p);                       // bool转型
    assert(p->use_count() == 1);     // operator->
    return 0;
}