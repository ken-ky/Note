#include <iostream>
using namespace std;

#include <boost/date_time/gregorian/greg_date.hpp>
using namespace boost::gregorian;

#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost::posix_time;

days operator"" _D(unsigned long long n) { // 后缀_D，返回天
    return days(n);
}

weeks operator"" _W(unsigned long long n) { // 后缀_W，返回周
    return weeks(n);
}

date operator"" _YMD(const char *s, size_t) { // 年、月、日格式，返回日期
    return from_string(s);
}

int main() {
    auto d = 100_D; // 100 days
    auto w = 1_W;   // a week

    assert(d.days() == 100);
    assert(w.days() == (7_D).days()); // 可以直接用字面值变量

    auto today = "2014/11/3"_YMD; // 将字符串转换为日期
    cout << today << endl;
    return 0;
}