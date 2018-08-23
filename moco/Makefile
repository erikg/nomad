LIBS=-lpigpio -lrt
CFLAGS=-Wall -pthread

BINS=moco
OBJS=main.o moco.o net.o test_mode.o

all: ${BINS}

moco: ${OBJS}
	gcc ${CFLAGS} -o $@ $^ -lpigpio -lrt

.PHONY : clean install
clean:
	${RM} ${OBJS} ${BINS}

install: moco
	sudo install -s -m 4750 -o root -g gpio moco /usr/local/bin/moco
