#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <pigpio.h>

#include "../seco.h"

#include "BMP280.h"

int
BMP280_init(int bus, uint8_t address, int mode) {
	int handle = i2cOpen(bus, address, 0);

//		if (mode & TEMP) {
//			fprintf(stderr, "Uh oh");
//			exit(-1);
//		}
//		if (mode & PRESSURE) {
//			fprintf(stderr, "Uh oh");
//			exit(-1);
//		}

	return handle;
}

float
BMP280_get_temperature(int handle) {
	return 42.0;
}

float
BMP280_get_pressure(int handle) {
	return 69.0;
}

int
BMP280_shutdown(int handle) {
	return i2cClose(handle) == handle;
}
