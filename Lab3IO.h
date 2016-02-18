/*
Header for the Lab 3 IO functions
*/
#pragma once

int Lab3LoadInput(double ***A, int *size);
int Lab3SaveOutput(double* x, int size, double time);

double** CreateMat(int NumRow, int NumCol);
int DestroyMat(double** A, int NumRow);
int PrintMat(double** A, int NumRow, int NumCol);
double* CreateVec(int size);
int PrintVec(double* b, int size);
int DestroyVec(double* b);