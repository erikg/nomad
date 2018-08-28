#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "moco.h"
#include "net.h"
#include "test_mode.h"

void
handle_data(unsigned char *data) {
	moco_momo(data[0], data[1]);
}

int
main(int argc, char **argv) {
	int retcode;

	retcode = moco_init();
	if (retcode != EXIT_SUCCESS) {
		fprintf(stderr, "Error initializing");
		return retcode;
	}

	net_listen(5128, handle_data);

	return moco_cleanup();
}
