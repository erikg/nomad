#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <unistd.h>
#include <pigpio.h>

#include "seco.h"
#include "i2c/LSM9DS1.h"

#define RPS 4
#define V3ARGS(x) (x)[0],(x)[1],(x)[2]
#define V3MAG2(x) ((x)[0]*(x)[0]+(x)[1]*(x)[1]+(x)[2]*(x)[2])
#define V3MAG(x) sqrt(V3MAG2(x))
#define RAD2DEG(x) ((x)*180.0/M_PI)

void
print_angles(float accel[3]) {
	float angles[2];
	angles[0] = RAD2DEG(atan2(accel[1], accel[2]));
	angles[1] = RAD2DEG(atan2(accel[2], accel[0]) - M_PI_2);

	printf(" % 3.1f\t% 3.1f\n", angles[0], angles[1]);
}

int
main(int argc, char **argv) {
	int counter = RPS * 5;	// 5 second default run time
	float accel[3];

	if (argc == 2 && isdigit(*argv[1])) { counter = atoi(argv[1]) * RPS; }
	if (gpioInitialise() < 0) { fprintf(stderr, "pigpio initialisation failed.\n"); return 1; }

	if (seco_init(ACCEL) < 0) {
		fprintf(stderr, "seco initialisation failed.\n");
		return 1;
	}

	while(counter-- > 0) {
		usleep(1000000 / RPS);

		seco_accel((float *)accel);
		print_angles(accel);
	}

	seco_cleanup();
}
