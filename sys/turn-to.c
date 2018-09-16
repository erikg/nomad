#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <unistd.h>
#include <pigpio.h>

#include "moco.h"
#include "seco.h"

#define POWER 30

float
normalizeAngleDegrees(float angle) {
	float a = angle;
	while(a<0) a+=360;
	while(a>360) a-= 360;
	return a;
}

float
turn_power(float a) {
	if (a > 90)
		return 90;
	if (a > 30)
		return 70;
	if (a > 7)
		return 50;
	return 35;
}

int
main(int argc, char **argv) {
	float target_heading;

	if (argc == 2 && isdigit(*argv[1])) {
		target_heading = atof(argv[1]);
	} else {
		return EXIT_FAILURE;
	}

	if (gpioInitialise() < 0) {
		fprintf(stderr, "pigpio initialisation failed.\n");
		return 1;
	}

	if (seco_init(MAG) < 0) {
		fprintf(stderr, "seco initialisation failed.\n");
		return 1;
	}
	moco_init();

	do {
		float dh, heading = seco_heading();
		dh = normalizeAngleDegrees(heading - target_heading + 540.0) - 180.0;
		signed char power = (signed char)floor(turn_power(fabs(dh)));
		if (fabs(dh) < 3)
			goto EXIT;
		else if ( dh < 0)
			moco_momo(power,-power);
		else
			moco_momo(-power,power);
	} while (1);
	EXIT:
	moco_momo(0,0);

	seco_cleanup();
	moco_cleanup();
}
