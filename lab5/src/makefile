CC=gcc
CFLAGS=-I.
all: mutex Parallel_fact

mutex : mutex.c
	$(CC) -o mutex mutex.c -lpthread  $(CFLAGS)

Parallel_fact : Parallel_fact.c
	$(CC) -o Parallel_fact Parallel_fact.c -lpthread $(CFLAGS)

clean :
	mutex Parallel_fact
