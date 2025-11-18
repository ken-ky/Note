#include <iostream>
#include <memory>

using namespace std;

class sample {
  private:
    class impl;         // 不完整的内部类声明
    shared_ptr<impl> p; // shared_ptr成员变量

  public:
    sample();
    void print();
};

class sample::impl { // 内部类的实现
  public:
    void print() { cout << "impl print" << endl; }
};

sample::sample() : p(new impl) {}

void sample::print() { // 调用pimpl实现print()
    p->print();
}

int main() {
    sample s;
    s.print();
}