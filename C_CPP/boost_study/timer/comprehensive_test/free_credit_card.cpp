#include <boost/date_time/date_clock_device.hpp>
#include <iostream>
using namespace std;

// 处理日期组件
#include <boost/date_time/gregorian/greg_date.hpp>
#include <boost/date_time/gregorian/parsers.hpp>
#include <boost/date_time/special_defs.hpp>

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
};