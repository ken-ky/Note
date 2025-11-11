#include <iostream>
using namespace std;

// 处理日期的组件
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/gregorian/parsers.hpp>
#include <boost/date_time/special_defs.hpp>
using namespace boost::gregorian;

// 处理时间组件
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost::posix_time;

int main() {
    date d(2017, 1, 23);

    date d_start(d.year(), d.month(), 1);
    date d_end = d.end_of_month();

    for (day_iterator d_iter(d_start); d_iter != d_end; ++d_iter) {
        cout << *d_iter << " " << d_iter->day_of_week() << endl;
    }
    return 0;
}