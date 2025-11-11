set(a 1)

if(DEFINED a)
    message("DEFINED a is true")
endif()

if(CACHE{b})
else()
    message("CACHE{b} is false")
endif()

if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/logic_cal.cmake")
    message("EXISTS \"${CMAKE_CURRENT_LIST_DIR}/logic_cal.cmake\" is true")
endif()