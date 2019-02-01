/**
* gesummv.c: This file is part of the PolyBench/C 3.2 test suite.
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
#include "gesummv.h"

/* Main computational kernel. The whole function will be timed,
including the call and return. */
void kernel_gesummv(int n,
	DATA_TYPE alpha,
	DATA_TYPE beta,
	DATA_TYPE POLYBENCH_2D(A, N, N, n, n),
	DATA_TYPE POLYBENCH_2D(B, N, N, n, n),
	DATA_TYPE POLYBENCH_1D(tmp, N, n),
	DATA_TYPE POLYBENCH_1D(x, N, n),
	DATA_TYPE POLYBENCH_1D(y, N, n))
{
	int i, j;

#pragma scop
	for (i = 0; i < _PB_N; i++)
	{
		tmp[i] = 0;
		y[i] = 0;
		for (j = 0; j < _PB_N; j++)
		{
			tmp[i] = A[i][j] * x[j] + tmp[i];
			y[i] = B[i][j] * x[j] + y[i];
		}
		y[i] = alpha * tmp[i] + beta * y[i];
	}
#pragma endscop

}
