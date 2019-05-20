#include "runge.h"

double** create_matrix(int m, int n) {
  double** M = malloc(sizeof(double*) * m);
  int i;
  for(i = 0;i < m;++i) {
    M[i] = calloc(n, sizeof(double));
  }
  return M;
}

void init_matrix(double** M, int m, int n, double* X, double* Y, int amnt) {
  int a, b, k, pos = 0;
  M[0][0] = 1;
  if(m != 1) {
    M[1][0] = X[pos+1] - X[pos];
    M[0][1] = -M[1][0];
  }
  M[0][n-1] = 0;
  ++pos;
  for(k = 1;k < m;++k) {
    if(k % 2 == 1) {
      if(k != m-1) {
        M[k][k] = pow(M[k][k-1], 2);
        M[k+1][k] = M[k][k];
	M[k][k+1] = X[pos+1] - X[pos];
	a = (Y[pos+1] - Y[pos]) / M[k][k+1];
	b = (Y[pos] - Y[pos-1]) / M[k][k-1];
	M[k][n-1] = a-b;
	++pos;
      }
      else {
        M[k][k] = 2 * (X[pos] - X[pos-1]);
	M[k][n-1] = 0;
      }
    }
    else {
      M[k][k] = -(X[pos] - X[pos-2]);
      if(k == m-2) {
        M[k+1][k] = 1;
      }
      else {
        M[k+1][k] = M[k-1][k];
      }
      M[k][k+1] = M[k-1][k] * M[k-1][k-2];
      if(M[k-1][n-1] != 0) {
        M[k][n-1] = -M[k-1][n-1];
      }
    }
  }
}

void rref(double** M, int m, int n) {
  int k;
  double f;
  for(k = 0;k < m-1;++k) {
    f = M[k+1][k] / M[k][k];
    M[k+1][k] -= M[k][k] * f;
    M[k+1][k+1] -= M[k][k+1] * f;
    M[k+1][n-1] -= M[k][n-1] * f;
  }
  for(k = m-1;k >= 1;--k) {
    f = M[k-1][k] / M[k][k];
    M[k-1][k] -= M[k][k] * f;
    M[k-1][n-1] -= M[k][n-1] * f;
  }
  for(k = 0;k < m;++k) {
    f = M[k][k];
    M[k][k] /= f;
    M[k][n-1] /= f;
    if(M[k][k] < 0) {
      M[k][k] = -M[k][k];
      M[k][n-1] = (M[k][n-1] != 0) ? (-M[k][n-1]):0;
      if(M[k][n-1] == -0) {
        M[k][n-1] = fabs(M[k][n-1]);
      }
    }
  }
}

void display(double** M, int m, int n) {
  int i,j;
  for(i = 0;i < m;++i) {
    for(j = 0;j < n;++j) {
      if(M[i][j] == 0 && j != n-1) {
        printf("-----------");
      }
      else {
        printf("%10.3lf", M[i][j]);
      }
    }
    printf("\n");
  }
}

double** read_from_file(int* amnt) {
  FILE* f;
  double** p;
  char file_name[100];
  int n, i;
  printf("Enter file name: ");
  scanf("%s", file_name);
  f = fopen(file_name, "r");
  if(!f) {
    printf("Cannot open file\n");
    return NULL;
  }
  fscanf(f, "%d", &n);
  p = malloc(sizeof(double*)* n);
  for(i = 0;i < n;++i) {
    p[i] = malloc(sizeof(double)* 2);
    fscanf(f, "%lf %lf\n", &p[i][0], &p[i][1]);
  }

  printf("# of points = %d\n", n);
  for(i = 0;i < n;++i) {
    printf("(%lf,%lf)\n", p[i][0], p[i][0]);
  }
  fclose(f);
  *amnt = n;
  return p;
}
