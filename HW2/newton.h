#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#define ERR 0.00000000001

// Holds degree and polynomial coefficients
struct poly {
  int deg;
  double* a;
  double* ap;
};

// Derive function
void derive(struct poly* nomial);

// function f taking polynomial coefficients and x
double f(struct poly nomial, double x);
double complex cf(struct poly nomial, double complex x);

// function f', derivative of f
double fprime(struct poly nomial, double x);
double complex cfprime(struct poly nomial, double complex x);

// function for newton's method
double newton(struct poly nomial, double x);
double complex cnewton(struct poly nomial, double complex x);
