#include <stdio.h>
#include <stdbool.h>

int ge_fw(float *matrix, int rows, int cols) {
  int pivotRow = 0; // set row that the pivot is on
  for(int currentCol = 0; currentCol < cols; currentCol++) {
    if(pivotRow >= rows) {
      return 1;
    }
    bool zeroCol = false;

    for(int i = pivotRow; i < rows; i++) {
      // if the current row pivot has a value that is not zero, move on
      if(matrix[i * cols + currentCol] != 0 && i == pivotRow) {
        break;
      }
      // else iterate through until the first non-zero row
      else if(matrix[i * cols + currentCol] != 0 && i > pivotRow) {
        for(int j = 0; j < cols; j++) {
          float temp = matrix[i * cols + j];
          matrix[i * cols + j] = matrix[0 + j];
          matrix[0 + j] = temp;
        }
        break;
      }
      // if the entire column contains zeroes, go to next col
      if(i == rows - 1) {
        zeroCol = true;
      }
    }
    // skip subtracting if column is zero
    if(!zeroCol) {
      // subtract a multiple of top row from the lower rows
      for(int i = pivotRow + 1; i < rows; i++) {
        if(matrix[i * cols + currentCol] != 0) {
          float r = matrix[i * cols + currentCol] / matrix[pivotRow * cols + currentCol];
          printf("%f\n", r);
          // subtract for each individual column in a row
          for(int j = 0; j < cols; j++) {
            matrix[i * cols + j] - r * matrix[pivotRow * cols + currentCol];
          }
        }
      }
      pivotRow++;
    }

  }
  return 1;
}

int ge_bw(float *matrix, int rows, int cols, float *matrix_out) {

  return 1;
}

int main()
{
  int rows = 4, cols = 2;
  float *matrix[4][2] = { {0, 1}, {1, 2}, {3, 4}, {5, 5} };
  ge_fw(matrix, rows, cols);
  for(int i = 0; i < rows; i++) {
    for(int j = 0; j < cols; j++) {
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
  return(0);
}
