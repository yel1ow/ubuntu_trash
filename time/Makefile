# Makefile for time

compiler=gcc
executable=time
default_ip=127.0.0.1
default_port=54321
std=-std=c11

all:
	echo "nothing to compile"

server:
	$(compiler) server.c -o server

client:
	$(compiler) client.c -o client

run:
	./server $(default_port)

run_client:
	./client $(default_ip) $(default_port)

clean:
	rm server

clean_client:
	rm client