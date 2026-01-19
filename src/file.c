/* Minimal Linux-only front-end for libmagic. */

#if !defined(__linux__)
#error "This reduced build only supports Linux."
#endif

#include <stdio.h>
#include <stdlib.h>
#include <magic.h>

int
main(int argc, char *argv[])
{
	magic_t m;
	const char *res;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		return 2;
	}

	m = magic_open(MAGIC_NONE);
	if (m == NULL) {
		fprintf(stderr, "magic_open failed\n");
		return 1;
	}

	if (magic_load(m, NULL) != 0) {
		fprintf(stderr, "magic_load failed: %s\n", magic_error(m));
		magic_close(m);
		return 1;
	}

	res = magic_file(m, argv[1]);
	if (res == NULL) {
		fprintf(stdout, "(null)\n");
	} else {
		printf("%s\n", res);
	}

	magic_close(m);
	return 0;
}