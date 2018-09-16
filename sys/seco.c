#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pigpio.h>

#include "seco.h"

#include "i2c/LSM9DS1.h"
#include "i2c/BMP280.h"

int bmp_handle = 0;
int imu_handle = 0;
int mag_handle = 0;

static void
load_mag_calib(char *filename) {
	return;
	FILE *fh = fopen(filename, "r");
	char *buf[BUFSIZ];
	fread(buf, 1, BUFSIZ, fh);
	fclose(fh);
	return;
}

int
seco_init(int mode) {
	bmp_handle = PI_NO_HANDLE;
	imu_handle = PI_NO_HANDLE;
	mag_handle = PI_NO_HANDLE;
	if (mode&(GYRO|ACCEL)) imu_handle = LSM9DS1_init(0x01, 0x6a, mode);
	if (mode&MAG) {
		mag_handle = LSM9DS1_init(0x01, 0x1c, mode);
		load_mag_calib(".mag");
	}
	if (mode&(PRESSURE|TEMP))bmp_handle = BMP280_init(0x01, 0x77, mode);
	return 1;
}

void
seco_accel(float *v) {
	LSM9DS1_get_accel_calibrated(imu_handle, v);
}

void
seco_accel_raw(int16_t *v) {
	LSM9DS1_get_accel(imu_handle, v);
}

void
seco_gyro(float *v) {
	LSM9DS1_get_gyro(imu_handle, v);
}


float
seco_heading() {
	return LSM9DS1_get_heading(mag_handle);
}

float
seco_temp() {
	return LSM9DS1_temp(mag_handle);
}

float
seco_pressure() {
	return 0.0;
}

int
seco_cleanup() {
	if(imu_handle >= 0) LSM9DS1_shutdown(imu_handle);
	if(mag_handle >= 0) LSM9DS1_shutdown(mag_handle);
	if(bmp_handle >= 0) LSM9DS1_shutdown(bmp_handle);
	return 0;
}
