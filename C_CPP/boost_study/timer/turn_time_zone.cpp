/* 自北京往旧金山，飞行时间为12h，跨时区时间转换 */
#include <iostream>
using namespace std;

// 包含必要头文件
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include <boost/date_time/local_time/local_time_types.hpp>
#include <boost/date_time/local_time/tz_database.hpp> // 时区对应数据
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost::gregorian;
using namespace boost::posix_time;
using namespace boost::local_time;

int main() {
    tz_database tz_db; // 时区数据库对象

    tz_db.load_from_file("./date_time_zonespec.csv"); // 文本数据库

    // 使用字符串 Asia/Shanghai 获得上海时区，即北京时间
    time_zone_ptr shz = tz_db.time_zone_from_region("Asia/Shanghai");

    // 使用字符串 American/Los_Angeles 获得旧金山时区，即洛杉矶时间
    time_zone_ptr sfz = tz_db.time_zone_from_region("American/Los_Angeles");

    cout << shz->has_dst() << endl; // 上海时区是否夏令时（无）
    cout << shz->std_zone_name() << endl; // 上海时区名称为CST

    local_date_time dt_bj(date(2014, 3, 6), // 北京时间
                          hours(16),
                          shz,  // 上海时区
                          false // 不使用夏令时
    );
    cout << dt_bj << endl;

    time_duration flight_time = hours(12); // 飞行12小时
    dt_bj += flight_time;                  // 到达旧金山时的北京时间
    local_date_time dt_sf = dt_bj.local_time_in(sfz); // 旧金山当地时间
    cout << dt_sf << endl;

    return 0;
}
