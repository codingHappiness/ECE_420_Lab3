#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include "Lab3IO.h"
#include "timer.h"
#include "rational.h"

double** Aud;
double* Xd;
rational** Au;
rational* X;

void swap(int i, int j) {
	if (i != j) {
		rational* temp = Au[i];
		Au[i] = Au[j];
		Au[j] = temp;
	}
}

int main(int argc, char* argv[]) {
	int i, j, k, size;
	double temp;
	double start, end;

	Lab3LoadInput(&Aud, &size);
	Lab3FixInput(&Aud, &Au, &size);
	
	Xd = CreateVec(size);
	X =  malloc(size * sizeof(rational));

	GET_TIME(start);
	if (size == 1) {
		X[0] = divide(Au[0][1], Au[0][0]);
	}
	else{
		for (j = 0; j < size; j++) {
			//find next row to work on. Call it j.
			for (i = j; i < size; i++) {
				if (Au[i][j].num) {
					swap(i,j);
					break;
				}
			}
			//normalize row j
			rational a = Au[i][j];
			Au[i][j] = (rational){1,1};
			for (i = j+1; i < size; i++) {
				Au[i][j] = divide(Au[i][j], a);
			}

			//collapse this?
			//i = row after current row
			//j = row, column of working index
			//k = current column
			for (i = j+1; i < size; i++) {
				rational a = Au[i][j];
				for (k = 0; k < size; k++) {
					if (k==j) { continue; }
					Au[i][k] = sub(Au[i][k],mul(a,Au[j][k]));
				}
			}
		}
		/*solution*/
		for (k = 0; k < size; k++) {
			Xd[k] = to_double(Au[k][size]);
		}
	}
	GET_TIME(end);

	printf("%lf\n", end-start);

	Lab3SaveOutput(Xd, size, end-start);
	
	DestroyVec(Xd);
	DestroyMat(Aud, size);
	return 0;	
}