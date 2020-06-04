CC=gcc
CFLAGS=-I.
all: mutex Parallel_fact deadlock

mutex : mutex.c
	$(CC) -o mutex mutex.c -lpthread  $(CFLAGS)

Parallel_fact : Parallel_fact.c
	$(CC) -o Parallel_fact Parallel_fact.c -lpthread $(CFLAGS)

Parallel_fact : deadlock.c
	$(CC) -o deadlock deadlock.c -lpthread $(CFLAGS)

clean :
	rm mutex Parallel_fact deadlock
