LIBS=-lpigpio -lrt
CFLAGS=-Wall -pthread

moco: moco.o main.o net.o
	gcc ${CFLAGS} -o $@ $^ -lpigpio -lrt

moco.o: moco.c
