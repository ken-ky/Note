#include <iostream>
using namespace std;

#include <boost/date_time/gregorian/greg_date.hpp>
#include <boost/date_time/gregorian/parsers.hpp>
#include <boost/date_time/special_defs.hpp>
using namespace boost::gregorian;

#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost::posix_time;

int main() {
    date d(2014, 11, 3);
    date_facet *dfacet = new date_facet("%Y 年 %m 月 % 日"); // 进行格式化

    cout.imbue(locale(cout.getloc(), dfacet));
    cout << d << endl;

    date_facet *tfacet = new time_facet("%Y 年 %m 月 %d 日 %H:%M:%S%F");
    cout.imbue(locale(cout.getloc(), tfacet));
    cout << ptime(d, hours(21) + minutes(50) + millisec(100)) << endl;
    return 0;
}