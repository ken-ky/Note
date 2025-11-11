#include <boost/date_time/date_clock_device.hpp>
#include <iostream>
using namespace std;

// 处理日期组件
#include <boost/date_time/gregorian/greg_date.hpp>
#include <boost/date_time/gregorian/parsers.hpp>
#include <boost/date_time/special_defs.hpp>
using namespace boost::gregorian;

// 处理时间组件
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost;

class credit_card {
  public:
    string bank_name; // 银行名
    int bill_day_no;  // 记账日
    credit_card(const char *bname, int no)
        : // 构造函数
          bank_name(bname), bill_day_no(no) {}

    int calc_free_days(date consume_day = day_clock::local_day()) const;

    friend bool operator<(const credit_card &l, const credit_card &r) {
        return l.calc_free_days() < r.calc_free_days(); // 比较免息期
    }
};

int credit_card::calc_free_days(date consume_day) const {
    date bill_day(consume_day.year(), consume_day.month(),
                  bill_day_no); // 得到记账日

    if (consume_day > bill_day) {
        bill_day += months(1);
    }
    return (bill_day - consume_day).days() + 20;
}

int main() {
    credit_card a("A bank", 25); // A银行的记账日是每月的25日
    credit_card b("B bank", 12); // B银行的记账日是每月的12号
    return 0;
}