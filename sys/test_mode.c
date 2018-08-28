#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "moco.h"
#include "net.h"
#include "test_mode.h"

void
handle_data(unsigned char *data) {
	printf("% 04d\t %04d\n", data[0], data[1]);
}

int
main(int argc, char **argv) {
	net_listen(5128, handle_data);
}
