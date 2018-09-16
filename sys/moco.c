#include <stdio.h>
#include <stdlib.h>
#include <pigpio.h>

#define MOTOR_A_1 5
#define MOTOR_A_2 6
#define MOTOR_A_PWM 13

#define MOTOR_B_1 26
#define MOTOR_B_2 16
#define MOTOR_B_PWM 12

#define MAX_PWM 120

#define MILLISECONDS_TO_SECONDS (1.0 / 1e3)
#define MICROSECONDS_TO_SECONDS (1.0 / 1e6)

int CLAMP(int x, int min, int max) {
	if (x < min) { return min; }
	if (x > max) { return max; }
	return x;
}

void
init_motor(int en, int in1, int in2) {
	gpioSetMode(in1, PI_OUTPUT);
	gpioSetMode(in2, PI_OUTPUT);
	gpioSetMode(en, PI_OUTPUT);
	gpioSetPWMrange(en, MAX_PWM);
	gpioSetPWMfrequency(en, 50);
}

int
moco_init() {
	if (gpioInitialise() < 0) {
		return EXIT_FAILURE;
	}

	init_motor(MOTOR_A_PWM, MOTOR_A_1, MOTOR_A_2);
	init_motor(MOTOR_B_PWM, MOTOR_B_1, MOTOR_B_2);
	return EXIT_SUCCESS;
}

int
moco_cleanup() {
	gpioTerminate();
	return EXIT_SUCCESS;
}

void tread_control(int val, int m1, int m2, int pwm) {
	int aval = abs(val);
	int cval = CLAMP(aval, 0, MAX_PWM);
	if (aval < 10) { 		/* STOP */
		gpioPWM(pwm, 0);
	} else if (val > 0) { 		/* FORWARD */
		gpioWrite(m1, 1);
		gpioWrite(m2, 0);
		gpioPWM(pwm, cval);
	} else {			/* BACKWARD */
		gpioWrite(m1, 0);
		gpioWrite(m2, 1);
		gpioPWM(pwm, cval);
	}
}

#define TREAD_CONTROL(tread, M1, M2, M_PWM) tread_control(tread,M1,M2,M_PWM)

void
moco_momo(signed char left, signed char right) {
	TREAD_CONTROL(left, MOTOR_A_1, MOTOR_A_2, MOTOR_A_PWM);
	TREAD_CONTROL(right, MOTOR_B_2, MOTOR_B_1, MOTOR_B_PWM);
}
