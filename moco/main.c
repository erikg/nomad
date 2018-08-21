#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "moco.h"
#include "net.h"
#include "test_mode.h"

void (*momo)(signed char, signed char);
int (*gpio_init)();
int (*gpio_cleanup)();

void
handle_data(unsigned char *data) {
	momo(data[0], data[1]);
}

int
main(int argc, char **argv) {
	int retcode;
	int testingMode = 0;

	if (argc == 2 && argv[1][0] == '-' && argv[1][1] == 't' && argv[1][2] == 0) {
		testingMode = 1;
		momo = test_momo;
		gpio_init = test_init;
		gpio_cleanup = test_cleanup;
	 } else {
		testingMode = 0;
		momo = moco_momo;
		gpio_init = moco_init;
		gpio_cleanup = moco_cleanup;
	 }

	retcode = gpio_init();
	if (retcode != EXIT_SUCCESS) {
		fprintf(stderr, "Error initializing");
		return retcode;
	}

	net_listen(5128, handle_data);

	return gpio_cleanup();
}
