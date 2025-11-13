set(regex1 [[\(a\+b\)]])
set(regex2 "\\(a\\+b\\)")
string(REGEX MATCH ${regex1} res "(a+b)")
message("${res}")