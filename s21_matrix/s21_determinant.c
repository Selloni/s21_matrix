#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
    int err_status = OK;
    if (A != NULL && A->matrix != NULL && A->rows > 0 && A->columns > 0) {
        if(A->rows == A->columns) {
           *result = s21_get_determinant(A);
        } else {
            err_status = ERROR_CALC;
        }
    } else {
        err_status = ERROR_MATRIX;
    }
    printf("%f", *result);
    return err_status;
}

void s21_pull_matrix(int row, int col, matrix_t *A, matrix_t *tmp) {
    for (int i = 0; i < A->rows; i++) {
        if (i == row) {
            continue;
        }
        col = 0;
        for (int j = 0; j < A->columns; j++) {
            if (j == col) {
                continue;
            }
           tmp->matrix[row][col] = A->matrix[i][j];
           col++;
         }
         row++;
    }
}

double s21_get_determinant(matrix_t *A) {
    double res;
    if(A->rows == 2) {
        res = A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    }
    else if (A->rows == 1) {
        res = A->matrix[0][0];
    } else {
        matrix_t  tmp;
        s21_create_matrix(A->rows - 1, A->rows - 1, &tmp);
        for (int i = 0; i < A->rows; i++) {
            s21_pull_matrix(0, i, A, &tmp);
            if (i % 2) {
                res += s21_get_determinant(&tmp);
            } else {
                res -= s21_get_determinant(&tmp);
            }
        }
    }
    return res;
}

