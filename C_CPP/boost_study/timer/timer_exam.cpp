#include <boost/timer/timer.hpp>
#include <iostream>

using namespace boost;
using namespace std;

int main() {
    timer::cpu_timer t;
    t.start();
    for (int i = 0; i != 3000; i++) {
        void();
    }
    t.stop();
    cout << t.format(); // 以默认6精度输出经过时间、用户时间和系统时间

    if (t.is_stopped()) {
        cout << "After stop() but before resume()" << endl;
    } else {
        cout << endl;
    }

    for (int i = 0; i != 200; i++) {
        if (i == 150) {
            cout << t.elapsed().wall << endl; // start()至调用此函数的经过时间
            cout << t.elapsed().user << endl; // start()至调用此函数的用户时间
            cout << t.elapsed().system << endl; // start()至调用此函数的系统时间
        }
    }
    t.stop();
    cout << t.format(3, "%w"); // 以3精度输出经过时间
    return 0;
}
