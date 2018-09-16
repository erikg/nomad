#ifndef LSM9DS1
#define LSM9DS1

/* returns handle >0 on success, <=0 on fail */
int LSM9DS1_init(int bus, uint8_t address, int mode);

int LSM9DS1_get_magnometer_raw(int handle, int16_t vect[4]);
int LSM9DS1_get_magnometer_calibrated(int handle, float vect[4]);

int LSM9DS1_get_accel(int handle, int16_t *vect);
int LSM9DS1_get_accel_calibrated(int handle, float *vect);
float LSM9DS1_temp(int handle);

int LSM9DS1_get_gyro(int handle, float *vect);

/* radians clockwise from magnetic north. */
float LSM9DS1_get_heading(int handle);

int LSM9DS1_shutdown(int handle);

#endif
