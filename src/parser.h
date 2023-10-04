#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "instructions.h"

struct COMMAND_MAP {
	const char *str;
	void (*fn)(const char *args);
};

/* A mapping of commands to their functions */
struct COMMAND_MAP cmd_map[] = {
	{ "print", print },
	{ "print_l", print_l },
	{ "cmp", NULL },
	{ "jmp", jump },
};

/* Gets rid of whitespace from a string */
char *parser_trim_whitespace (char *str);

/* Gets the first word of a string by looking at first occurence of the delim char */
char *parser_get_cmd (const char *line, const char delim, ssize_t len);

/* Checks that a string matches a valid cmd */
ssize_t parser_is_cmd (const char *cmd);

/* Reads a line of input */
int parser_read_line (const char *line, const size_t len);

#include "parser.c"

#endif /* PARSER_H */
