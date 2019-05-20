#include "quadblend.h"

double a(double t) {
  return 0.5 - t + 0.5 * pow(t, 2);
}


double b(double t) {
  return 0.5 + t - pow(t,2);
}

double c(double t) {
  return 0.5 * pow(t, 2);
}
