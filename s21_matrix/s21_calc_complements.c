#include "s21_matrix.h"

int s21_calc_complements (matrix_t *A, matrix_t *result) {
    int err_status = OK;
    if(A != NULL && A->matrix != NULL && A->rows > 0 && A->columns > 0) {
        if (A->columns == A->rows) {         
            s21_create_matrix(A->rows, A->columns, result);
            for(int i = 0; i < A->rows; i++) {
                printf("i%d", i);
                for(int k = 0; k < A->columns; k++) {
                    printf("k%d", k);
                    matrix_t tmp;
                    s21_create_matrix(A->rows - 1, A->columns - 1, &tmp);
                    s21_pull_matrix(i, k, A, &tmp);
                    result->matrix[i][k] = s21_get_determinant(&tmp);
                    printf("%f ", result->matrix[i][k]);
                    s21_remove_matrix(&tmp);
                }
                printf("\n");
            }
            //  свободлить result в тестах;     
            } else {
            err_status = ERROR_CALC;
        }
    } else {
        err_status = ERROR_MATRIX;
    }
    return err_status;
}