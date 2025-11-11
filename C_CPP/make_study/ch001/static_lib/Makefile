# -lab:链接名为ab的库
main: main.o libab.a
	gcc main.o -o main -L. -lab

main.o: main.c
	gcc -c main.c -o main.o

# ar rcs【r:文件归档，c:创建新归档文件不输出警告，s:为归档文件创建索引】
libab.a: a.o b.o
	ar rcs libab.a a.o b.o

a.o: a.c
	gcc -c a.c -o a.o

b.o: b.c
	gcc -c b.c -o b.o