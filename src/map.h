#ifndef __MAP_H__
#define __MAP_H__

#include <stdint.h>

struct SECTION {
	const char *name;
	const char *instructions;
};

struct VARIABLE {
	char *var;
	uint8_t type;
};

struct MAP {
	struct SECTION section;
	struct VARIABLE variable;
};

struct MAP file_map[];

#include "map.c"

#endif /* MAP_H */
