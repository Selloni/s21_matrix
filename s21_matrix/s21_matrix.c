#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
    int err_status = OK;
    if (rows > 0 && columns > 0) {
        result->rows = rows;
        result->columns = columns;
        double **matrix = (double **)calloc(rows, sizeof(double *));  //  выделяем динамическую память на указатель
        double *values = (double *)calloc(rows * columns, sizeof(double));
        for (int i = 0; i < rows; i++) {
            matrix[i] = values + columns * i;
        }
        result->matrix = matrix;
    } else {
        err_status = ERROR_MATRIX;
        result->matrix = NULL;
    }
    return err_status;
}

// int s21_create_matrix(int rows, int columns, matrix_t *result) {
//     int err_status = OK;
//     if (rows > 0 && columns > 0) {
//         result->rows = rows;
//         result->columns = columns;
//         double **A;
//         A = (double **)calloc(rows, sizeof(double*));
//         for (int i = 0; i < rows; i++) {
//             A[i] = (double *) calloc(columns, sizeof(double));
//         }
//     } else {
//         err_status = ERROR_MATRIX;
//     }
//     return err_status;
// }

// void s21_remove_matrix(matrix_t *A) {  // освобождаем каждый элмент иказатель
//     for (int i = 0; i < A->rows; i++) {
//         if (A->matrix) free(A->matrix[i]);
//     }
//     if (A->matrix) free(A->matrix);
// }

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
    if (CHEK_CORECT && A->rows == B->rows && A->columns == B->columns) {
        for(int i = 0; i < A->rows; i++) {
            int k = 0;
            while(k < A->columns ) {
                if(fabs(A->matrix[i][k] - B->matrix[i][k]) > EPS) err_status = FAILURE;  //  EPS 0,0000001 fabs = abc
                k++;
            }
        }
    } else {
        err_status = FAILURE;
    }
    return err_status;
}


int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int err_status = OK;
    if (CHEK_CORECT) {
        if ((A->rows == B->rows) && (A->columns == B->columns)) {
            s21_create_matrix(A->rows, A->columns, result);
            for (int i = 0; i < A->rows; i++) {
                for (int k = 0; k < A->columns; k++) {
                    result->matrix[i][k] = A->matrix[i][k] + B->matrix[i][k];
                }
            }
            // s21_remove_matrix(result);
        } else {
            err_status = ERROR_CALC;
        }
    } else {
        err_status = ERROR_MATRIX;
    }
    return err_status;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int err_status;
    if (CHEK_CORECT) {
        if ((A->rows == B->rows) && (A->columns == B->columns)) {
            s21_create_matrix(A->rows, A->columns, result);  //   это тип я просто выделяю память для создания матрицы нкжно обьяснить
            err_status = OK;
            for(int i = 0; i < A->rows; i++) {
                for(int k = 0; k < A->columns; k++) {
                    result->matrix[i][k] = A->matrix[i][k] - B->matrix[i][k];
                }
            }
            // s21_remove_matrix(result);
        } else {
            err_status = ERROR_CALC;
        }
    } else {
        err_status = ERROR_MATRIX;
    }
    return err_status;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
    int err_status = OK;
    if (A != NULL && A->rows > 0 && A->columns > 0 && A->matrix != NULL) {
        s21_create_matrix(A->rows, A->columns, result);
        for(int i = 0; i < A->rows; i++) {
            for(int k = 0; k < A->columns; k++) {
                result->matrix[i][k] = A->matrix[i][k] * number;
            }
        }
        // s21_remove_matrix(result);
    } else {
        err_status = ERROR_MATRIX;
    }
    return err_status;
}

/// умножать можно только когда число строк совпадает с числом столбцов А = строкам Б
// число столбцов равно числу строк, все стобци премноаем на число строк ,
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int err_status = OK;
    if (CHEK_CORECT) {
        if (A->columns == B->rows && A->rows == B->columns) {
            s21_create_matrix(A->rows, B->columns, result);
            int i = 0;
            while(i < A->rows) {
                int k = 0;
                while(k < B->columns) {
                    int j = 0;
                    while(j < A->rows) {
                        result->matrix[i][k] += A->matrix[i][j] * B->matrix[j][k];
                        j++;
                    }
                    k++;
                }
                i++;
            }
        } else {
            err_status = ERROR_CALC;
        }
        // s21_remove_matrix(result);
    } else {
        err_status = ERROR_MATRIX;
    }
    return err_status;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
    int err_status = OK;
    if (A->matrix != NULL && A != NULL && A->rows > 0 && A->columns > 0) {
        s21_create_matrix(A->columns, A->rows, result);
        for(int i = 0; i < A->rows; i++) {
            for(int k = 0; k < A->columns; k++) {
                result->matrix[k][i] = A->matrix[i][k];
            }
        }
        // s21_remove_matrix(result);
    } else {
        err_status = ERROR_MATRIX;
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
            err_status = ERROR_CALC;
        }
    } else {
        err_status = ERROR_MATRIX;
    }
    return err_status;
}

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

double s21_get_determinant(matrix_t *A) {
    double res = 0;
    if (A->rows == 1) {
        res = A->matrix[0][0];
    } else {
        matrix_t tmp;
        s21_create_matrix(A->rows - 1, A->columns - 1, &tmp);
        for (int i = 0; i < A->columns; i++) {
            s21_get_matrix(0, i, A, &tmp);
            res += pow(-1, i) * (A->matrix[0][i] * s21_get_determinant(&tmp)); 
            // if (i % 2) {
            //     res -= A->matrix[0][i] * s21_get_determinant(&tmp);
            // } else {
            //     res += A->matrix[0][i] * s21_get_determinant(&tmp);
            // }
        }
        s21_remove_matrix(&tmp);
    }
    return res;
}

void s21_get_matrix(int row, int col, matrix_t *A, matrix_t *result) { //  создаем матрицу по осям поменьше
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

// проверка детерминанта != 0
// транспонтировать 
// находим алгеброическое дополнение
// и действия для инвертирования

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
    int err_status = OK;
    double res;
    if(A != NULL && A->matrix != NULL && A->rows > 0 && A->columns > 0) {
        s21_determinant(A, &res);
        if (res != 0 && A->columns == A->rows && fabs(res) > EPS) {
            matrix_t tmp;
            matrix_t buf;
            // s21_create_matrix(A->rows, A->columns, &tmp);
            // s21_create_matrix(A->rows, A->columns, &buf);
            double inverse = 0;
            s21_transpose(A, &buf);
            s21_calc_complements(&buf, &tmp);
            inverse = (1./res); 
            s21_mult_number(&tmp, inverse, result);
            s21_remove_matrix(&tmp);
            s21_remove_matrix(&buf);
        } else {
            err_status = ERROR_CALC;
        }
    } else {
        err_status = ERROR_MATRIX;
    }
    return err_status;
}


////////////////dop_funtion///////////////

void s21_fill(matrix_t *matrix, double value) {
  for (int i = 0; i < matrix->rows; i++) {
    for (int j = 0; j < matrix->columns; j++) {
      matrix->matrix[i][j] = value;
    }
  }
}
