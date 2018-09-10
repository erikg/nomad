#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <unistd.h>
#include <pigpio.h>

#include "seco.h"
#include "i2c/LSM9DS1.h"

#define RPS 2

int
main(int argc, char **argv) {
	int handle;
	int slu;
	float min[3] = {999999,999999,999999}, max[3] = {-999999,-999999,-999999}, v[3];
	char buf[BUFSIZ];
	int sleeptime = 40000;
	int sluCnt = 100;

	if (gpioInitialise() < 0) {
		fprintf(stderr, "pigpio initialisation failed.\n");
		return 1;
	}

	handle = LSM9DS1_init(1, 0x1c, MAG);
	while(slu++ < sluCnt) {
		int16_t vi[3];
		LSM9DS1_get_magnometer_raw(handle, vi);
		v[0] = (float)vi[0];
		v[1] = (float)vi[1];
		v[2] = (float)vi[2];
		if (v[0] < min[0]) { min[0] = v[0]; slu = 0; }
		if (v[1] < min[1]) { min[1] = v[1]; slu = 0; }
		if (v[2] < min[2]) { min[2] = v[2]; slu = 0; }
		if (v[0] > max[0]) { max[0] = v[0]; slu = 0; }
		if (v[1] > max[1]) { max[1] = v[1]; slu = 0; }
		if (v[2] > max[2]) { max[2] = v[2]; slu = 0; }
		if(slu == 0) {
			printf("Min: %.0f,%.0f,%.0f   Max: %.0f,%.0f,%.0f\n", min[0], min[1], min[2], max[0], max[1], max[2]);
		}
		usleep(sleeptime);
	}

	v[0] = floor((min[0] + max[0]) / 2.0);
	v[1] = floor((min[1] + max[1]) / 2.0);
	v[2] = floor((min[2] + max[2]) / 2.0);

	snprintf(buf, BUFSIZ, "{%.1f, %.1f, %.1f, %.1f, %.1f, %.1f};\n", 
			v[0], max[0]-v[0], 
			v[1], max[1]-v[1], 
			v[2], max[2]-v[2]);

	if (argc == 2) {
		FILE *fh = fopen(argv[1],"w");
		fwrite(buf, 1, strlen(buf), fh);
		fflush(fh);
		fclose(fh);
	}
	puts(buf);

	LSM9DS1_shutdown(handle);
}
