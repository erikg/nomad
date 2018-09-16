#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <unistd.h>
#include <pigpio.h>

#include "seco.h"

float
normalizeAngleDegrees(float angle) {
	float a = angle;
	while(a<0) a+=360;
	while(a>360) a-= 360;
	return a;
}

#define RPS 2

int
main(int argc, char **argv) {
	int counter = 10 * RPS;

	if (argc == 2 && isdigit(*argv[1])) {
		counter = atoi(argv[1]) * RPS;
	}

	if (gpioInitialise() < 0) {
		fprintf(stderr, "pigpio initialisation failed.\n");
		return 1;
	}

	if (seco_init(MAG) < 0) {
		fprintf(stderr, "seco initialisation failed.\n");
		return 1;
	}

	while(counter--) {
		printf("%.1f\n", seco_heading());
		usleep(1000000 / RPS);
	}

	seco_cleanup();
}
