#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <unistd.h>
#include <pigpio.h>

#include "seco.h"
#include "i2c/LSM9DS1.h"

#define RPS 5
#define V3ARGS(x) (x)[0],(x)[1],(x)[2]
#define V3MAG2(x) ((x)[0]*(x)[0]+(x)[1]*(x)[1]+(x)[2]*(x)[2])
#define V3MAG(x) sqrt(V3MAG2(x))

int
main(int argc, char **argv) {
	int i, tot, counter = RPS * 5;	// 5 second default run time
	double bigAccel[3];//, bigGyro[3];
	float accel[3];
//	float gyro[3];

	if (argc == 2 && isdigit(*argv[1])) {
		counter = atoi(argv[1]) * RPS;
	}
	if (gpioInitialise() < 0) {
		fprintf(stderr, "pigpio initialisation failed.\n");
		return 1;
	}

	if (seco_init(ACCEL) < 0) {
		fprintf(stderr, "seco initialisation failed.\n");
		return 1;
	}


	tot = 0;
	for(i=0;i<3;i++) {
		bigAccel[i] = 0.0;
//		bigGyro[i] = 0.0;
	}
	while(counter-- > 0) {
		int16_t vect[3];

		seco_accel_raw(vect);
		for(i=0;i<3;i++) {
			accel[i] = (float)vect[i];
		}
		// seco_gyro((float *)gyro);
		for (i=0;i<3;i++) {
			bigAccel[i] += accel[i];
		//	bigGyro[i] += gyro[i];
		}
		tot++;

//		printf("Press: %g\n", seco_pressure());
//		printf("Temp: %g \t", seco_temp());

//		printf("G<%.1f,%.1f,%.1f>", gyro[0], gyro[1], gyro[2]);
//		mag = 0.0;
//		for(i=0;i<3;i++) {
//			mag += (accel[i] * accel[i]);
//		}
//		mag = sqrt(mag);
//		printf("A<%.3f,%.3f,%.3f>\t%f", accel[0], accel[1], accel[2], mag);

		usleep(1000000 / RPS);
	}

	for (i=0;i<3;i++) {
		float cnt = tot;
		accel[i] = bigAccel[i] / cnt;
//		gyro[i] = bigGyro[i] / cnt;
	}

	printf("%f,%f,%f\n", V3ARGS(accel));

	seco_cleanup();
}
