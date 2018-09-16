LIBS=-lpigpio -lrt -lm
CFLAGS?=-W -Wall -Werror -pedantic -pthread

BINS=moco seco_test calib turn turn-to maintain-heading calib-static inclinometer compass
OBJS=calib-static.o calib.o compass.o inclinometer.o main.o maintain-heading.o moco.o net.o seco.o seco_test.o turn-to.o turn.o
LIBFILES=libsysbus.a libmoco.a libseco.a

SYSBUS=libsysbus.a
SECO=libseco.a $(SYSBUS)
MOCO=libmoco.a

all: $(BINS)

libsysbus.a: i2c/sysi2c.o i2c/LSM9DS1.o i2c/BMP280.o
libmoco.a: moco.o
libseco.a: seco.o

lib%.a:
	$(AR) cruU $@ $^

moco: main.o net.o $(MOCO) $(SECO)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

.PHONY : clean $(INSTALL)
clean:
	$(RM) $(OBJS) $(BINS)

$(INSTALL): moco
	sudo $(INSTALL) -s -m 4750 -o root -g gpio moco /usr/local/bin/moco

seco_test: seco_test.o $(SECO)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

calib: calib.o libsysbus.a
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

calib-static: calib-static.o $(SECO)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

inclinometer: inclinometer.o $(SECO)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

turn: turn.o $(MOCO) $(SECO)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

turn-to: turn-to.o $(MOCO) $(SECO)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

maintain-heading: maintain-heading.o $(MOCO) $(SECO)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

compass: compass.o $(SECO)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

test: seco_test
	sudo ./seco_test 5
