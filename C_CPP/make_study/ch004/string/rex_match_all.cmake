set(regex "([abc]+)")
string(REGEX MATCHALL ${regex} res adb dcd abcdcba)
message("${res}")