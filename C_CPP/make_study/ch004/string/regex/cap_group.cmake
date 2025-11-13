function(print_mathces)
    message("--- BEGIN ---")
    message("CMAKE_MATCH_COUNT:\t${CMAKE_MATCH_COUNT}")
    message("CMAKE_MATCH_0:\t\t${CMAKE_MATCH_0}")
    message("CMAKE_MATCH_1:\t\t${CMAKE_MATCH_1}")
    message("CMAKE_MATCH_2:\t\t${CMAKE_MATCH_2}")
    message("--- END ---\n")
endfunction()

set(regex "([abc])([abc]+)")
# 单次正则匹配
string(REGEX MATCH ${regex} aaa d abc)
print_mathces()

# 全部正则匹配
string(REGEX MATCHALL ${regex} res aaa d abc)
print_mathces()

# 正则替换
string(REGEX REPLACE ${regex} [[(\1)\2]]
res aaa d abc)
print_mathces()

# 字符串匹配条件判断
if("aaadabc" MATCHES ${regex})
    print_mathces()
endif()