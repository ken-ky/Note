function(abc_f)
    # <结果变量前缀名>
    # <开关选项关键字列表> <单值参数关键字列表> <多值参数关键字列表>
    # <将被解析的参数来源>
    cmake_parse_arguments(abc "ENABLE" "VALUE" "" ${ARGN})
    # 这里参数来源为函数传回的参数列表，即`ARGN`
    
    message("abc_ENABLE: ${abc_ENABLE}")
    message("abc_VALUE: ${abc_VALUE}")
endfunction()
abc_f(VALUE a ENABLE)
#[[
ENABLE开关选项的实参值被存入"结果变量"abc_ENABLE中
VALUE单值参数的实参值存入了abc_VALUE中
]]