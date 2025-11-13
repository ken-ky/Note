set(template [=[
#cmakedefine C
#cmakedefine01 D
#cmakedefine E e
#cmakedefine F @F@
]=])

#[=[
    替换变量a：${a}
    替换变量b：@b@
    定义宏C
    
    定义0/1宏D          D的值为假时，会为 0
    定义值为e的宏E
    定义值为F变量的宏F  F被名为F的变量的宏替换
]=]