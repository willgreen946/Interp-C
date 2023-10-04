#ifndef __INSTRUCTIONS_H__
#define __INSTRUCTIONS_H__

/* Prints to the console */
void print (const char *args);

/* Prints to the console with a newline char */
void print_l (const char *args);

/* Jumps to a specified line */
void jump (const char *args);

#include "instructions.c"

#endif /* __INSTRUCTION_H__ */
