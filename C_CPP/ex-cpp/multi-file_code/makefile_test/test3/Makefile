project := test2

link := info.o util.o main.o

${project}: ${link}
	g++ ${link} -o "${project}.sh"

# 拓展内容
${wildcard *.o}: ${wildcard *.cpp}	# 进行批处理编译
	g++ -c $< -o $@
# 自动变量 \
$@：目标 \
$^：所有目标依赖 \
$<：目标依赖列表中的第一个依赖 \
$?：所有目标依赖中被修改过的文件

# 使用如下方法也可以进行类似编译 \
%.o: %.cpp \
	g++ -c $< -o $@

print: ${wildcard *.cpp}	# 打印所有通配符中的内容
	echo $< 
	
clean:
	rm -f *.o *.sh

.PHONY: clean