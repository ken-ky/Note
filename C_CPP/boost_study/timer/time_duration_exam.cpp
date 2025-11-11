#include <iostream>
using namespace std;

#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost::posix_time;
using namespace boost::
    gregorian; // posix_time命名空间不包含gregorian空间，因此需要加上引用

void test1() {
    hours h(1);     // 1h
    minutes m(10);  // 10mins
    seconds s(30);  // 30s
    millisec ms(1); // 1ms

    time_duration td1 = h + m + s + ms;         // 可以赋值给time_duration
    time_duration td2 = hours(2) + seconds(10); // 也可以直接赋值

    time_duration td3 = duration_from_string("1:10:30:001"); // 工厂函数直接转换

    // 时间对象的各个部分
    time_duration td(1, 10, 30, 1000);
    assert(td.hours() == 1 && td.minutes() == 10 && td.seconds() == 30);
    assert(td.total_seconds() == (1 * 60 + 10) * 60 + 30);
    assert(td.total_milliseconds() ==
           td.total_seconds() * 1000 + 1);   // 总毫秒数
    assert(td.fractional_seconds() == 1000); // 总微秒数

    // 负数值操作
    hours h1(-10);           // time_duration允许取负
    assert(h.is_negative()); // 判断是否为负值

    time_duration h2 = h1.invert_sign(); // 可以用于反转符号，并返回新值
    assert(!h2.is_negative() && h2.hours() == 10);

    // 赋值特殊时间
    time_duration td4(not_a_date_time);
    assert(td4.is_special() && td4.is_not_a_date_time());

    time_duration td5(neg_infin);
    assert(td5.is_negative() && td5.is_neg_infinity());
}

void test2() {
    time_duration td1 = hours(1);
    time_duration td2 = hours(2) + minutes(30);

    assert(td1 < td2);
    assert((td1 + td2).hours() == 3);
    assert((td1 - td2).is_negative());
    assert(td1 * 5 == td2 * 2);
    assert((td1 / 2).minutes() == td2.minutes());

    // 输出time_duration
    time_duration td(1, 10, 30, 1000);

    cout << to_simple_string(td); // 返回HH:mm:SS.fffffffff
    cout << to_iso_string(td);    // 返回HHMMSS, fffffffff
    // 使用to_tm()可以将time_duration转换为tm结构（不能反向转换）
}

#define BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG // 定义纳秒精度宏
#include <boost/date_time/posix_time/posix_time.hpp>

void test3() {
    time_duration td(1, 10, 30, 1000); // 1000ns，即：1微秒

    cout << td;
    assert(td.total_milliseconds() ==
           td.total_seconds() * 1000); // 计算总毫秒时，微秒会被忽略
    assert(td.resolution() == boost::date_time::nano); // 纳秒分辨率
    assert(td.num_fractional_digits() == 9); // 纳秒分辨率断言成立（微秒为6位）

    // 使用自定义毫秒单位
    time_duration::tick_type my_millsec =
        time_duration::ticks_per_second() / 1000;
    time_duration td1(1, 10, 30, 10 * my_millsec); // 10毫秒，即：0.01s
}

void test4() {
    ptime p(date(2017, 7, 7), hours(1)); // 2017.1.1 1:00AM

    ptime p1 = time_from_string("2017-7-7 01:00:00");
    ptime p2 = from_iso_string("20170707T010000");

    ptime p1_1 = second_clock::local_time();       // 秒精确度
    ptime p2_1 = microsec_clock::universal_time(); // 微秒精确度
    cout << p1_1 << endl << p2_1;

    ptime p1_2(not_a_date_time); // 无效时间
    assert(p1_2.is_not_a_date_time());
    ptime p2_2(pos_infin); // 正无穷时间
    assert(p2_2.is_special() && p2_2.is_pos_infinity());
}

void test5() {
    // 2010.3.20 12:30AM
    ptime p(date(2010, 3, 20), hours(12) + minutes(30));

    date d = p.date();
    time_duration td = p.time_of_day();
    assert(d.month() == 3 && d.day() == 20);
    assert(td.total_seconds() == 12 * 3600 + 30 * 60);

    // 时间点运算
    ptime p1(date(2010, 3, 20), hours(12) + minutes(30));
    ptime p2 = p1 + hours(3);

    assert(p1 < p2);
    assert(p2 - p1 == hours(3));

    p2 += months(1);
    assert(p2.date().month() == 4);

    // 转换字符串
    ptime p0(date(2017, 5, 20), hours(14));
    tm t = to_tm(p0);

    assert(t.tm_year == 117 && t.tm_hour == 14);
    assert(ptime_from_tm(t) == p);

    ptime p01 = from_time_t(time(0));
    assert(p.date() == day_clock::local_day());
    cout << to_time_t(p2) << endl;
}

void test6() {
    ptime p(date(2017, 1, 1), hours(12));
    time_period tp1(p, hours(8));            // 一个8小时的区间
    time_period tp2(p + hours(8), hours(1)); // 一个1小时的区间
    assert(tp1.end() == tp2.begin() && tp1.is_adjacent(tp2));
    assert(!tp1.intersects(tp2)); // 两个时间区间相邻而不相交

    tp1.shift(hours(1));         // tp1平移1h
    assert(tp1.is_after(p));     // tp1在中午之后
    assert(tp1.intersects(tp2)); // 两个时间区间现在相交

    tp2.expand(hours(10)); // tp2向两端扩展10h
    assert(tp2.contains(p) && tp2.contains(tp1));
}

void test7() {
    ptime p(date(2017, 5, 31), hours(10));

    for (time_iterator t_iter(p, minutes(10)); t_iter < p + hours(1);
         ++t_iter) {
        cout << *t_iter << endl;
    }
}

int main() {
    /* 处理时间 */
    test1(); // 时间对象
    test2(); // 时间运算
    test3(); // 自定义毫秒单位

    test4(); // 时间点
    test5(); // 时间点运算

    test6(); // 时间区间
    test7(); // 时间迭代器
    return 0;
}