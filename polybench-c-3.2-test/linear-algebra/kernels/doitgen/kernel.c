/**
* doitgen.c: This file is part of the PolyBench/C 3.2 test suite.
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
#include "doitgen.h"

/* Main computational kernel. The whole function will be timed,
including the call and return. */
void kernel_doitgen(int nr, int nq, int np,
	DATA_TYPE POLYBENCH_3D(A, NR, NQ, NP, nr, nq, np),
	DATA_TYPE POLYBENCH_2D(C4, NP, NP, np, np),
	DATA_TYPE POLYBENCH_3D(sum, NR, NQ, NP, nr, nq, np))
{
	int r, q, p, s;

#pragma scop
	for (r = 0; r < _PB_NR; r++)
		for (q = 0; q < _PB_NQ; q++) {
			for (p = 0; p < _PB_NP; p++) {
				sum[r][q][p] = 0;
				for (s = 0; s < _PB_NP; s++)
					sum[r][q][p] = sum[r][q][p] + A[r][q][s] * C4[s][p];
			}
			for (p = 0; p < _PB_NR; p++)
				A[r][q][p] = sum[r][q][p];
		}
#pragma endscop

}
