set(regex "[abc]+") # abc内字符出现一次或多次
string(REGEX MATCH ${regex} res aaa)
message("${res}")
string(REGEX MATCH ${regex} res aaa bbb ccc abc)
message("${res}")
string(REGEX MATCH ${regex} res bcd aaa)    # 匹配首个
message("${res}\n")

set(regex ^[abc]+$) # 只有abc内的字符出现一次或多次
string(REGEX MATCH ${regex} res aaa)
message("${res}")
string(REGEX MATCH ${regex} res aaa bbb ccc abc)
message("${res}")
string(REGEX MATCH ${regex} res bcd aaa)    # 包含了d
message("${res}")   # 输出为空