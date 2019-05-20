#include "cubicblend.h"

double a(double t) {
  return (1.0 - 3.0 * t + 3.0 * pow(t, 2) - pow(t, 3)) / 6.0;
}

double b(double t) {
  return (4.0 - 6.0 * pow(t, 2) + 3.0 * pow(t, 3)) / 6.0;
}

double c(double t) {
  return (1.0 + 3.0 * t + 3.0 * pow(t, 2) - 3.0 * pow(t, 3)) / 6.0;
}

double d(double t) {
  return pow(t, 3) / 6.0;
}
