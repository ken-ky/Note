import re

# 元字符

# 开始与结束字符
p1 = r'\w+@2000q1'  # 不强制以这个字符串开头
p2 = r'^\w@zhijieketang\.com\$'  # 强制以此字符串结尾

text = 'qwwd@2000q1'
email = 'tony_guan588@zhijieketang.com'

print(re.search(p1, text))
print(re.search(p2, email))

# 字符类
p3 = r'[Jj]ava'  # 允许此位置有多个字符匹配
print(re.search(p3, 'I like Java and python.'))

p4 = r'[^2-6]'  # 对2~6的字符取反
print(re.search(p4, '2Python 3'))  # 被匹配到的第一个非p4的字符
print(re.search(p4, '23232'))

# 分组
p5 = r'(121){2}'
m1 = re.search(p5, '121121abcabc')
print(m1)
print(m1.group())
print(m1.group(1))
