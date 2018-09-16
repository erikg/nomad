#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <pigpio.h>

#include "../seco.h"

#include "LSM9DS1.h"

int
LSM9DS1_init(int bus, uint8_t address, int mode) {
	int handle = i2cOpen(bus, address, 0);

	int whoami = i2cReadByteData(handle, 0x0F);

	if (whoami == 0x68 && (mode & GYRO)) {
		i2cWriteByteData(handle, 0x1E, 0x38);	// 0b 0011 1000	 CTRL_REG_4
		i2cWriteByteData(handle, 0x10, 0xB8);	// 0b 0011 1000  CTRL_REG1_G
		i2cWriteByteData(handle, 0x13, 0xB8);	// 0b 0000 0000  ORIENT_CFG_G
	}
	if (whoami == 0x68 && (mode & ACCEL)) {
		int res;
		printf("Setting up accelerometer");
		res = i2cWriteByteData(handle, 0x20, 0x38);	// 0b 0011 1000	 CTRL_REG5_XL
		if (res != 0) { printf("Error 0x20!"); exit(-1); }
		res = i2cWriteByteData(handle, 0x21, 0x28);	// 0b 0011 1000  CTRL_REG6_XL
		if (res != 0) { printf("Error 0x21!"); exit(-1); }
//		i2cWriteByteData(handle, 0x21, 0x00);	// 0b 0000 0000  CTRL_REG7_XL
	}
	if (whoami == 0x3D && (mode & MAG)) {
		i2cWriteByteData(handle, 0x20, 0xAD);
		i2cWriteByteData(handle, 0x21, 0x60);
		i2cWriteByteData(handle, 0x22, 0x00);
		i2cWriteByteData(handle, 0x23, 0x04);
	}

	return handle;
}

float LSM9DS1_temp(int handle) {
	return (float)(i2cReadByteData(handle, 0x15) | i2cReadByteData(handle, 0x16) << 8);
}

int LSM9DS1_get_accel(int handle, int16_t *vect) {
	int i, readRes = 0;
	uint8_t v[6];
	int res[3];

	readRes = i2cReadI2CBlockData(handle, 0x80 | 0x28, (char *)v, 6);

	if (readRes != 6) {
		printf("Pi error: %d\n", readRes);
		exit(-1);
	}
	res[0] = (int16_t)(v[0] | v[1] << 8);
	res[1] = (int16_t)(v[2] | v[3] << 8);
	res[2] = (int16_t)(v[4] | v[5] << 8);

	for(i=0;i<3;i++) { vect[i] = res[i]; }

	return 0;
}

int LSM9DS1_get_accel_calibrated(int handle, float *vect) {
	int i, rval;
	float calib[3] = {-438.9999845,97.7200015,-181.819946};
	int16_t v[3];

	rval = LSM9DS1_get_accel(handle, v);
	for(i=0;i<3;i++) {
		vect[i] = 4.0 * ((float)(v[i]) - calib[i]);
	}
	return rval;
}

int
LSM9DS1_get_gyro(int handle, float *vect) {
	return -1;
}

int
LSM9DS1_get_magnometer_raw(int handle, int16_t *vect) {
	int readRes = 0;
	uint8_t v[6];

	readRes = i2cReadI2CBlockData(handle, 0x28, (char *)&v[0], 6);

	if (readRes != 6) {
		printf("Pi error: %d\n", readRes);
		exit(-1);
	}

	vect[0] = v[0] | v[1] << 8;
	vect[1] = v[2] | v[3] << 8;
	vect[2] = v[4] | v[5] << 8;

	return 1;
}

int
LSM9DS1_get_magnometer_calibrated(int handle, float *v) {
	int16_t vec[3];
	float calib[6] = {-2749.0, 826.0, -3518.0, 770.0, -970.0, 874.0};

	float calibOffset[3] = {calib[0], calib[2], calib[4]};
	float calibScale[3] = {calib[1], calib[3], calib[5]};

	int ret = LSM9DS1_get_magnometer_raw(handle, vec);
	v[0] = ((float)vec[0] - calibOffset[0]) / calibScale[0];
	v[1] = ((float)vec[1] - calibOffset[1]) / calibScale[1];
	v[2] = ((float)vec[2] - calibOffset[2]) / calibScale[2];
	return ret;
}

/* radians clockwise from magnetic north.  negative if fail */
float
LSM9DS1_get_heading(int handle) {
	float v[3] = {0,0,0};
	float res = 0.0;

	LSM9DS1_get_magnometer_calibrated(handle, v);
	res = 180.0 * atan2((double)v[1],(double)v[0]) / M_PI;

	res += 90.0; // mounted sideways

	while (res < 0) { res += 360; }
	while (res > 360) { res -= 360; }
	return res;
}

int
LSM9DS1_shutdown(int handle) {
	return i2cClose(handle) == handle;
}
