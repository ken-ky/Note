function(my_copy_func)
    message("ARGN: ${ARGN}")
    
    # 设置三个待定内容列表
    set(options OVERWRITE MOVE)
    set(oneValueArgs DESTINATION)
    set(multiValueArgs PATHS)
    cmake_parse_arguments(
        my
        "${options}" "${oneValueArgs}" "${multiValueArgs}"  # 设置的三个列表
        ${ARGN}
    )
    message("OVERWRITE:\t${my_OVERWRITE}")
    message("MOVE:\t\t${my_MOVE}")
    message("DESTINATION:\t${my_DESTINATION}")
    message("PATH:\t\t${my_PATHS}")
    message("---\n")
endfunction()

my_copy_func(DESTINATION ".." PATHS "1.txt" "2.txt" OVERWRITE)
my_copy_func(MOVE DESTINATION "../.." PATHS "3.txt" "4.txt")
my_copy_func(DESTINATION "../folder;name" PATHS 1.txt;2.txt)
#[[ 
    第三次调用时由于`DESTINATION`是单值变量
    因此接收到的参数列表会被处理为`DESTINATION:../folder;name`
    之后在进行解析时抛弃了`;`连接的部分
]]