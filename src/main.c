#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "map.h"
#include "parser.h"

/* Opens up a file for reading */
int ropen_file (const char *fn, FILE **fp) {
	if ((*fp = fopen(fn, "r")) == NULL) {
		printf("FILE ERROR (%s)\n", fn);
		return 1;
	}
	return 0;
}

/* Closes a file stream */
void close_file (FILE **fp) {
	fclose(*fp);
}

/* Reads file line by line and passes the string to parser */
int read_file (char *buf, size_t len, FILE *stream) {
	while (fgets(buf, len, stream)) {
		if (parser_read_line(buf, len))
			return 1;

		memset(buf, 0, strlen(buf));
	}
	return 0;
}

/* Loops through the opening and reading process */
int global_entry (const char **argv) {
	FILE *fp;
	char buf[1024];

	/* Open all the files */
	while (*++argv) {
		if (ropen_file(*argv, &fp))
			return EXIT_FAILURE;

		if (read_file(buf, 1024, fp))
			return EXIT_FAILURE;

		close_file(&fp);
	}
	return EXIT_SUCCESS;
}

int main (int argc, const char **argv) {
	return global_entry(argv);
}
