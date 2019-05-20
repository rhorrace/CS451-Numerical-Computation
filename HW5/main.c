#include "matrix.h"
#include "FPToolkit.c"

int main() {
  int swidth = 600, sheight = 600, i, j, k, deg, amnt;
  int key;

  printf("level of degree: ");
  scanf("%d", &deg);
  printf("# of points: ");
  scanf("%d", &amnt);

  int m = deg+1, n = deg+2;

  printf("Allocating points\n");
  double** p = malloc(sizeof(double*) * amnt);
  for(k = 0;k < amnt;++k) {
    p[k] = malloc(sizeof(double) * 2);
  }


  G_init_graphics(swidth, sheight);

  G_rgb(0.3,0.3,0.3);
  G_clear();

  G_rgb(1,0,0);
  for(k = 0;k < amnt;++k) {
    G_wait_click(p[k]);
    G_fill_circle(p[k][0], p[k][1], 3);
  }

  key = G_wait_key();

  printf("Creating matrix\n");
  double** M = create_matrix(m, n);

  for(i = 0;i < m;++i) {
    for(j = 0;j < m;++j) {
      if(i == 0 && j == 0) {
        M[i][j] = amnt;
      }
      else {
        M[i][j] = 0;
        for(k = 0;k < amnt;++k) {
          M[i][j] += fabs(pow(p[k][0], i+j));
        }
      }
    }
  }
  for(i = 0;i < m;++i) {
    M[i][n-1] = 0;
    for(k = 0;k < amnt;++k) {
      M[i][n-1] += fabs(pow(p[k][0], i)) * p[k][1];
    }
  }

  printf("Reducing matrix\n");
  rref(M, m, n);

  display_matrix(M, m, n);
  key = G_wait_key();
  double res, z;

  printf("Making line\n");
  G_rgb(1,1,0);
  for(z = 0;z < swidth;++z) {
    res = 0;
    for(i = 0;i < m;++i) {
      res += M[i][n-1] * pow(z, i);
    }
    printf("z = %lf  f(z) = %lf\n", z, res);
    G_fill_circle(z, res, 1);
  }

  key = G_wait_key();

  return 0;
}

