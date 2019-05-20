#include "matrix.h"

/*
  Horrace, Robert
  CS 451
  This program computes the
  row reduced echelon form
  of a m x n matrix, assuming
  it is an augmented matrix
*/

int main() {
  int i, j, m, n;
  // Read in row and column
  printf("Enter # of rows and columns: ");
  scanf("%d %d", &m, &n);
  double** matrix = create_matrix(m, n);
  // Set matrix
  set_matrix(matrix, m , n);

  printf("Entered matrix:\n");
  display_matrix(matrix, m , n);
  // Form upper triangle form
  upper_triangle(matrix, m , n);
  // Form lower triangle (rref)
  lower_triangle(matrix, m , n);
  // Convert negative rows to positive
  adjust(matrix, m, n);
  // Simplify so it is in proper rref
  simplify(matrix, m, n);
  // Display matrix (should be in rref)
  printf("rref:\n");
  display_matrix(matrix, m, n);
  for(i = 0;i < m;++i) {
    free(matrix[i]);
    matrix[i] = NULL;
  }
  free(matrix);
  matrix = NULL;
  return 0;
}
