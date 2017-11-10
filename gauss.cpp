#include <iostream>
#include <vector>

using namespace std;

// steps for row echelon form
int ref(double *matrix, int rows, int cols) {
  int pivotRow = 0, i, currentCol, j; // set row that the pivot is on
  for(currentCol = 0; currentCol < cols; currentCol++) {
    if(pivotRow >= rows) {
      return 0;
    }
    int zeroCol = 0;

    for(i = pivotRow; i < rows; i++) {
      // if the current row pivot has a value that is not zero, move on
      if(matrix[i * cols + currentCol] != 0 && i == pivotRow) {
        break;
      }
      // else iterate through until the first non-zero row
      else if(matrix[i * cols + currentCol] != 0 && i > pivotRow) {
        for(int j = 0; j < cols; j++) {
          double temp = matrix[i * cols + j];
          matrix[i * cols + j] = matrix[0 + j];
          matrix[0 + j] = temp;
        }
        break;
      }
      // if the entire column contains zeroes, go to next col
      if(i == rows - 1) {
        zeroCol = 1;
      }
    }
    // skip subtracting if column is zero
    if(!zeroCol) {
      // subtract a multiple of top row from the lower rows
      for(i = pivotRow + 1; i < rows; i++) {
        if(matrix[i * cols + currentCol] != 0) {
          double r = matrix[i * cols + currentCol] / matrix[pivotRow * cols + currentCol];
          // subtract for each individual column in a row
          for(j = 0; j < cols; j++) {
            matrix[i * cols + j] -= r * matrix[pivotRow * cols + j];
            // ensure positive if value is 0 so we dont get -0.00
            if(((matrix[i*cols+j]) > 0 && matrix[i*cols+j] < 0.000001) || ((matrix[i*cols+j]) < 0 && matrix[i*cols+j] > -0.000001)) {
              matrix[i * cols + j] = 0.0f;
            }
          }
        }
      }
      pivotRow++;
    }
  }
  return 0;
}

// steps for reduced row echelon forms
int rref_from_ref(double *matrix, int rows, int cols) {
  int i, j, k, r;
  // started from the bottom now we here
  for(i = rows - 1; i >= 0; i--) {
    int zeroRow = 0;
    int currentCol = cols - 1;
    // check for first non-zero row
    for(j = 0; j < cols; j++) {
      // since doubles are being used, we must check precision to be safe
      if(matrix[i * cols + j] != 0.0f) {
        currentCol = j;
        // set leading number to 1
        double ratio = 1.0f / matrix[i * cols + j];
        for(k = j; k < cols; k++) {
          matrix[i * cols + k] *= ratio;
        }
        break;
      }
      if(j == cols - 1) {
        zeroRow = 1;
      }
    }
    if(!zeroRow) {
      for(r = i - 1; r >= 0; r--) {
        double p = matrix[r * cols + currentCol] / matrix[i * cols + currentCol];
        for(j = currentCol; j < cols; j++) {
          matrix[r * cols + j] -= p * matrix[i * cols + j];
          // ensure positive if value is 0 so we dont get -0.00
          if(((matrix[r*cols+j]) > 0 && matrix[r*cols+j] < 0.000001) || ((matrix[r*cols+j]) < 0 && matrix[r*cols+j] > -0.000001)) {
            matrix[r * cols + j] = 0.0f;
          }
        }
      }
    }
  }
  return 0;
}

int main()
{
  int rows, cols, i, j;
  cout << "Please enter the number of rows and columns separated by a space: " << endl;
  cin >> rows >> cols;
  double *matrix = (double *) malloc((rows*cols)*sizeof(double));
  cout << "Please enter the elements for each row separated by spaces:" << endl;
  for(int i = 0; i < rows; i++) {
    for(int j = 0; j < cols; j++) {
      cin >> matrix[i * cols + j];
    }
  }
  ref(matrix, rows, cols);
  rref_from_ref(matrix, rows, cols);
  for(i = 0; i < rows; i++) {
    for(j = 0; j < cols; j++) {
      printf("%.2f ", matrix[i * cols  + j]);
    }
    printf("\n");
  }
  return(0);
}
