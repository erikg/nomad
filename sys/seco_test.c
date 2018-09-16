#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <unistd.h>
#include <pigpio.h>

#include "seco.h"

#define RPS 2

int
main(int argc, char **argv) {
	int counter = RPS * 60 * 5;	// 5 minute default run time
	float accel[3];
	float gyro[3];

	if (argc == 2 && isdigit(*argv[1])) {
		counter = atoi(argv[1]) * RPS;
	}
	if (gpioInitialise() < 0) {
		fprintf(stderr, "pigpio initialisation failed.\n");
		return 1;
	}

	if (seco_init(MAG | ACCEL | GYRO | PRESSURE | TEMP) < 0) {
		fprintf(stderr, "seco initialisation failed.\n");
		return 1;
	}

	while(counter-- > 0) {
		float heading = seco_heading();
		seco_accel((float *)accel);
		seco_gyro((float *)gyro);

		printf("\theading: % 3.1f \t", heading);
//		printf("Press: %g\n", seco_pressure());
//		printf("Temp: %g \t", seco_temp());

		printf("A<% 05.1f,% 5.1f,% 5.1f>", accel[0], accel[1], accel[3]);

		printf("\n");
		usleep(1000000 / RPS);
	}

	seco_cleanup();
}
