#include "newton.h"

/*
  Horrace, Robert
  CS 451
  This is Homework 2.
  This calculate newton's method
  by utilizing the formula
  Xn+1 = Xn - f(Xn)/f'(Xn).
  The program captures the degree of
  a user's polynomial and captures
  the coefficients of each degree,
  meaning formulas are int the form
  AnX^n + An-1X^n-1 + ... + A0X^0.
*/


int main() {
  int i, choice;
  double x, a, b, res;
  double complex cx, cres;
  struct poly nomial;

  // Initialize polynomial variables
  nomial.deg = 0;
  nomial.a = NULL;
  nomial.a = NULL;

  // User enters a valid degree (greater than 0)
  do {
    printf("Enter degree of polynomial: ");
    scanf("%d", &nomial.deg);
    printf("%d\n", nomial.deg);
    if("Error: degree must be 1 or greater.\n");
  } while(nomial.deg < 1);

  // set up array of coefficients for polynomial
  nomial.a = malloc(sizeof(double) * (nomial.deg + 1));

  // Get coefficients from the user, from left to right
  printf("Enter coefficients, starting from highest degree to lowest degree\n");
  for(i = nomial.deg;i >= 0;--i) {
    printf("Enter a%d: ", i);
    scanf("%lf", &nomial.a[i]);
  }

  // Derive the polynomial to f' coefficients
  derive(&nomial);

  // Ask user if guess is real or complex form
  printf("Is your guess in real form or complex form?\n");
  do{
    printf("1) Real 2) Complex: ");
    scanf("%d", &choice);
  }while(choice != 1 && choice != 2);

  // Get an x value, calculate root
  if(choice == 1){
    printf("Enter an x value: ");
    scanf("%lf",&x);
    printf("Entered guess: %20.16lf\n", x);
    res = newton(nomial, x);
    printf("Calculated root: %20.16lf\n", res);
  }
  else {
    printf("Enter x's value (in form a+bi): ");
    scanf("%lf+%lfi", &a, &b);
    cx = CMPLX(a,b);
    printf("Entered guess: %20.16lf + %20.lfI\n", creal(cx), cimag(cx));
    cres = cnewton(nomial, cx);
    printf("Calculated root: %20.16lf + %20.lfI\n", creal(cres), cimag(cres));
  }

  // Calculate root (might not be correct)

  free(nomial.a);
  free(nomial.ap);
  nomial.a = NULL;
  nomial.ap = NULL;
  return 0;
}
