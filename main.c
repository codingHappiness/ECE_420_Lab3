#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include "Lab3IO.h"
#include "timer.h"

#define TOL 0.0005

int thread_count;

int main(int argc, char* argv[])
{
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
            /*Pivoting*/
            temp = 0;
            j=0;
            #pragma omp parallel for shared(Au) private(temp) num_threads(thread_count)
            for (i = k; i < size; ++i) {
                if (temp < Au[index[i]][k] * Au[index[i]][k]){
                    temp = Au[index[i]][k] * Au[index[i]][k];
                    j = i;
                }
            }
            if (j != k)/*swap*/{
                i = index[j];
                index[j] = index[k];
                index[k] = i;
            }
            /*calculating*/
            #pragma omp parallel for shared(Au) private(temp) num_threads(thread_count)
            for (i = k + 1; i < size; ++i) {
                temp = Au[index[i]][k] / Au[index[k]][k];
                for (j = k; j < size + 1; ++j) {
                    Au[index[i]][j] -= Au[index[k]][j] * temp;
                }
            }       
        }
        /*Jordan elimination*/
        //#pragma omp parallel for shared(Au) private(temp) num_threads(thread_count) //collapse(2)
        for (k = size - 1; k > 0; --k) {
            #pragma omp parallel for shared(Au) private(temp) num_threads(thread_count)
            for (i = k - 1; i >= 0; --i ) {
                temp = Au[index[i]][k] / Au[index[k]][k];
                Au[index[i]][k] -= temp * Au[index[k]][k];
                Au[index[i]][size] -= temp * Au[index[k]][size];
            } 
        }
        /*solution*/
        #pragma omp parallel for shared(Au) num_threads(thread_count)
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
