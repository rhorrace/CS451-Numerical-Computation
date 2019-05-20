#include "newton.h"

void derive(struct poly* nomial) {
  // If polynomial is NULL
  if(!nomial) {
    return;
  }
  int i;
  // deriving function coefficients for f' coefficients
  nomial->ap = malloc(sizeof(double) * nomial->deg);
  for(i = nomial->deg;i > 0;--i) {
    nomial->ap[i-1] = nomial->a[i] * i;
  }
}

double f(struct poly nomial, double x) {
  int i;
  double res = 0;
  // Calculate result of f(x)
  for(i = nomial.deg;i >= 0;--i) {
    if(nomial.a[i] != 0) {
      res += (nomial.a[i] * pow(x, i));
    }
  }
  return res;
}

double complex cf(struct poly nomial, double complex x) {
  int i;
  double complex res = 0;
  // Calculate result of f(x)
  for(i = nomial.deg;i >= 0;--i) {
    if(nomial.a[i] != 0) {
      res += (nomial.a[i] * cpow(x, i));
    }
  }
  return res;
}

double fprime(struct poly nomial, double x) {
  int i;
  double res = 0;
  // Calculate result of f'(x)
  for(i = nomial.deg-1;i >= 0;--i) {
    if(nomial.ap[i] != 0) {
      res += (nomial.ap[i] * pow(x, i));
    }
  }
  return res;
}

double complex cfprime(struct poly nomial, double complex x) {
  int i;
  double complex res = 0;
  // Calculate result of f'(x)
  for(i = nomial.deg-1;i >= 0;--i) {
    if(nomial.ap[i] != 0) {
      res += (nomial.ap[i] * cpow(x, i));
    }
  }
  return res;
}

double newton(struct poly nomial, double x) {
  // Calculate f(root) = 0 (might not always work)
  do {
    x = x - f(nomial, x)/fprime(nomial, x);
  } while(f(nomial, x) >= ERR); // Cannot be >= 0, due to infinite loop problem
  return x;
}

double complex cnewton(struct poly nomial, double complex x) {
  double complex res;
  double rres, ires;
  // Calculate cf(root) = 0 (might not always work)
  do {
    x = x - cf(nomial, x)/cfprime(nomial, x);
    res = cf(nomial, x);
    rres = creal(res);
    ires = cimag(res);
  } while(rres >= ERR || ires >= ERR);
  return x;
}
