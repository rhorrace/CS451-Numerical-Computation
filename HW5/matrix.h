#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
  Horrace, Robert
  This is the header file
  that holds the function
  declarations.
*/

// Defined min/max function
#define min(a, b) ((a<b)?a:b)
#define max(a, b) ((a>b)?a:b)

// Create matrix function
double** create_matrix(int m, int n);

// Display matrix function
void display_matrix(double** matrix, int m, int n);

//Set matrix function
void set_matrix(double** matrix, int m, int n);

// greatest common divisor function
int gcd(int a, int b);

// least common multiple function
int lcm(int a, int b);

// find maximum row function
int find_max_row(double** matrix, int r, int c, int m);

// row swapping function
void row_swap(double** matrix, int r1, int r2, int n);

// upper triangle form function
void upper_triangle(double** matrix, int m, int n);

// lower triangle form function
void lower_triangle(double** matrix, int m, int n);

// Adjusting matrix function
void adjust(double** matrix, int m, int n);

// Simplify matrix function
void simplify(double** matrix, int m, int n);

void rref(double** matrix, int m, int n);
