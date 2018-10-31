# Makefile for __HELLO__ stepic course

all: libHello.so hello

libHello.so: hello.c
	gcc -o libHello.so -shared -fPIC hello.c

hello: hello.c
	gcc main.c -fPIC -ldl -o hello

clean:
	-rm hello *.o *.so hello_static 2>/dev/null
