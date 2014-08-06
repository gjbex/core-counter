#ifndef CL_PARAMS_HDR
#define CL_PARAMS_HDR

#include <stdbool.h>
#include <stdio.h>

typedef struct {
	bool num_threads;
	bool verbose;
} Params;

void initCL(Params *params);
void parseCL(Params *params, int *argc, char **argv[]);
void parseFileCL(Params *params, char *fileName);
void dumpCL(FILE *fp, char prefix[], Params *params);
void finalizeCL(Params *params);

#endif