LIBS=-lpigpio -lrt
CFLAGS=-Wall -pthread

BINS=moco
OBJS=main.o moco.o net.o test_mode.o

all: ${BINS}

moco: ${OBJS}
	gcc ${CFLAGS} -o $@ $^ -lpigpio -lrt

.PHONY : clean
clean:
	${RM} ${OBJS} ${BINS}
