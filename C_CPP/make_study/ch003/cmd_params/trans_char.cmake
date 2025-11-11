cmake_minimum_required(VERSION 3.20)
set("a?b" "var_a?b")

# \? 转义为 ?
message(${a\?b}) # 转义为变量 a?b
message(What_day_is_today\?)

# \n 转义为换行符，\t 转义为制表符，\! 转义为 !
message(Quest: \n\tWhat_day_is_today\!)
set("a;b" "var_a;b")

# 非引号参数中，\; 转义为 ;，且不分隔变量
message(x;y\;z)

# 引号参数中 \; 不转义
message("x;y\;z")

# 变量引号中 \; 转义为 ;
message("${a\;b}") # 转义为变量 a;b