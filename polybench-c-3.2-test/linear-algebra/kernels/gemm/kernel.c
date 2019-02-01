/**
* gemm.c: This file is part of the PolyBench/C 3.2 test suite.
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
#include "gemm.h"

/* Main computational kernel. The whole function will be timed,
including the call and return. */
void kernel_gemm(int ni, int nj, int nk,
	DATA_TYPE alpha,
	DATA_TYPE beta,
	DATA_TYPE POLYBENCH_2D(C, NI, NJ, ni, nj),
	DATA_TYPE POLYBENCH_2D(A, NI, NK, ni, nk),
	DATA_TYPE POLYBENCH_2D(B, NK, NJ, nk, nj))
{
	int i, j, k;

#pragma scop
	/* C := alpha*A*B + beta*C */
	for (i = 0; i < _PB_NI; i++)
		for (j = 0; j < _PB_NJ; j++)
		{
			C[i][j] *= beta;
			for (k = 0; k < _PB_NK; ++k)
				C[i][j] += alpha * A[i][k] * B[k][j];
		}
#pragma endscop

}