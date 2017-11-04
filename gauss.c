#include <stdio.h>
#include <math.h>
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
            matrix[i * cols + j] -= r * matrix[pivotRow * cols + j];
            // ensure positive if value is 0 so we dont get -0.00
            if(fabs(matrix[i * cols + j]) < 0.000001) {
              matrix[i * cols + j] = 0.0f;
            }
          }
        }
      }
      pivotRow++;
    }
  }
  return 1;
}

// steps for reduced row echelon forms
int ge_bw(float *matrix, int rows, int cols) {
  // started from the bottom now we here
  for(int i = rows - 1; i >= 0; i--) {
    bool zeroRow = false;
    int currentCol = cols - 1;
    // check for first non-zero row
    for(int j = 0; j < cols; j++) {
      // since floats are being used, we must check precision to be safe
      if(fabs(matrix[i * cols + j]) > 0.00001) {
        currentCol = j;
        // set leading number to 1
        float ratio = 1.0f / matrix[i * cols + j];
        for(int k = j; k < cols; k++) {
          matrix[i * cols + k] *= ratio;
        }
        break;
      }
      if(j == cols - 1) {
        zeroRow = true;
      }
    }
    if(!zeroRow) {
      for(int r = i - 1; r >= 0; r--) {
        float p = matrix[r * cols + currentCol] / matrix[i * cols + currentCol];
        for(int j = currentCol; j < cols; j++) {
          matrix[r * cols + j] -= p * matrix[i * cols + j];
          // ensure positive if value is 0 so we dont get -0.00
          if(fabs(matrix[r * cols + j]) < 0.000001) {
            matrix[r * cols + j] = 0.0f;
          }
        }
      }
    }
  }
  return 1;
}

int main()
{
  int rows = 4, cols = 4;
  float matrix[4][4] = { {5.0f, 2.0f, 2.0f, 12.0f}, {1.0f, 2.0f, 0.0f, 7.0f}, {3.0f, 4.0f, 13.0f, 0.0f}, {0.0f, 0.0f, -9.0f, -5.0f} };
  ge_fw(*matrix, rows, cols);
  for(int i = 0; i < rows; i++) {
    for(int j = 0; j < cols; j++) {
      printf("%.2f ", matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");
  ge_bw(*matrix, rows, cols);
  for(int i = 0; i < rows; i++) {
    for(int j = 0; j < cols; j++) {
      printf("%.2f ", matrix[i][j]);
    }
    printf("\n");
  }
  return(0);
}
