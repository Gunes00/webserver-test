CC = gcc
CFLAGS = -Wall -Wextra

all: clean server

server: ./src/webserver.c
	$(CC) $(CFLAGS) ./src/webserver.c -o server
	./server

clean:
	rm -f server
