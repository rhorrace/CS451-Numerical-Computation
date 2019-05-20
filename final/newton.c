#include "newton.h"

#define 0.000001

double complex f(double complex x) {
  return cpow(x, CMPLX(4,0)) - 1;
}

double complex fp(double complex x) {
  return 4 * cpow(x, CMPLX(3,0));
}

int newton(double complex x) {
  double complex res;
  double rres, ires;
  double complex one = CMPLX(1,0), none = CMPLX(-1,0);
  double complex i = CMPLX(0,1), ni = CMPLX(0,-1);
  do {
    x -= f(x)/fp(x);
    res = f(x);
    rres = creal(res);
    ires = cimag(res);
  } while(rres >= ERR || ires >= ERR);
  double complex space1 = cabs();
  double complex space2;
  double complex space3;
  double complex space4;
}
