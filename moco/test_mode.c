#include <stdio.h>
#include <stdlib.h>

int
test_init() {
	return EXIT_SUCCESS;
}

int
test_cleanup() {
	return EXIT_SUCCESS;
}

void
test_momo(signed char left, signed char right) {
	printf("%04d %04d\n", left, right);
}
