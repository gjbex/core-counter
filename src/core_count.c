/*
 * core_count prints the number of cores available to OpenMP programs
 * Copyright (C) 2013  Geert Jan BEX (geertjan.bex@uhasselt.be)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include "cl_params.h"

int main(int argc, char *argv[]) {
    Params params;
    initCL(&params);
    parseCL(&params, &argc, &argv);
    if (params.verbose) {
        dumpCL(stderr, "# ", &params);
    }
#ifdef _OPENMP
#pragma omp parallel
    if (omp_get_thread_num() == 0) {
        if (params.num_threads) {
            printf("%d", omp_get_num_threads());
        } else {
            printf("%d", omp_get_num_procs());
        }
    }
#else
    errx(EXIT_FAILURE, "application not compiled for OpenMP");
#endif
    return EXIT_SUCCESS;
}

