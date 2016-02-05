/*
Header for the Lab 3 IO functions
*/
#pragma once
#include "rational.h"

int Lab3LoadInput(double ***A, int *size);
int Lab3SaveOutput(double* x, int size, double time);
int Lab3FixInput(double ***A, rational ***B, int *size);

double** CreateMat(int NumRow, int NumCol);
int DestroyMat(double** A, int NumRow);
int PrintMat(double** A, int NumRow, int NumCol);
double* CreateVec(int size);
int PrintVec(double* b, int size);
int DestroyVec(double* b);