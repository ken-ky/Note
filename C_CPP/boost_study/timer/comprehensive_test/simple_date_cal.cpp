#include <boost/date_time/gregorian/greg_calendar.hpp>
#include <iostream>
using namespace std;

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/gregorian/parsers.hpp>
#include <boost/date_time/special_defs.hpp>
using namespace boost::gregorian;

#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost::posix_time;

typedef gregorian_calendar gre_cal;

int main() {
    date d(2017, 1, 23);

    date d18years = d + years(18);
    cout << d18years << " is " << d18years.day_of_week() << endl;

    int cnt = 0; // 星期天的计数器
    for (day_iterator d_iter(date(d18years.year(), 1, 1));
         d_iter != d18years.end_of_month(); ++d_iter) {
        if (d_iter->day_of_week() == Sunday) {
            ++cnt;
        }
    }
    cout << "total " << cnt << " Sundays." << endl;

    cnt = 0;
    for (month_iterator m_iter(date(d18years.year(), 1, 1));
         m_iter < date(d18years.year() + 1, 1, 1); ++m_iter) {
        cnt += m_iter->end_of_month().day();
    }
    cout << "total " << cnt << " days of year." << endl;

    cout << "total " << (gre_cal::is_leap_year(d18years.year()) ? 366 : 355)
         << " days of year." << endl;
    return 0;
}