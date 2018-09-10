LIBS=-lpigpio -lrt -lm
CFLAGS=-Wall -pthread

BINS=moco seco_test calib
OBJS=main.o moco.o seco.o net.o

all: ${BINS}

libsysbus.a: i2c/sysi2c.o i2c/LSM9DS1.o i2c/BMP280.o
libmoco.a: moco.o

lib%.a:
	ar cruU $@ $^

moco: main.o net.o seco.o moco.o libsysbus.a
	gcc ${CFLAGS} -o $@ $^ ${LIBS}

.PHONY : clean install
clean:
	${RM} ${OBJS} ${BINS}

install: moco
	sudo install -s -m 4750 -o root -g gpio moco /usr/local/bin/moco

seco_test: seco.o seco_test.o libsysbus.a
	gcc ${CFLAGS} -o $@ $^ ${LIBS}

calib: calib.o libsysbus.a
	gcc ${CFLAGS} -o $@ $^ ${LIBS}

test: seco_test
	sudo ./seco_test 5
