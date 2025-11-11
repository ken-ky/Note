if(ABC)
else()
    message("ABC isn't a defined variable, thus this condition is false\n")
endif()

set(a "XYZ")
set(b "0")
set(c "a-NOTFOUND")

if(a)
    message("a is a variable, the value isn't false, thus the condition is true\n")
endif()

if(b)
else()
    message("b is a variable, the value is false, thus the condition is false\n")
endif()

if(c)
else()
    message("c is a variable, the value is false, thus the condition is false\n")
endif()