/**
* bicg.c: This file is part of the PolyBench/C 3.2 test suite.
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
#include "bicg.h"

/* Main computational kernel. The whole function will be timed,
including the call and return. */
void kernel_bicg(int nx, int ny,
	DATA_TYPE POLYBENCH_2D(A, NX, NY, nx, ny),
	DATA_TYPE POLYBENCH_1D(s, NY, ny),
	DATA_TYPE POLYBENCH_1D(q, NX, nx),
	DATA_TYPE POLYBENCH_1D(p, NY, ny),
	DATA_TYPE POLYBENCH_1D(r, NX, nx))
{
	int i, j;

#pragma scop
	for (i = 0; i < _PB_NY; i++)
		s[i] = 0;
	for (i = 0; i < _PB_NX; i++)
	{
		q[i] = 0;
		for (j = 0; j < _PB_NY; j++)
		{
			s[j] = s[j] + r[i] * A[i][j];
			q[i] = q[i] + A[i][j] * p[j];
		}
	}
#pragma endscop

}
