#include <memory>

using namespace std;

class Singleton {
  private:
    Singleton() {}
    static weak_ptr<Singleton> m_instance;

  public:
    static shared_ptr<Singleton> getInstance() {
        shared_ptr<Singleton> instance = m_instance.lock();
        if (!instance) {
            instance.reset(new Singleton());
            m_instance = instance;
        }
        return instance;
    }
};

weak_ptr<Singleton> Singleton::m_instance;

int main() {
    // 这个例子实现了单例模式的优点
    // 1.避免循环应用：避免了内存泄漏。
    // 2.访问控制：可以访问对象，但是不会延长对象的生命周期。
    // 3.可以在单例对象不被使用时，自动释放对象。
    return 0;
}