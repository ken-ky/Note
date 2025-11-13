string(TIMESTAMP res "%Y/%m/%d %H时%M分%S秒")
message(${res})

string(TIMESTAMP res "%Y年%m月%d日 %H:%M:%S UTC" UTC)
message(${res})