#include <stdlib.h>
#include <pigpio.h>

#define MOTOR_A_1 21
#define MOTOR_A_2 20
#define MOTOR_B_1 26
#define MOTOR_B_2 19

#define MILLISECONDS_TO_SECONDS (1.0 / 1e3)
#define MICROSECONDS_TO_SECONDS (1.0 / 1e6)

int 
moco_init() {
	if (gpioInitialise() < 0) {
		return EXIT_FAILURE;
	}

	gpioSetMode(MOTOR_A_1, PI_OUTPUT);
	gpioSetMode(MOTOR_A_2, PI_OUTPUT);
	gpioSetMode(MOTOR_B_1, PI_OUTPUT);
	gpioSetMode(MOTOR_B_2, PI_OUTPUT);
	return EXIT_SUCCESS;
}

int 
moco_cleanup() {
	gpioTerminate();
	return EXIT_SUCCESS;
}

void 
moco_momo(signed char left, signed char right) {
	if (left > 0) {
		gpioWrite(MOTOR_A_1, 1);
		gpioWrite(MOTOR_A_2, 0);
	} else if (left < 0) {
		gpioWrite(MOTOR_A_1, 0);
		gpioWrite(MOTOR_A_2, 1);
	} else {
		gpioWrite(MOTOR_A_1, 0);
		gpioWrite(MOTOR_A_2, 0);
	}

	if (right > 0) {
		gpioWrite(MOTOR_B_1, 1);
		gpioWrite(MOTOR_B_2, 0);
	} else if (right < 0) {
		gpioWrite(MOTOR_B_1, 0);
		gpioWrite(MOTOR_B_2, 1);
	} else {
		gpioWrite(MOTOR_B_1, 0);
		gpioWrite(MOTOR_B_2, 0);
	}
}
