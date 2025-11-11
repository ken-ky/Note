#include <boost/date_time/gregorian/formatters.hpp>
#include <boost/date_time/gregorian/gregorian_types.hpp>
#include <iostream>
using namespace std;

// 处理日期的组件
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/gregorian/parsers.hpp>
#include <boost/date_time/special_defs.hpp>
using namespace boost::gregorian;

// 处理时间的组件
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost::posix_time;

void test1() {
    date d1;               // 一个无效日期
    date d2(2010, 1, 1);   // 使用数字构造日期
    date d3(2000, Jan, 1); // 使用英文构造
    date d4(d2);           // 支持拷贝

    assert(d1 == date(not_a_date_time)); // 比较一个临时对象
    assert(d2 == d4);
    assert(d3 < d4);
}

void test2() {
    date d1 = from_string("1999-12-31");
    date d2(from_string("2015/1/1"));
    date d3 = from_undelimited_string("20011118");

    cout << "test2: " << day_clock::local_day() << endl
         << day_clock::universal_day() << endl;
}

void test3() {
    date d1(1399, 12, 1); // 超过日期下限
    date d2(10000, 1, 1); // 超过日期上限
    date d3(2017, 2, 29); // 不存在的日期
}

void test4() {
    date d(2017, 6, 1);
    assert(d.year() == 2017);
    assert(d.month() == 6);
    assert(d.day() == 1);

    date::ymd_type ymd = d.year_month_day(); // 可以返回ymd形式
    assert(ymd.year == 2017);
    assert(ymd.month == 6);
    assert(ymd.day == 1);

    cout << d.day_of_week() << endl; // 返回星期几（0为星期天）
    cout << d.day_of_year() << endl; // 返回是一年中的第几天
    assert(d.end_of_month() == date(2017, 6, 30)); // 当月的最后一天

    cout << "test4:\n";
    cout << date(2015, 1, 10).week_number()
         << endl; // 返回date所在是当年第几周（0~53）

    assert(date(pos_infin).is_infinity());         // 是否是无限日期
    assert(date(pos_infin).is_pos_infinity());     // 是否是正无限日期
    assert(date(neg_infin).is_neg_infinity());     // 是否是负无限日期
    assert(date(not_a_date_time).is_not_a_date()); // 是否是无效日期
    assert(date(not_a_date_time).is_special());    // 是否是特殊日期
    assert(!date(2017, 5, 31).is_special());
}

void test5(const char *args) {
    date d(2017, 1, 23);

    cout << "test5:\n";
    cout << to_simple_string(d) << endl;       // 转换为YYYY-mmm-DD格式
    cout << to_iso_string(d) << endl;          // 转换为YYYYMMDD格式
    cout << to_iso_extended_string(d) << endl; // 转换为YYYY-MM-DD
    cout << d << endl;                         // 默认使用YYYY-mmm-DD格式

    date d1(from_simple_string(string(args)));
    cout << d1 << endl;
}

void test6() {
    date d(2017, 5, 20);
    tm t = to_tm(
        d); // 转换tm后，tm_hour/tm_min/tm_sec均置为0，夏令时tm_isdst置为-1
    assert(t.tm_hour == 0 && t.tm_min == 0);
    assert(t.tm_year == 117 && t.tm_mday == 20);

    date d2 = date_from_tm(t);
    assert(d == d2);
}

void test7() {
    days dd1(10), dd2(-100), dd3(255);

    assert(dd1 > dd2 && dd1 < dd3);
}

void test8() {
    days dd1(10), dd2(-100), dd3(255);

    assert(dd1 > dd2 && dd1 < dd3);
    assert(dd1 + dd2 == days(-90));
    assert((dd1 + dd3).days() == 265);
    assert(dd3 / 5 == days(51));
}

void test9() {
    weeks w(3); // 创建weeks对象
    assert(w.days() == 21);

    months m(5); // 5个月
    years y(2);  // 2年

    months m2 = y + m; // 2年+5个月

    // 不同对象的转换
    assert(m2.number_of_months() == 29);
    assert((y * 2).number_of_years() == 4);
}

void test10() {
    cout << "test 10: ";
    date d1(2000, 1, 1), d2(2017, 11, 18);
    cout << d2 - d1 << endl; // 6531 days
    assert(d1 + (d2 - d1) == d2);

    d1 += days(10); // 2000-1-11
    assert(d1.day() == 11);
    d1 += months(2); // 2000-3-11
    assert(d1.month() == 3 && d1.day() == 11);
    d1 -= weeks(1); // 2000-3-04
    assert(d1.day() == 4);

    d2 -= years(10); // 2007-11-18
    assert(d2.year() == d1.year() + 7);
}

