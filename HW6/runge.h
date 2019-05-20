#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double** create_matrix(int m, int n);

void init_matrix(double** M, int m, int n, double* X, double* Y, int amnt);

void rref(double** M, int m, int n);

void display(double** M, int m, int n);

double** read_from_file(int* amnt);
