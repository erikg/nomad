#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <unistd.h>
#include <signal.h>

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
		return 70;
	if (a > 55)
		return 50;
	if (a > 25)
		return 40;
	return 35;
}

void
cleanup(int sig) {
	sig+=0;
	moco_momo(0,0);
	seco_cleanup();
	moco_cleanup();
}

void
report(int sig) {
	if (sig != SIGUSR2) {
		printf("bad signal? %d\n", sig);
	}
	printf("%g\n", seco_heading());
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

	signal(SIGTERM, cleanup);
	signal(SIGINT, cleanup);
	signal(SIGUSR1, cleanup);
	signal(SIGUSR2, report);

	do {
		float dh, heading = seco_heading();
		char power;

		dh = normalizeAngleDegrees(heading - target_heading + 540.0) - 180.0;
		power = (char)floor(turn_power(fabs(dh)));
		if (fabs(dh) < 5) {
			moco_momo(0,0);
			sleep(1);
		} else if ( dh < 0) {
			moco_momo(power,-power);
		} else {
			moco_momo(-power,power);
		}
	} while (1);
	cleanup(0);
}
