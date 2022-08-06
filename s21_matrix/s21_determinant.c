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
    printf("%f\n", *result);
    return err_status;
}

void s21_pull_matrix(int row, int col, matrix_t *A, matrix_t *tmp) {
    int count_col = 0;
    int count_row = 0; 
    for (int i = 0; i < A->rows; i++) {
        if (i == row) {
            continue;
        }
        count_col = 0;
        for (int j = 0; j < A->columns; j++) {
            if (j == col) {
                continue;
            }
           tmp->matrix[count_row][count_col] = A->matrix[i][j];
           count_col++;
         }
         count_row++;
    }
}

double s21_get_determinant(matrix_t *A) {
    double res;
    // if(A->rows == 2) {
    //     res = (A->matrix[0][0] * A->matrix[1][1]) - (A->matrix[0][1] * A->matrix[1][0]);
    //     printf("___._minnor_.__\n");
    //     for( int i = 0; i < 2; i++) {
    //         for( int k = 0; k < 2; k++) {
    //             printf("%f ",A->matrix[i][k]);
    //         }
    //     printf("\n");
    //     }
    // }
    if (A->rows == 1) {
        res = A->matrix[0][0];
    } else {
        matrix_t  tmp;
        s21_create_matrix(A->rows - 1, A->rows - 1, &tmp);
        for (int k = 0; k < A->rows; k++) {
            s21_pull_matrix(0, k, A, &tmp);
            res += pow(-1, k) * (A->matrix[0][k] * s21_get_determinant(&tmp));
        }
    }
    return res;
}

