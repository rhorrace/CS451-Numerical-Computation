#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#define MARGIN 0.00000000000000000000000000001

// Polynomial struct
struct poly {
  double complex* a;
  double complex* aps;
  double complex* roots;
  int deg;
};

//f using synthetic division
double complex f(struct poly nomial, double complex x);

//f' using synthetic division
double complex fp(struct poly nomial, double complex x);

// Newton's method function
double complex newton(struct poly nomial, double complex x);

// Evaluate function
int eval(struct poly nomial, double complex x);

void disp_a(struct poly nomial);

void disp_aps(struct poly nomial);
