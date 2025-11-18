#include <iostream>
#include <memory>

using namespace std;

class abstract { // 接口类
  protected:     // 基类为保护态，用户无法做出任何破坏行为
    virtual ~abstract() = default; // 注意这里

  public:
    virtual void f() = 0;
    virtual void g() = 0;
};

class impl : public abstract {
  public:
    impl() = default;
    virtual ~impl() = default;

  public:
    virtual void f() { cout << "class impl f" << endl; }
    virtual void g() { cout << "class impl g" << endl; }
};

shared_ptr<abstract> create() { return make_shared<impl>(); }

int main() {
    auto p = create(); // 工厂函数创建对象
    p->f();
    p->g();
}