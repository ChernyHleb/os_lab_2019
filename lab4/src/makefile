CC=gcc
CFLAGS=-I.
all: parallel_min_max makeZombie process_memory

process_memory: process_memory.o
	$(CC) -o process_memory process_memory.o $(CFLAGS)

process_memory.o:
	$(CC) -o process_memory.o -c process_memory.c $(CFLAGS)

makeZombie: makeZombie.o
	$(CC) -o makeZombie makeZombie.o $(CFLAGS)

makeZombie.o:
	$(CC) -o makeZombie.o -c makeZombie.c $(CFLAGS)

parallel_min_max : utils.o find_min_max.o utils.h find_min_max.h
	$(CC) -o parallel_min_max utils.o find_min_max.o parallel_min_max.c $(CFLAGS)

utils.o : utils.h
	$(CC) -o utils.o -c utils.c $(CFLAGS)

find_min_max.o : utils.h find_min_max.h
	$(CC) -o find_min_max.o -c find_min_max.c $(CFLAGS)

clean :
	rm utils.o find_min_max.o parallel_min_max makeZombie makeZombie.o process_memory.o
