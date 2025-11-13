include(template_def.cmake)

set(a "a_val")
set(b "b_val")
set(C "ON")    # 值真，表示已定义
set(D "TRUE")
set(E "1")      # 值真，输出类模板内定义
set(F "YES") # 值真，输出定义的变量

string(CONFIGURE ${template} res)
message(${res})