# 多个文件的批量链接过程
project := test2

link := info.o util.o main.o

${project}: ${link}
	g++ ${link} -o "${project}.sh"

info.o: info.cpp
	g++ -c info.cpp -o info.o

util.o: util.cpp
	g++ -c util.cpp -o util.o

main.o: main.cpp
	g++ -c main.cpp -o main.o
	
clean:
	rm -f *.o *.sh

.PHONY: clean