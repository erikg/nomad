LIBS=-lpigpio -lrt -lm
CFLAGS=-Wall -pthread

BINS=moco seco_test calib turn turn-to maintain-heading calib-static inclinometer compass
OBJS=main.o moco.o seco.o net.o

all: $(BINS)

libsysbus.a: i2c/sysi2c.o i2c/LSM9DS1.o i2c/BMP280.o
libmoco.a: moco.o
libseco.a: seco.o libsysbus.a

lib%.a:
	ar cruU $@ $^

moco: main.o net.o libmoco.a libseco.a libsysbus.a
	gcc $(CFLAGS) -o $@ $^ $(LIBS)

.PHONY : clean install
clean:
	$(RM) $(OBJS) $(BINS)

install: moco
	sudo install -s -m 4750 -o root -g gpio moco /usr/local/bin/moco

seco_test: seco_test.o libseco.a libsysbus.a
	gcc $(CFLAGS) -o $@ $^ $(LIBS)

calib: calib.o libsysbus.a
	gcc $(CFLAGS) -o $@ $^ $(LIBS)

calib-static: calib-static.o libseco.a libsysbus.a
	gcc $(CFLAGS) -o $@ $^ $(LIBS)

inclinometer: inclinometer.o libseco.a libsysbus.a
	gcc $(CFLAGS) -o $@ $^ $(LIBS)

turn: turn.o libmoco.a libseco.a libsysbus.a
	gcc $(CFLAGS) -o $@ $^ $(LIBS)

turn-to: turn-to.o libmoco.a libseco.a libsysbus.a
	gcc $(CFLAGS) -o $@ $^ $(LIBS)

maintain-heading: maintain-heading.o libmoco.a libseco.a libsysbus.a
	gcc $(CFLAGS) -o $@ $^ $(LIBS)

compass: compass.o libseco.a libsysbus.a
	gcc $(CFLAGS) -o $@ $^ $(LIBS)

test: seco_test
	sudo ./seco_test 5
