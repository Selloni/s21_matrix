#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define SUCCESS 1
#define FAILURE 0
#define EPS 1e-7
#define CHEK_CORECT A != NULL && B != NULL && A->matrix != NULL && B->matrix != NULL && \
A->rows > 0 && A->columns > 0 && B->rows > 0 && B->columns > 0

typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;

enum {
OK,
ERROR_MATRIX,
ERROR_CALC,
};
 
//  generated_by_makefile

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
double s21_get_determinant(matrix_t *A);
void s21_get_matrix(int row, int col, matrix_t *A, matrix_t *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
void s21_fill(matrix_t *matrix, double value);


#endif //  SRC_S21_MATRIX_H_