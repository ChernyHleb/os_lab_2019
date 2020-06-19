CC=gcc
CFLAGS=-I. -std=c99

all : server client

server : server.c
	$(CC) -lpthread -o server server.c -L. -lModFact $(CFLAGS)

client : client.c
	$(CC) -o client client.c -L. -lModFact $(CFLAGS)

clean :
	rm -f client server