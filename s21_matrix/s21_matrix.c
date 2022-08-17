#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int err_status = OK;
  if (rows > 0 && columns > 0) {
    result->rows = rows;
    result->columns = columns;
    double **matrix = (double **)calloc(rows, sizeof(double *));
    double *values = (double *)calloc(rows * columns, sizeof(double));
    for (int i = 0; i < rows; i++) {
      matrix[i] = values + columns * i;
    }
    result->matrix = matrix;
  } else {
    err_status = INCORRECT_MATRIX;
    result->matrix = NULL;
  }
  return err_status;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix) {
    if (A->matrix[0]) free(A->matrix[0]);
    free(A->matrix);
    if (A->rows) {
      A->rows = 0;
    }
    if (A->columns) {
      A->columns = 0;
    }
    A->matrix = NULL;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int err_status = SUCCESS;
  if (A != NULL && A->matrix != NULL && B != NULL && B->matrix != NULL &&
      A->rows == B->rows && A->columns == B->columns && A->rows > 0 &&
      A->columns > 0 && B->rows > 0 && B->columns > 0) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) err_status = FAILURE;
      }
    }
  } else {
    err_status = FAILURE;
  }
  return err_status;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int err_status = OK;
  if (A != NULL && B != NULL && A->matrix != NULL && B->matrix != NULL &&
      A->rows > 0 && A->columns > 0 && B->rows > 0 && B->columns > 0) {
    if (A->rows == B->rows && A->columns == B->columns) {
      s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    } else {
      err_status = COUNTING_ERROR;
    }
  } else {
    err_status = INCORRECT_MATRIX;
  }
  return err_status;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int err_status = OK;
  if (A != NULL && B != NULL && A->matrix != NULL && B->matrix != NULL &&
      A->rows > 0 && A->columns > 0 && B->rows > 0 && B->columns > 0) {
    if (A->rows == B->rows && A->columns == B->columns) {
      s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    } else {
      err_status = COUNTING_ERROR;
    }
  } else {
    err_status = INCORRECT_MATRIX;
  }
  return err_status;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int err_status = OK;
  if (A != NULL && A->matrix != NULL && A->rows > 0 && A->columns > 0) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  } else {
    err_status = INCORRECT_MATRIX;
  }
  return err_status;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int err_status = OK;
  if (A != NULL && B != NULL && A->matrix != NULL && B->matrix != NULL &&
      A->rows > 0 && A->columns > 0 && B->rows > 0 && B->columns > 0) {
    if (A->columns == B->rows) {
      s21_create_matrix(A->rows, B->columns, result);
      for (int i = 0; i < B->columns; i++) {
        for (int j = 0; j < A->rows; j++) {
          for (int k = 0; k < A->columns; k++) {
            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
          }
        }
      }
    } else {
      err_status = COUNTING_ERROR;
    }
  } else {
    err_status = INCORRECT_MATRIX;
  }
  return err_status;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int err_status = OK;
  if (A != NULL && A->matrix != NULL && A->rows > 0 && A->columns > 0) {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  } else {
    err_status = INCORRECT_MATRIX;
  }
  return err_status;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int err_status = OK;
  if (A != NULL && A->matrix != NULL && A->rows > 0 && A->columns > 0) {
    if (A->rows == A->columns) {
      s21_create_matrix(A->columns, A->rows, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          matrix_t minor;
          double determinant = 0;
          s21_create_matrix(A->columns - 1, A->rows - 1, &minor);
          s21_get_matrix(i, j, A, &minor);
          s21_determinant(&minor, &determinant);
          result->matrix[i][j] = pow(-1, (i + j)) * determinant;
          s21_remove_matrix(&minor);
        }
      }
    } else {
      err_status = COUNTING_ERROR;
    }
  } else {
    err_status = INCORRECT_MATRIX;
  }
  return err_status;
}

int s21_determinant(matrix_t *A, double *result) {
  int err_status = OK;
  if (A != NULL && A->matrix != NULL && A->rows > 0 && A->columns > 0) {
    if (A->rows == A->columns) {
      *result = s21_get_determinant(A);
    } else {
      err_status = COUNTING_ERROR;
    }
  } else {
    err_status = INCORRECT_MATRIX;
  }
  return err_status;
}

double s21_get_determinant(matrix_t *A) {
  double res = 0;
  if (A->rows == 1) {
    res = A->matrix[0][0];
  } else {
    matrix_t tmp;
    s21_create_matrix(A->rows - 1, A->columns - 1, &tmp);
    for (int i = 0; i < A->columns; i++) {
      s21_get_matrix(0, i, A, &tmp);
      if (i % 2) {
        res -= A->matrix[0][i] * s21_get_determinant(&tmp);
      } else {
        res += A->matrix[0][i] * s21_get_determinant(&tmp);
      }
    }
    s21_remove_matrix(&tmp);
  }
  return res;
}

void s21_get_matrix(int row, int col, matrix_t *A, matrix_t *result) {
  int m_row = 0;
  int m_col = 0;
  for (int i = 0; i < A->rows; i++) {
    if (i == row) {
      continue;
    }
    m_col = 0;
    for (int j = 0; j < A->columns; j++) {
      if (j == col) {
        continue;
      }
      result->matrix[m_row][m_col] = A->matrix[i][j];
      m_col++;
    }
    m_row++;
  }
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int err_status = OK;
  if (A != NULL && A->matrix != NULL && A->rows > 0 && A->columns > 0) {
    if (A->rows == A->columns) {
      double determinant = 0;
      s21_determinant(A, &determinant);
      if (determinant != 0 && fabs(determinant) > EPS) {
        matrix_t buf1;
        matrix_t buf2;
        s21_calc_complements(A, &buf1);
        s21_transpose(&buf1, &buf2);
        s21_mult_number(&buf2, 1. / determinant, result);
        s21_remove_matrix(&buf1);
        s21_remove_matrix(&buf2);
      } else {
        err_status = COUNTING_ERROR;
      }
    } else {
      err_status = COUNTING_ERROR;
    }
  } else {
    err_status = INCORRECT_MATRIX;
  }
  return err_status;
}

void s21_fill(matrix_t *matrix, double value) {
  for (int i = 0; i < matrix->rows; i++) {
    for (int j = 0; j < matrix->columns; j++) {
      matrix->matrix[i][j] = value;
    }
  }
}
