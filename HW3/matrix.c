#include "matrix.h"

/*
  Horrace, Robert
  This is the implementation
  of the declared functions in matrix.h
*/

//Creates an m x n matrix
double** create_matrix(int m, int n) {
  double** matrix = malloc(sizeof(double*) * m);
  int i,j;
  for(i = 0;i < m;++i) {
    matrix[i] = malloc(sizeof(double) * n);
    for(j = 0;j < n;++j) {
      matrix[i][j] = 0;
    }
  }
  return matrix;
}

// Displays the m x n matrix
void display_matrix(double** matrix, int m, int n) {
  int i,j;
  for(i = 0;i < m;++i) {
    printf("|");
    for(j = 0;j < n;++j) {
      if(j == n-1) {
        printf("%2.2lf", matrix[i][j]);
      }
      else {
        printf("%2.2lf\t", matrix[i][j]);
      }
    }
    printf("|\n");
  }
}

// Sets the m x n matrix index values to user defined values
void set_matrix(double** matrix, int m, int n) {
  int i,j;
  for(i = 0;i < m;++i) {
    for(j = 0;j < n;++j) {
      printf("Enter matrix[%d][%d]'s value: ", i, j);
      scanf("%lf", &matrix[i][j]);
    }
  }
}

// gcd using euclidean algorithm
int gcd(int a, int b) {
  if(a == 0) {
    return b;
  }
  else if(b == 0) {
    return a;
  }
  int k = abs(a), m = abs(b);
  while(k != m) {
    if(k > m) {
      k = k - m;
    }
    else {
      m = m - k;
    }
  }
  return k;
}

// lcm function
int lcm(int a, int b) {
  if(a == 0 && b == 0) {
    return 0;
  }
  return (a * b) / gcd(a, b);
}

// find max row function (could be the same row or all zeros)
int find_max_row(double** matrix, int r, int c, int m) {
  int i, max_r = r;
  for(i = r+1;i < m;++i) {
    if(abs(matrix[i][c]) > abs(matrix[max_r][c])) {
      max_r = i;
    }
  }
  return max_r;
}

// row swapping row function
void row_swap(double** matrix, int r1, int r2, int n) {
  int i;
  double temp;
  for(i = 0;i < n;++i) {
    temp = matrix[r1][i];
    matrix[r1][i] = matrix[r2][i];
    matrix[r2][i] = temp;
  }
}

// upper triangle function
void upper_triangle(double** matrix, int m, int n) {
  int i, j, k, max_r;
  double mult, div1, div2, md1, md2;
  int stop = min(m-1, n-1);
  // loops on matrix[k][k], the identity values
  for(k = 0;k <= stop;++k) {
    // if identity value is 0
    if(matrix[k][k] == 0) {
      max_r = find_max_row(matrix, k, k, m);
      if(max_r != k) {
        row_swap(matrix, k, max_r, n);
      }
      else {
        continue;
      }
    }
    // set row values to Ri = ?Ri - ?Rk
    for(i = k+1;i < m;++i) {
      mult = lcm(matrix[k][k], matrix[i][k]);
      div1 = mult / matrix[k][k];
      div2 = mult / matrix[i][k];
      for(j = 0;j < n;++j) {
        md1 = matrix[k][j] * div1;
        md2 = matrix[i][j] * div2;
	matrix[i][j] = md2 - md1;
      }
    }
  }
}

// Lower triangle function
void lower_triangle(double** matrix, int m, int n) {
  int i, j, k;
  double mult, div1, div2, md1, md2;
  int start = min(m-1, n-1);
  // start at lower rightmost identity
  for(k = start;k > 0;--k) {
    if(matrix[k][k] == 0) {
      continue;
    }
    // Set upper rows to Ri = ?Ri - ?Rk
    for(i = k-1;i >= 0;--i) {
      mult = lcm(matrix[k][k], matrix[i][k]);
      div1 = mult / matrix[k][k];
      div2 = mult / matrix[i][k];
      for(j = n-1;j >= 0;--j) {
        md1 = matrix[k][j] * div1;
        md2 = matrix[i][j] * div2;
	matrix[i][j] = md2 - md1;
      }
    }
  }
}

// adjusting function sets negative identities to positives
// adjusting following row values accordingly
void adjust(double** matrix, int m, int n) {
  int i, j, stop;
  stop = min(m-1, n-1);
  for(i = 0;i <= stop;++i) {
    if(matrix[i][i] >= 0) {
      continue;
    }
    for(j = 0;j < n;++j) {
      if(matrix[i][j] != 0) {
        matrix[i][j] *= -1;
      }
    }
  }
}

// simplifying function simplifies rows
// according to their identities
void simplify(double** matrix, int m, int n) {
  int i, j, stop;
  stop = min(m-1,n-1);
  for(i = 0;i <= stop;++i) {
    double div = matrix[i][i];
    for(j = 0;j < n;++j) {
      if(matrix[i][j] == 0) {
        continue;
      }
      matrix[i][j] /= div;
    }
  }
}
