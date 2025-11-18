#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class IObserver {
  public:
    virtual void update(const string &msg) = 0;
};

class Subject {
  private:
    vector<shared_ptr<IObserver>> observes_;

  public:
    void attach(const shared_ptr<IObserver> &observer) {
        observes_.emplace_back(observer);
    }

    void detach(const shared_ptr<IObserver> &observer) {
        observes_.erase(remove(observes_.begin(), observes_.end(), observer),
                        observes_.end());
    }

    void notify(const string &msg) {
        for (auto &observer : observes_) {
            observer->update(msg);
        }
    }
};

class ConcreteObserver : public IObserver {
  private:
    shared_ptr<Subject> Subject_;

  public:
    ConcreteObserver(const shared_ptr<Subject> &Subject) : Subject_(Subject) {}
    void update(const string &msg) override {
        cout << "ConcreteObserver " << msg << endl;
    }
};

int main() {
    shared_ptr<Subject> subject = make_shared<Subject>();
    shared_ptr<IObserver> observer = make_shared<ConcreteObserver>(subject);
    subject->attach(observer);
    subject->notify("update");
    return 0;
}