#include "FPToolkit.c"
#include "newton.h"

int main() {
  int sheight = 700, swidth = 700;
  G_init_graphics(swidth, sheight);
  G_rgb(0.5, 0.5, 0.5);
  G_clear();
  G_rgb(0, 0, 0);
  int key = G_wait_key();
  return 0;
}
