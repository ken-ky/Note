include(template_def.cmake)

set(a "a_val")
set(b "b_val")
set(C "C_val")
set(D "D_val")
set(E "E_val")
set(F "F_val")  # 由于F模板为@F@，所以可以正常赋值

string(CONFIGURE ${template} res @ONLY)
message(${res})