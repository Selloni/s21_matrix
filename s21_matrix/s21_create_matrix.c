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