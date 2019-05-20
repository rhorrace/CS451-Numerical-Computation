#include "newton.h"

int main() {
  struct poly nomial;
  double a,b;
  int i, j, choice, count;
  double complex guess, res;
  do {
    printf("Enter degree of polynomial: ");
    scanf("%d", &nomial.deg);
    if(nomial.deg < 1) {
      printf("Error: Degree must be >= 1\n");
    }
  } while(nomial.deg < 1);

  // initialize a, aps, and roots
  nomial.a = malloc(sizeof(double complex) * (nomial.deg+1));
  nomial.aps = malloc(sizeof(double complex) * nomial.deg);
  nomial.roots = malloc(sizeof(double complex) * nomial.deg);

  // Get coefficients from user
  for(i = nomial.deg;i >= 0;--i) {
    do {
      printf("1) real 2) imaginary: ");
      scanf("%d", &choice);
      if(choice != 1 && choice != 2) {
        printf("Error: not an option\n");
      }
    } while(choice != 1 && choice != 2);
    if(choice == 1) {
      printf("Enter coefficient A%d: ", i);
      scanf("%lf", &a);
      b = 0;
    }
    else {
      printf("Enter coefficient A%d (in form a+bI): ", i);
      scanf("%lf+%lfI", &a,&b);
    }
    nomial.a[i] = CMPLX(a,b);
  }

  // Print polynomial
  for(i = nomial.deg;i >= 0;--i) {
    if(cimag(nomial.a[i]) == 0) {
      printf("%lf", creal(nomial.a[i]));
    }
    else {
      printf("(%lf+%lfI)", creal(nomial.a[i]), cimag(nomial.a[i]));
    }
    if(i == 0) {
      printf("\n");
    }
    else {
      printf("x^%d + ", i);
    }
  }

  // Read user's guess
  printf("Enter your guess (in form a+bI): ");
  scanf("%lf+%lfI", &a, &b);
  guess = CMPLX(a, b);

  res = f(nomial, guess);
  a = abs(creal(res));
  b = abs(cimag(res));
  if(a <= MARGIN && b<= MARGIN) {
    printf("Your guess is either correct or really close\n");
  }
  else {
    printf("Your guess is not close\n.");
  }

  // Calculate roots
  int degree = nomial.deg;
  for(i = 0;i < degree;++i) {
    res = newton(nomial, guess);
    nomial.roots[i] = res;
    // Set a to aps
    free(nomial.a);
    // Lower degree
    --nomial.deg;
    nomial.a = malloc(sizeof(double complex) * (nomial.deg+1));
    for(j = nomial.deg;j >= 0;--j) {
      nomial.a[j] = nomial.aps[j];
    }
    free(nomial.aps);
    // If 0 degree
    if(nomial.deg == 0) {
      nomial.aps = malloc(sizeof(double complex) * 1);
    }
    else {
      nomial.aps = malloc(sizeof(double complex) * nomial.deg);
    }
  }

  // Display calculated roots
  printf("Calculated Roots:\n");
  for(i = 0;i < degree;++i) {
    printf("%20.16lf + %20.16lfI\n", creal(nomial.roots[i]), cimag(nomial.roots[i]));
  }

  // Free allocated arrays
  if(nomial.a) {
    free(nomial.a);
    nomial.a = NULL;
  }
  if(nomial.aps) {
    free(nomial.aps);
    nomial.aps = NULL;
  }
  free(nomial.roots);
  nomial.roots = NULL;
  return 0;
}
