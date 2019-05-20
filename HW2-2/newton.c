#include "newton.h"

// f function
double complex f(struct poly nomial, double complex x) {
  // If 0 degree
  if(nomial.deg == 0) {
    nomial.aps[0] = nomial.a[0];
    return nomial.a[0];
  }

  // Set aps' coefficients and calculate result
  int i;
  for(i = nomial.deg;i > 0;--i) {
    if(i == nomial.deg) {
      nomial.aps[i-1] = nomial.a[i];
      continue;
    }
    nomial.aps[i-1] = (nomial.aps[i] * x) + nomial.a[i];
  }

  // Return calculated result
  return nomial.aps[0] * x + nomial.a[0];
}

// f' function
double complex fp(struct poly nomial, double complex x) {
  int i;
  int res;

  // If 0 degree
  if(nomial.deg == 0) {
    return nomial.aps[0];
  }

  // Calculate result
  for(i = nomial.deg-1;i >= 0;--i) {
    if(i == nomial.deg-1) {
      res = nomial.aps[i];
      continue;
    }
    res = (res * x) + nomial.aps[i];
  }

  // Return result
  return res;
}

// Newton's method function
double complex newton(struct poly nomial, double complex x) {
  double complex temp, fx, fpx;
  int flag = 0;
  // Calculate root starting with x (user guess)
  do {
    fx = f(nomial, x);
    fpx = fp(nomial, x);
    if(abs(creal(fpx)) <= MARGIN && abs(creal(fpx)) <= MARGIN) {
      break;
    }
    x = x - fx/fpx;
    temp = f(nomial, x);

    if(isnan(creal(x)) || isnan(cimag(x))) {
      printf("Error: Guess diverges/invalidates,try another guess.\n");
      exit(1);
    }
    if(isinf(creal(x)) || isinf(cimag(x))) {
      printf("Error: Guess diverges/invalidates, try another guess.\n");
      exit(2);
    }
    if(abs(creal(temp)) <= MARGIN && abs(cimag(temp)) <= MARGIN) {
      flag = 1;
    }
  } while(flag == 0);
  return x;
}

// Evaluate function
int eval(struct poly nomial, double complex x) {
  double complex temp = f(nomial,x);
  double tr = creal(temp), ti = cimag(temp);
  return (abs(tr) <= MARGIN && abs(ti) <= MARGIN);
}

// Display a coefficents
void disp_a(struct poly nomial) {
  int i;
  for(i = nomial.deg;i >= 0;--i) {
    printf("%lf + %lfI", creal(nomial.a[i]), cimag(nomial.a[i]));
    if(i == 0) {
      printf("\n");
    }
    else {
      printf(" | ");
    }
  }
}

// Display a' coefficients
void disp_aps(struct poly nomial) {
  int i;
  if(nomial.deg == 0) {
    printf("%lf + %lfI\n", creal(nomial.aps[i]), cimag(nomial.aps[i]));
    return;
  }
  for(i = nomial.deg-1;i >= 0;--i) {
    printf("%lf + %lfI", creal(nomial.aps[i]), cimag(nomial.aps[i]));
    if(i == 0) {
      printf("\n");
    }
    else {
      printf(" | ");
    }
  }
}
