#include "FPToolkit.c"
#include "runge.h"
#include <ctype.h>
#include "unistd.h"

int main() {
  int swidth = 600, sheight = 600;
  double** p;
  int i, k, amnt, key;
  char res;

  printf("Read from a file? (Y/N): ");
  scanf("%c", &res);

  res = toupper(res);

  if(res == 'Y') {
    p = read_from_file(&amnt);
    if(!p) {
      exit(0);
    }
  }
  else {
    printf("How many points? ");
    scanf("%d", &amnt);
    p = malloc(sizeof(double*)* amnt);
    for(i = 0;i < amnt;++i) {
      p[i] = malloc(sizeof(double) * 2);
    }
  }

  G_init_graphics(swidth, sheight);

  G_rgb(0, 0, 0);
  G_clear();

  G_rgb(1, 0, 0);
  for(i = 0;i < amnt;++i) {
    if(res != 'Y') {
      G_wait_click(p[i]);
    }
    G_fill_circle(p[i][0],p[i][1], 2);
  }

  double X[amnt], Y[amnt];

  for(i = 0;i < amnt;++i) {
    X[i] = p[i][0];
    Y[i] = p[i][1];
  }

  int m = (amnt - 1) * 2;
  int n = m+1;
  double** M = create_matrix(m, n);

  init_matrix(M, m, n, X, Y, amnt);

  display(M, m, n);

  rref(M, m, n);

  key = G_wait_key();

  G_rgb(1, 1, 0);

  double x,y;
  int A = 0, B = A+1;
  for(i = 0;i < amnt-1;++i) {
    for(x = X[i];x <= X[i+1];x+=0.1) {
      double a = Y[i+1] - Y[i];
      double b = X[i+1] - X[i];
      double c = a/b;
      y = Y[i] + c*(x-X[i]);
      y += M[A][n-1] * ((x - X[i]) * (x - X[i+1]));
      y += M[B][n-1] * (pow(x - X[i], 2) * (x - X[i+1]));
      G_point(x,y);
    }
    A += 2;
    B += 2;
    usleep(750);
  }

  key = G_wait_key();

  G_save_image_to_file("spline.xwd");

  for(i = 0;i < amnt;++i) {
    free(p[i]);
    p[i] = NULL;
  }
  free(p);
  p = NULL;

  return 0;
}
