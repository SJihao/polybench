/**
* cholesky.c: This file is part of the PolyBench/C 3.2 test suite.
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
#include "cholesky.h"

/* Main computational kernel. The whole function will be timed,
including the call and return. */
void kernel_cholesky(int n,
	DATA_TYPE POLYBENCH_1D(p, N, n),
	DATA_TYPE POLYBENCH_2D(A, N, N, n, n))
{
	int i, j, k;

	DATA_TYPE x;

#pragma scop
	for (i = 0; i < _PB_N; ++i)
	{
		x = A[i][i];
		for (j = 0; j <= i - 1; ++j)
			x = x - A[i][j] * A[i][j];
		p[i] = 1.0 / sqrt(x);
		for (j = i + 1; j < _PB_N; ++j)
		{
			x = A[i][j];
			for (k = 0; k <= i - 1; ++k)
				x = x - A[j][k] * A[i][k];
			A[j][i] = x * p[i];
		}
	}
#pragma endscop

}
