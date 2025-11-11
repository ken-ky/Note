main: main.o liba.so
	gcc main.o -o main -L. '-Wl,-R$$ORIGIN' -la
# 其中传递了 -R $ORIGIN 参数，表示 RUNPATH 位于 “$ORIGIN”（程序所在目录）

main.o: main.c
	gcc -c main.c -o main.o

liba.so: a.o
	gcc -shared a.o -o liba.so

a.o: a.c
	gcc -fPIC -c a.c -o a.o

clean:
	rm *.o *.so main || true