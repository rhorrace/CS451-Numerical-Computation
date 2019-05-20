#include "FPToolkit.c"
#include "cubicblend.h"
#include <ctype.h>

void draw_line(double* X, double* Y, int n);
void draw_connected(double* X, double* Y, int n);

int main() {
  int swidth = 700, sheight = 700;
  double** p;
  int i, n;
  char response;
  do {
    printf("# of points (must be 4 or more): ");
    scanf("%d", &n);
    if(n < 4) {
      printf("Error: Need 4 or more points");
    }
  } while(n < 4);
  do{
    printf("Connect the line? (Y/N):");
    scanf(" %c", &response);
    response = toupper(response);
    if(response != 'Y' && response != 'N') {
      printf("Error: not a valid option\n");
    }
  } while(response != 'Y' && response != 'N');
  p = malloc(sizeof(double*) * n);
  for(i = 0;i < n;++i) {
    p[i] = malloc(sizeof(double) * 2);
  }

  G_init_graphics(swidth, sheight);

  G_rgb(0, 0, 0);
  G_clear();

  double X[n], Y[n];

  G_rgb(1, 0, 0);
  for(i = 0;i < n;++i) {
    G_wait_click(p[i]);
    G_fill_circle(p[i][0], p[i][1], 2);
    X[i] = p[i][0];
    Y[i] = p[i][1];
  }

  G_rgb(1, 1, 0);
  if(response == 'Y') {
    draw_connected(X, Y, n);
  }
  else {
    draw_line(X, Y, n);
  }

  int key = G_wait_key();
  G_save_image_to_file("bspline.xwd");

  for(i = 0;i < n;++i) {
    free(p[i]);
    p[i] = NULL;
  }
  free(p);
  p = NULL;

  return 0;
}

void draw_line(double* X, double* Y, int n) {
  int i, key;
  double at, bt, ct, dt, t, x, y;
  for(i = 0;i < n-3;++i) {
    for(t = 0.0;t <= 1.0;t += 0.01) {
      at = a(t);
      bt = b(t);
      ct = c(t);
      dt = d(t);
      x = at * X[i] + bt * X[i+1] + ct * X[i+2] + dt * X[i+3];
      y = at * Y[i] + bt * Y[i+1] + ct * Y[i+2] + dt * Y[i+3];
      G_point(x,y);
    }
    if(i != n-4) {
      key = G_wait_key();
    }
  }
}

void draw_connected(double* X, double* Y, int n) {
  int i, key;
  double at, bt, ct, dt, t, x, y;
  for(i = 0;i < n;++i) {
    for(t = 0.0;t <= 1.0;t += 0.01) {
      at = a(t);
      bt = b(t);
      ct = c(t);
      dt = d(t);
      x = at * X[i%n] + bt * X[(i+1)%n] + ct * X[(i+2)%n] + dt * X[(i+3)%n];
      y = at * Y[i%n] + bt * Y[(i+1)%n] + ct * Y[(i+2)%n] + dt * Y[(i+3)%n];
      G_point(x,y);
    }
    if(i != n-1) {
      key = G_wait_key();
    }
  }
}
