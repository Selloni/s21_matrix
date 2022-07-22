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

void s21_remove_matrix(matrix_t *A) {  // освобождаем каждый элмент иказатель 
    for (int i = 0; i < A->rows; i++) {
        if (A->matrix) free(A->matrix[i]);
    }
    if (A->matrix) free(A->matrix);
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    int err_status = SUCCESS;
    if (CHEK_CORECT) {
        int k = 0;
        for(int i; i < A->rows; i++) {
            while(k < A->columns ) {
                if(fabs(A->matrix[i][k] - B->matrix[i][k]) > EPS) err_status = FAILURE;
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
        if (A->rows == B->columns) {
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
        }
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
    }
    return err_status;
}
int s21_calc_complements(matrix_t *A, matrix_t *result) {
    int err_status;
    // int M;
    
    for(int i = 0; i < A->rows; i++) {
        for(int k = 0; k < A-> columns; k++) {
            // A->matrix[i][k] = s21_minor();  
        }
    }
}

//  определитель матрицы можно рачитать с помощью любой строки или столбца 
int s21_determinant(matrix_t *A, double *result) {
    int err_status;
    

}
// 1 создаем матрице без зачеркнуых значей 
// 2 цклом в нее запизивает последовательно столбцы и строки и сразу проверяем для остановки рекурсии она должна быть 3х3
// 3 если три на три считаем
// разобраться с матрицами в 4х4 и более что должно поисходит 
/// !!!!!! пока по задумке функцияя уменьшает матрицу до 2х2 за счет рекурсии, после переводит в матрицу алгеброического дополнения и ретернит это число ---
///...после чего складывает его с минором вследоватьльно минор с кадой итераии увиличиваеться после того как нашлась младшая матрица!!!!!!
////////////////////////////////                                   //////////////////////

//нужно сделать превй цикл который будет изначально пердавать i and k in cycle и заполняет матрицу результата
//
// 
void s21_matrix_reduction(int str, int i, int k, matrix_t matrix_lees) {
    s21_create_matrix(str, str, &matrix_lees); // creat less matrix for minor it is must be in сycle // а не даляю ли я свою основную матрицу такиеми дейтсиями когда передаю ее арес 
    for(int minor_i = 0; minor_i < str; minor_i++) {
        for(int minor_k = 0; minor_k < str; minor_k++) {
            if(minor_i != i && minor_k != k) {
                matrix_lees.matrix[i][k] = matrix_lees.matrix[i][k];
            }
        }
    } // minor должен возвращаться в таблицу с кторой начинался отсчет ..
    double minor ;
    double algb ;
    if (matrix_lees.rows < 1) {
        minor = matrix_lees.matrix[0][0] * matrix_lees.matrix[1][1] - matrix_lees.matrix[1][0] * matrix_lees.matrix[1][0];
        algb = pow(-1, (i+k)) * minor;    
    }
    // if (matrix_lees.rows > 1) algb += s21_matrix_reduction(str - 1, i - 1, k - 1, matrix_lees);
    // return algb;
}

// Алгебраическим дополнением элемента матрицы является значение минора умноженное на -1^(i+j).

// void s21_my_thots () {
//     s21_create_matrix(str - 1, post - 1, &matrix_lees) { // creat less matrix for minor it is mast in сycle
//     int algb = -1^(i+k)*M;
//     }
// }

int s21_inverse_matrix(matrix_t *A, matrix_t *result);


////////////////dop_funtion///////////////

// void s21_fill(matrix_t *matrix, double value) {
//   for (int i = 0; i < matrix->rows; i++) {
//     for (int j = 0; j < matrix->columns; j++) {
//       matrix->matrix[i][j] = value;
//     }
//   }
// }
