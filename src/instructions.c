#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "instructions.h"
#include "parser.h"

/* Removes double quotes from string */
char *format_rm_dq (const char *line) {
	char *str = (char*)malloc(strlen(line));
	while (*line++)
		if (*line != '"')
			strncat(str, *&line, 1);

	return str;
}

/* Checks for special chars and double quotes */
char *format_str (const char *line) {
	char *str = format_rm_dq(line);
	char *nstr = (char*)malloc(strlen(line));

	while (*str++) {
		if (*str == '\\')
			switch (*str) {
				case 'n':
					strncat(nstr, "\n", 1);
					*str++;
					break;
			}

		else strncat(nstr, *&str, 1);
	}

	free(str);
	return nstr;
}

/* Prints text to the console */
void print (const char *args) {
	char *str = format_str(args);
	fprintf(stdout, "%s", str);
	free(str);
}

/* Prints text to the console with a newline */
void print_l (const char *args) {
	char *str = format_rm_dq(args);
	fprintf(stdout, "%s\n", str);
	free(str);
}

/* Prints text to the standard error stream */
void print_e (const char *args) {
	char *str = format_rm_dq(args);
	fprintf(stderr, "%s\n", str);
	free(str);
}

void jump (const char *args) {

}
