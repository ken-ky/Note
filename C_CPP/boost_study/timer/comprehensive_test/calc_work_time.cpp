#include <boost/date_time/date_clock_device.hpp>
#include <iostream>
#include <map>
using namespace std;

#include <boost/date_time/gregorian/greg_date.hpp>
using namespace boost::gregorian;

#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost::posix_time;

class work_time {
  public:
    typedef map<time_period, string> map_t;

  private:
    map_t map_ts;
    void init();

  public:
    work_time() { // 构造函数调用init()初始化
        init();
    }

    void greeting(const ptime &t); // 消息输出函数
};

void work_time::init() {
    ptime p(day_clock::local_day()); // 获得当天的日期和零点
    map_ts[time_period(p, hours(9))] = "It\'s too early, just relax.\n";

    p += hours(9);
    map_ts[time_period(p, hours(3) + minutes(30))] =
        "It\'s AM, please work hard.\n";

    p += hours(3) + minutes(30);
    map_ts[time_period(p, hours(1))] = "It\'s lunch time, are you hungry?\n";

    p += hours(1);
    map_ts[time_period(p, hours(4) + minutes(30))] =
        "It\'s PM, please work hard.\n";

    p += hours(4) + minutes(30);
    map_ts[time_period(p, hours(6))] =
        "Are you still working? You do need a rest.\n";
}

void work_time::greeting(const ptime &t) {
    for (auto &x : map_ts) {
        if (x.first.contains(t)) {
            cout << x.second;
            return;
        }
    }

    cout << "Oh, this is a bug!" << endl;
}

int main() {
    work_time wt;
    wt.greeting(second_clock::local_time());
    return 0;
}