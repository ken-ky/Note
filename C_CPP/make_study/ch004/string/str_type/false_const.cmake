include(template_def.cmake)

set(a "a_val")
set(b "b_val")
set(C "OFF")    # 值为假
set(D "FALSE")
set(E "0")      # 值为假
set(F "IGNORE") # 值为假

string(CONFIGURE ${template} res)
message(${res})