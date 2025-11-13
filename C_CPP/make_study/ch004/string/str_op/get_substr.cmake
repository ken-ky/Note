string(SUBSTRING "abc" 1 1 res)
message(${res})

string(SUBSTRING  "abc" 1 -1 res)
message(${res})

string(SUBSTRING "abc" 1 10 res)
message(${res})

string(SUBSTRING "你好" 3 3 res)
message(${res})