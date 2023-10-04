#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "parser.h"

typedef unsigned short parser_type_t;

/* Trims whitespace from a string */
char *parser_trim_whitespace (char *str) {
	char *result;

	while (isspace((unsigned char) *str)) str++;

	if (*str)
		return str; /* All whitespace */

	/* Trim whitespace */
	result = str + strlen(str) - 1;
	while (result > str && isspace((unsigned char)*result)) result--;

	result[1] = '\0';
	return str;
}

/* Removes \n char at the end of the string */
char *parser_rm_newline (const char *line) {
	char *newline = (char*)malloc(strlen(line));

	while (*line) {
		if (*line != '\n')
			strncat(newline, *&line, 1);
		*line++;
	}

	return newline;
}

/* Returns char * to first word in string and trims whitespace */
char *parser_get_cmd (const char *line, const char delim, ssize_t len) {
	char *cmd = (char*)malloc(len);

	do {
		strncat(cmd, *&line, 1);
	} while (*++line != delim);

	cmd = parser_trim_whitespace(cmd);
	return cmd;
}

ssize_t parser_is_cmd (const char *cmd) {
	for (size_t i = 0; cmd_map[i].str; i++)
		if (!strncmp(cmd_map[i].str, cmd, strlen(cmd_map[i].str)))
			return i;

	return -1;
}

/* Returns unseperated args by removing whitespace */
char *parser_get_args (const char *line, const char delim, const size_t len) {
	char *args = (char*)malloc(len);

	while (*++line != delim)
		;

	while (*line++)
		strncat(args, *&line, 1);

	args = parser_trim_whitespace(args);
	args = parser_rm_newline(args);
	return args;
}

void parser_check_call (const char *args, const size_t index) {
	cmd_map[index].fn(args);
}

int parser_read_line (const char *line, const size_t len) {
	char *cmd, *args;
	ssize_t cmd_index = 0;

	/* Get the instruction/command */
	if ((cmd = parser_get_cmd(line, ':', len)) == NULL)
		return 1;

	if ((args = parser_get_args(line, ':', len)) == NULL)
		return 1;

	/* TODO Fix this annoying hack with 13 instead of -1 */
	if ((cmd_index = parser_is_cmd(cmd)) == 13) {
		fprintf(stderr, "-E No such function %s\n", cmd);
		return 1;
	}

	parser_check_call(args, cmd_index);

	memset(cmd, 0, strlen(cmd));
	memset(args, 0, strlen(args));
	free(cmd);
	free(args);
	return 0;
}
