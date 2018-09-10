#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pigpio.h>

#include "seco.h"

#include "i2c/LSM9DS1.h"

static int imu_handle = 0;
static int gyro_handle = 0;
static int bmp_handle = 0;

static float magOffset[3];
static float magScale[3];

static void 
load_mag_calib(char *filename) {
	FILE *fh = fopen(filename, "r");
	char *buf[BUFSIZ];
	fread(buf, 1, BUFSIZ, fh);
	fclose(fh);
	return;
}

int
seco_init(int mode) {
	 if (mode&(MAG|ACCEL)) imu_handle = LSM9DS1_init(0x01, 0x1c, mode);
	 if (mode&GYRO) gyro_handle = LSM9DS1_init(0x01, 0x6a, mode);
	 if (mode&(PRESSURE|TEMP))bmp_handle = BMP280_init(0x01, 0x77, mode);
	 return 1;
}

void
seco_accel(float *v) {
	LSM9DS1_get_accel(imu_handle, v);
}

void
seco_gyro(float *v) {
}


float
seco_heading() {
	return LSM9DS1_get_heading(imu_handle);
}

float
seco_temp() {
	return LSM9DS1_temp(imu_handle);
}

float 
seco_pressure() {
	return 0.0;
}

int
seco_cleanup() {
	LSM9DS1_shutdown(imu_handle);
	return 0;
}
