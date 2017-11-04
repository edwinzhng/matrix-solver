#include <stdio.h>
#include <stdbool.h>

// steps for row echelon form
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
          // subtract for each individual column in a row
          for(int j = 0; j < cols; j++) {
            for(int r = 0; r < rows; r++) {
              for(int c = 0; c < cols; c++) {
                printf("%.1f ", matrix[r * cols + c]);
              }
              printf("\n");
            }
            printf("\n");

            matrix[i * cols + j] -= r * matrix[pivotRow * cols + j];
          }
        }
      }
      pivotRow++;
    }
  }
  return 1;
}

// steps for reduced row echelon form
int ge_bw(float *matrix, int rows, int cols, float *matrix_out) {

  return 1;
}

int main()
{
  int rows = 4, cols = 2;
  float matrix[4][2] = { {0.0f, 1.0f}, {1.0f, 2.0f}, {3.0f, 4.0f}, {5.0f, 5.0f} };
  ge_fw(matrix, rows, cols);
  // ge_bw(matrix, rows, cols);
  for(int r = 0; r < rows; r++) {
    for(int c = 0; c < cols; c++) {
      printf("%.1f ", matrix[r][c]);
    }
    printf("\n");
  }
  return(0);
}
