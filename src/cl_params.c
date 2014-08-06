#include <err.h>
#include <stdlib.h>
#include <string.h>

#include "cl_params.h"
#include "cl_params_aux.h"

#define MAX_CL_OPT_LEN 128
#define MAX_CL_LINE_LEN 1024

void initCL(Params *params) {
	params->num_threads = false;
	params->verbose = false;
}

void parseCL(Params *params, int *argc, char **argv[]) {
	char *argv_str;
	int i = 1;
	while (i < *argc) {
		if (!strncmp((*argv)[i], "-num_threads", 13)) {
			params->num_threads = true;
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-verbose", 9)) {
			params->verbose = true;
			i++;
			continue;
		}
		break;
	}
	if (i > 1) {
		(*argv)[i - 1] = (*argv)[0];
		*argv = &((*argv)[i - 1]);
		*argc -= (i - 1);
	}
}

void parseFileCL(Params *params, char *fileName) {
	char line_str[MAX_CL_LINE_LEN];
	char argv_str[MAX_CL_LINE_LEN];
	FILE *fp;
	if (!(fp = fopen(fileName, "r"))) {
		fprintf(stderr, "### error: can not open file '%s'\n", fileName);
		exit(EXIT_CL_FILE_OPEN_FAIL);
	}
	while (fgets(line_str, MAX_CL_LINE_LEN, fp)) {
		if (isCommentCL(line_str)) continue;
		if (isEmptyLineCL(line_str)) continue;
		if (sscanf(line_str, "num_threads = %[^\n]", argv_str) == 1) {
			if (!1) {
				fprintf(stderr, "### error: invalid value for option '-num_threads' of type bool\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			if (!strncmp("false", argv_str, 6)) {
				params->num_threads = false;
			} else if (!strncmp("true", argv_str, 5)) {
				params->num_threads = true;
			} else {
				params->num_threads = atoi(argv_str);
			}
			continue;
		}
		if (sscanf(line_str, "verbose = %[^\n]", argv_str) == 1) {
			if (!1) {
				fprintf(stderr, "### error: invalid value for option '-verbose' of type bool\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			if (!strncmp("false", argv_str, 6)) {
				params->verbose = false;
			} else if (!strncmp("true", argv_str, 5)) {
				params->verbose = true;
			} else {
				params->verbose = atoi(argv_str);
			}
			continue;
		}
		fprintf(stderr, "### warning, line can not be parsed: '%s'\n", line_str);
	}
	fclose(fp);
}

void dumpCL(FILE *fp, char prefix[], Params *params) {
	fprintf(fp, "%snum_threads = %d\n", prefix, params->num_threads);
	fprintf(fp, "%sverbose = %d\n", prefix, params->verbose);
}

void finalizeCL(Params *params) {
}