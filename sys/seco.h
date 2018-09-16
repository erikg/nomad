#ifndef SECO_H
#define SECO_H

/* IMU */
#define MAG		(2 << 0)
#define ACCEL		(2 << 1)
#define GYRO		(2 << 2)

/* pressure/temp */
#define PRESSURE	(2 << 3)
#define TEMP		(2 << 4)

int imu_handle;

int seco_init(int mode);
float seco_heading();
void seco_accel(float *v);
void seco_accel_raw(int16_t *v);
void seco_gyro(float *v);
float seco_temp();
float seco_pressure();
int seco_cleanup();

#endif
