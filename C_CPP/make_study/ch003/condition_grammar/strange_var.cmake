cmake_minimum_required(VERSION 3.20)
set(on "OFF")
if(on)  # 变量不为空
    message("ON")
else()
    message("OFF")
endif()

if(${on})   # 使用的值为 False
    message("ON")
else()
    message("OFF")
endif()