void test11() {
    date d1(2017, 1, 1);

    date d2 = d1 + days(pos_infin);
    assert(d2.is_pos_infinity());

    d2 = d1 + days(not_a_date_time);
    assert(d2.is_not_a_date());

    d2 = date(neg_infin);
    days dd = d1 - d2;
    assert(dd.is_special() && !dd.is_negative());
}

void test12() {
    date_period dp1(date(2017, 1, 1), days(20));         // begin(), len()
    date_period dp2(date(2017, 1, 1), date(2016, 1, 1)); // invalid：左大右小
    date_period dp3(date(2017, 3, 1),
                    days(-20)); // invalid：日期长度应大于等于 0
}

void test13() {
    date_period dp(date(2017, 1, 1), days(20));

    assert(!dp.is_null());
    assert(dp.begin().day() == 1);
    assert(dp.last().day() == 20);
    assert(dp.end().day() == 21);
    assert(dp.length().days() == 20);

    // date_period标准输出
    date_period dp1(date(2017, 1, 1), days(20));
    date_period dp2(date(2017, 2, 19), days(10));

    cout << "test13: " << dp1;
    assert(dp1 < dp2);
}

void test14() {
    date_period dp(date(2017, 1, 1), days(20));
    dp.shift(days(3)); // 将日期区间平移3天，长度不变
    assert(dp.begin().day() == 4);
    assert(dp.length().days() == 20);

    dp.expand(days(3)); // 向期间前后同时扩展3天
    assert(dp.begin().day() == 1);
    assert(dp.length().days() == 26);
}

void test15() {
    date_period dp(date(2010, 1, 1), days(20));

    assert(dp.is_after(date(2009, 12, 1))); // 日期区间是否在日期前
    assert(dp.is_before(date(2010, 2, 1))); // 或后
    assert(dp.contains(date(2010, 1, 10))); // 或者为子集

    date_period dp2(date(2010, 1, 5), days(10));
    assert(dp.contains(dp2));

    assert(dp.intersects(dp2));          // 两个区间是否存在交集
    assert(dp.intersection(dp2) == dp2); // 两个区间的交集

    date_period dp3(date(2010, 1, 21), days(5));
    assert(!dp3.intersects(dp2));
    assert(dp3.intersection(dp2).is_null());

    assert(dp.is_adjacent(dp3)); // 两个日期区间是否相邻
    assert(!dp.intersects(dp3));
}

void test16() {
    date_period dp1(date(2010, 1, 1), days(20));
    date_period dp2(date(2010, 1, 5), days(10));
    date_period dp3(date(2010, 2, 1), days(5));
    date_period dp4(date(2010, 1, 15), days(10));

    assert(dp1.contains(dp2) &&
           dp1.merge(dp2) ==
               dp1); // merge()返回两个日期区间的并集（不相邻则返回无效区间）
    assert(!dp1.intersects(dp3) && dp1.merge(dp3).is_null());
    assert(dp1.intersects(dp2) && dp1.merge(dp4).end() == dp4.end());
    assert(dp1.span(dp3).end() == dp3.end()); // 合并两个日期区间以及之间的间隙
}

void test17() {
    date d(2007, 9, 28);
    day_iterator d_iter(d); // 增减步长默认为一天

    assert(d_iter == d);
    ++d_iter; // 递增1天
    assert(d_iter == date(2007, 9, 28));

    year_iterator y_iter(*d_iter, 10); // 增减步长为10年
    assert(y_iter == d + days(1));
    ++y_iter;
    assert(y_iter->year() == 2017);

    day_iterator iter(day_clock::local_day()); // 声明一个日期迭代器
    ++iter;                                    // 使用operator++正确
    // iter += 5;                                 // 错误，编译失败
    // std::advance(iter, 5); // 错误，编译失败
}

int main() {
    /* 处理日期 */
    test1(); // 日期
    test2(); // 创建日期对象
    // test3(); //
    test4();                              // 访问日期
    test5(string("2017-Jan-23").c_str()); // 日期的输出
    test6(); // 转换C结构：date支持与C语言的tm结构相互转换

    test7();  // 创建days对象
    test8();  // 关于days内容的运算
    test9();  // 关于 weeks,years,months 的转换与计算
    test10(); // exam：计算自2000-1-1至2017-11-18的天数，并执行其它的日期运算
    test11(); // exam：特殊日期计算

    test12(); // 创建date_period对象
    test13();
    test14(); // 两个重要函数
    test15(); // 其它成员函数
    test16(); // 并集操作
    test17(); // 迭代器用法
}
