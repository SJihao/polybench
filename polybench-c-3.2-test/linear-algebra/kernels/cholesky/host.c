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


/* Array initialization. */
static
void init_array(int n,
	DATA_TYPE POLYBENCH_1D(p, N, n),
	DATA_TYPE POLYBENCH_2D(A, N, N, n, n))
{
	int i, j;

	for (i = 0; i < n; i++)
	{
		p[i] = 1.0 / n;
		for (j = 0; j < n; j++)
			A[i][j] = 1.0 / n;
	}
}


/* DCE code. Must scan the entire live-out data.
Can be used also to check the correctness of the output. */
static
void print_array(int n,
	DATA_TYPE POLYBENCH_2D(A, N, N, n, n))

{
	int i, j;

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++) {
			fprintf(stderr, DATA_PRINTF_MODIFIER, A[i][j]);
			if ((i * N + j) % 20 == 0) fprintf(stderr, "\n");
		}
}




int main(int argc, char** argv)
{
	/* Retrieve problem size. */
	int n = N;

	/* Variable declaration/allocation. */
	POLYBENCH_2D_ARRAY_DECL(A, DATA_TYPE, N, N, n, n);
	POLYBENCH_1D_ARRAY_DECL(p, DATA_TYPE, N, n);


	/* Initialize array(s). */
	init_array(n, POLYBENCH_ARRAY(p), POLYBENCH_ARRAY(A));

	/* Start timer. */
	polybench_start_instruments;

	/* Run kernel. */
	kernel_cholesky(n, POLYBENCH_ARRAY(p), POLYBENCH_ARRAY(A));

	/* Stop and print timer. */
	polybench_stop_instruments;
	polybench_print_instruments;

	/* Prevent dead-code elimination. All live-out data must be printed
	by the function call in argument. */
	polybench_prevent_dce(print_array(n, POLYBENCH_ARRAY(A)));

	/* Be clean. */
	POLYBENCH_FREE_ARRAY(A);
	POLYBENCH_FREE_ARRAY(p);

	return 0;
}
