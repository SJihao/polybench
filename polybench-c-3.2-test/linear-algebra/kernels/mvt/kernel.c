/**
* mvt.c: This file is part of the PolyBench/C 3.2 test suite.
*
*
* Contact: Louis-Noel Pouchet <pouchet@cse.ohio-state.edu>
* Web address: http://polybench.sourceforge.net
*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

/* Include polybench common header. */
#include <polybench.h>

/* Include benchmark-specific header. */
/* Default data type is double, default size is 4000. */
#include "mvt.h"

/* Main computational kernel. The whole function will be timed,
including the call and return. */
static
void kernel_mvt(int n,
	DATA_TYPE POLYBENCH_1D(x1, N, n),
	DATA_TYPE POLYBENCH_1D(x2, N, n),
	DATA_TYPE POLYBENCH_1D(y_1, N, n),
	DATA_TYPE POLYBENCH_1D(y_2, N, n),
	DATA_TYPE POLYBENCH_2D(A, N, N, n, n))
{
	int i, j;

#pragma scop
	for (i = 0; i < _PB_N; i++)
		for (j = 0; j < _PB_N; j++)
			x1[i] = x1[i] + A[i][j] * y_1[j];
	for (i = 0; i < _PB_N; i++)
		for (j = 0; j < _PB_N; j++)
			x2[i] = x2[i] + A[j][i] * y_2[j];
#pragma endscop

}
