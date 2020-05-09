CC=gcc
CFLAGS=-I.
all: parallel_min_max makeZombie process_memory parallel_sum

parallel_sum: arr_sum.o utils.o parallel_sum.c
	$(CC) -o parallel_sum parallel_sum.c utils.o arr_sum.o -lpthread  $(CFLAGS)

arr_sum.o: utils.h arr_sum.h
	$(CC) -o arr_sum.o -c arr_sum.c $(CFLAGS)

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
	rm utils.o find_min_max.o parallel_min_max makeZombie makeZombie.o process_memory.o arr_sum.o
