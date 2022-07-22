#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int err_status = OK;
  if (A != NULL && A->matrix != NULL && A->rows > 0 && A->columns > 0) {
    if (A->rows == A->columns) {
      *result = s21_get_determinant(A);
    } else {
      err_status = ERROR_CALC;
    }
  } else {
    err_status = ERROR_MATRIX;
  }
  return err_status;
}

double s21_get_determinant (matrix_t *A) {
    
}