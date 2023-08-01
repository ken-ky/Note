# 条件表达式：表达式1 if 条件 else 表达式2
import sys

score = int(sys.argv[1])  # 使用命令行输入方式
result = 'pass' if score >= 60 else 'failed'
print(result)
