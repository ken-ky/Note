#include <boost/date_time/posix_time/ptime.hpp>
#include <iostream>
using namespace std;

#include <boost/date_time/gregorian/greg_date.hpp>
#include <boost/date_time/microsec_time_clock.hpp>
#include <boost/date_time/special_defs.hpp>
using namespace boost::gregorian;

#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost::posix_time;

template <typename Clock = microsec_clock> class basic_ptimer {
  public:
    basic_ptimer() { // 初始化开始时间
        restart();
    }

    void restart() { // 重新开始计时
        _start_time = Clock::local_time();
    }

    void elapsed() const { // 计量流逝时间
        cout << Clock::local_time() - _start_time << endl;
    }

    ~basic_ptimer() { // 析构函数自动输出时间
        elapsed();
    }

  private:
    ptime _start_time; // 保存计时开始时间
};

typedef basic_ptimer<microsec_clock> ptimer;
typedef basic_ptimer<second_clock> sptimer;

int main() {
    ptimer t;
    sleep(20);
    return 0;
}