#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include "Lab3IO.h"
#include "timer.h"

void Usage(char* prog_name);

int thread_count;

int main(int argc, char* argv[]) {
	int i, j, k, size;
	double** Au;
	double* X;
	double temp, error, Xnorm;
	int* index;
	double start, end;

	/* Get number of threads from command line */
	if (argc != 2) Usage(argv[0]);
	thread_count = strtol(argv[1], NULL, 10);
	if (thread_count <= 0) Usage(argv[0]);

	Lab3LoadInput(&Au, &size);

	GET_TIME(start);
	X = CreateVec(size);
	index = malloc(size * sizeof(int));
	for (i = 0; i < size; ++i) {
		index[i] = i;
	}

	if (size == 1) {
		X[0] = Au[0][1] / Au[0][0];
	}
	else{
		/*Gaussian elimination*/
		for (k = 0; k < size - 1; ++k) {
			#pragma omp parallel for shared(Au) private(temp,i,j) num_threads(thread_count)
			for (i = k + 1; i < size; ++i) {
				temp = Au[index[i]][k] / Au[index[k]][k];
				for (j = k; j < size + 1; ++j)
					Au[index[i]][j] -= Au[index[k]][j] * temp;
			}	   
		}
		/*Jordan elimination*/
		for (k = size - 1; k > 0; --k) {
			#pragma omp parallel for private(temp,i) num_threads(thread_count)
			for (i = 0; i < k; i++ ) {
				temp = Au[index[i]][k] / Au[index[k]][k];
				Au[index[i]][k] -= temp * Au[index[k]][k];
				Au[index[i]][size] -= temp * Au[index[k]][size];
			}
		}
		/*solution*/
		#pragma omp parallel for private(k) num_threads(thread_count)
		for (k=0; k< size; ++k) {
			X[k] = Au[index[k]][size] / Au[index[k]][k];
		}
	}
	GET_TIME(end);

	printf("%lf\n", end-start);

	Lab3SaveOutput(X, size, end-start);

	DestroyVec(X);
	DestroyMat(Au, size);
	free(index);
	return 0;
}

void Usage(char* prog_name) {
	fprintf(stderr, "usage: %s <number of threads>\n", prog_name);
	exit(0);
}
