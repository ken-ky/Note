blah.sh: blah.o	# 链接为可执行文件
	g++ blah.o -o blah.sh

blah.o: blah.cpp	# 编译为二进制文件
	g++ -c blah.cpp -o blah.o

blah.cpp:
	echo int main() { return 0; } > blah.cpp

# 上述依赖自底向上传输

clean:
	rm -f *.o *.sh

.PHONY: clean