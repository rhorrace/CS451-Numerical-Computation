/*
  Horrace, Robert
  CS451
  This program calculates a solution of a
  function using interval bisection.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ERR 0.000001 // Margin of error

// Function
double f(double x) {
  return x * x - 10;
}

// Interval bisection
int bisection(double l, double u) {
  // Establish midpoint
  double c = l;
  // Find midpoint by bisecting. repeat
  while((u - l) >= ERR) {
    c = (l + u) / 2;
    if(f(c) == 0.0) {
      break;
    }
    else if(f(c) * f(l) < 0) {
      u = c;
    }
    else {
      l = c;
    }
  }
  // Root found (might not be correct)
  printf("Root is: %f\n", c);
  return 1;
}

int main() {
  double l;
  double u;
  do {
    printf("Enter lower and upper bound (separated by a space): ");
    scanf("%lf %lf", &l, &u);
    if(u < l) {
      printf("Error: upper bound must be greater than lower bound\n");
    }
  } while(u < l);
  printf("l = %f, u = %f\n", l, u);
  bisection(l, u);
  return 0;
}
