# Makefile for __HELLO__ stepic course

all: libHello.so hello

main.o: main.c
	gcc -o main.o -c main.c

hello.o: hello.c
	gcc -o hello.o -c hello.c

libHello.so: hello.c hello.h
	gcc -o libHello.so -shared -fPIC hello.c

hello: hello.c
	gcc main.c -L. -lHello -o hello

hello_static: main.o hello.o
	gcc -o hello_static main.o hello.o

clean:
	-rm hello *.o *.so hello_static 2>/dev/null
