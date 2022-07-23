#include "s21_matrix.h"

double s21_less_matrix(int row, int col, matrix_t *A) {
  matrix_t tmp;
  double res = 0;
  s21_create_matrix(A->columns - 1, A->rows - 1, &tmp);
  int m_row = 0;
  int m_col = 0;
    if (A->rows == 1) {
    res = A->matrix[0][0];
  }
  if (A->rows  == 2) {
    res = A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    res += pow(-1, (m_row + m_col)) * res;
  } else {  
    for (int i = 0; i < A->rows; i++) {
    if (i == row) {
      continue;
    }
    m_col = 0;
    for (int j = 0; j < A->columns; j++) {
      if (j == col) {
        continue;
      }
      tmp.matrix[m_row][m_col] = A->matrix[i][j];
      m_col++;
    }
    m_row++;
    }
    if (A->rows  == 2) {
      res = A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
      res += pow(-1, (m_row + m_col)) * res;
    }
    if (A->rows > 2) {
      
    }
  }
}


int s21_determinant(matrix_t *A, double *result) {
  int err_status = OK;
  if (A != NULL && A->matrix != NULL && A->rows > 0 && A->columns > 0) {
    if (A->rows == A->columns) {
      *result = s21_get_determinant(A);
      result *= A->matrix[0][i];
    } else {
      err_status = ERROR_CALC;
    }
  } else {
    err_status = ERROR_MATRIX;
  }
  return err_status;
}

// double s21_minor (matrix_t *A) {
//     double res = 0;
//     if (A->rows == 1) {
//       res = A->matrix[0][0];
//     }
//     if (A->rows  == 2) {
//       res = A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
//     }
//       for (int i = 0; A->columns; i++) {
//         s21_less_matrix(0, i, A);

//         }
// }



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















// // нужно матрицы поправить и заставить выводить значения 
// int s21_matrix_reduction(int str, int i, int k, matrix_t *matrix_lees , int count) {
//     int tmp_str = str - 1;
//     double minor = 0;
//     double algb = 0;
//     matrix_t tmp;
    
//     if(str > 1) {
//     printf("str%d i%d k%d\n", str,i,k);
//     s21_create_matrix(tmp_str, tmp_str, &tmp); // creat less matrix for minor it is must be in сycle // а не даляю ли я свою основную матрицу такиеми дейтсиями когда передаю ее арес     
//         printf("____%dx%d___\n", tmp.rows, str);
//         int minor_i = 0, tmp_i = 0, minor_k = 0, tmp_k = 0 ;
//         while (minor_i < str) {
//             if(minor_i != i) {
//                 while (minor_k < str) {
//                     if (minor_k != k) {
//                         // printf("matrix-%f\n",matrix_lees->matrix[minor_i][minor_k]);
//                         printf("%d.%d  ", minor_i, minor_k);
//                         tmp.matrix[tmp_i][tmp_k] = matrix_lees->matrix[minor_i][minor_k];
//                         tmp_k++;
//                     }
//                     minor_k++;
//                 }
//                 tmp_i++;
//             }
//             minor_i ++;
//             printf("\n");
//         }
//         // for(int minor_i = 0, tpm_i = 0; minor_i < str; minor_i++ tmp_i++) {
//         //     if(minor_i != i) { 
//         //         for(int minor_k = 0; minor_k < str; minor_k++) {
//         //             if(minor_k != k) {
//         //                 printf("matrix-%f\n",matrix_lees->matrix[minor_i][minor_k]);
//         //                 printf("%d.%d  ", minor_i, minor_k);
//         //                 tmp.matrix[minor_i][minor_k] = matrix_lees->matrix[minor_i][minor_k];
//         //             }
//         //         }
//         //     }
//         //     printf("\n");
//         // } // minor должен возвращаться в таблицу с кторой начинался отсчет ..
//         for(int minor_i = 0; minor_i < tmp.rows; minor_i++) {                
//             for(int minor_k = 0; minor_k < tmp.rows; minor_k++) {
//                     printf("flag recurses #%d\n", count);
//                     algb = s21_matrix_reduction(tmp.rows, minor_i , minor_k , &tmp, count++);
//             } // сега вылетает потому что у меня i сохраняет изначальное значение а матрица у меня меньше
//         }
//     } else {
//         printf("flag recurses #%d\n", count);
//     }
// // //    for( i = 0; i < matrix_lees->rows; i++) {
// //   //     for( k = 0; k < matrix_lees->rows; k++) {
// //     //       printf("%f.%f",matrix_lees->matrix[i][k]);
// //       //     // B.matrix[i][k] = k;
// //        //}
// //        //printf("\n");
// //    //}
// //    //if (matrix_lees->rows > 2) s21_matrix_reduction(matrix_lees->rows - 1, i , k , matrix_lees);
//         // double m1 = matrix_lees->matrix[0][0];
//         // double m2 = matrix_lees->matrix[1][1];
//         // double m3 = matrix_lees->matrix[1][0];
//         // double m4 = matrix_lees->matrix[0][1];
//         // printf("minor = %f * %f - %f * %f = ", m1, m2, m3, m4);
//         minor = matrix_lees->matrix[0][0] * matrix_lees->matrix[1][1] - matrix_lees->matrix[1][0] * matrix_lees->matrix[0][1];
//         algb += pow(-1, (i+k)) * minor; 
//         // printf("|-%f-|\n", algb );   
//     // printf("- %f -\n", minor );
    
//     return algb;
//     // printf("- %f -\n", minor );
// }

// // void print_mstrix (matrix_t tmp){
// //             for(int minor_i = 0; minor_i < str; minor_i++) {
// //                 if(minor_i != i) { 
// //                     for(int minor_k = 0; minor_k < str; minor_k++) {
// //                         if(minor_k != k) {
// //                             tmp.matrix[minor_i][minor_k] = matrix_lees->matrix[minor_i][minor_k];
// //                             printf("%d.%d  ", minor_i, minor_k);
// //                         }
// //                     }
// //                 }
// //             }
// // }



//     matrix_t tmp;
//     int minor;
//     s21_create_matrix(new_matrix->rows - 1 , new_matrix->columns - 1, &tmp);
//     if(new_matrix->rows < 1) {
//         int minor_i = 0, tmp_i = 0, minor_k = 0, tmp_k = 0 ;
//         while (minor_i < new_matrix->rows) {
//             if(minor_i != i) {
//                 while (minor_k < new_matrix->rows) {
//                     if (minor_k != k) {
//                         // printf("matrix-%f\n",matrix_lees->matrix[minor_i][minor_k]);
//                         printf("%d.%d  ", minor_i, minor_k);
//                         tmp.matrix[tmp_i][tmp_k] = new_matrix->matrix[minor_i][minor_k];
//                         printf(".%f.\n", tmp.matrix[tmp_i][tmp_k]);
//                         tmp_k++;
//                     } else {tmp_k++;}
//                     minor_k++;
//                 }
//                 minor_k = 0;
//                 tmp_i++;
//             } else {tmp_i++;}
//             minor_i ++;
//             printf("\n");
//         }
//     }
//         // double m1 = new_matrix->matrix[0][0];
//         // double m2 = new_matrix->matrix[1][1];
//         // double m3 = new_matrix->matrix[1][0];
//         // double m4 = new_matrix->matrix[0][1];
//         // printf("minor = %f * %f - %f * %f = ", m1, m2, m3, m4);
//     minor = new_matrix->matrix[0][0] * new_matrix->matrix[1][1] - new_matrix->matrix[1][0] * new_matrix->matrix[0][1];
//     return minor;



// // int s21_matrix_reduction(int str, int i, int k, matrix_t *matrix_lees) {
// //     double minor = 0;
// //     double algb = 0;
// //     s21_create_matrix(str, str, matrix_lees); // creat less matrix for minor it is must be in сycle // а не даляю ли я свою основную матрицу такиеми дейтсиями когда передаю ее арес 
// //     printf("____%d___\n", matrix_lees->rows);
// //     if(matrix_lees->rows > 2) {
// //         for(int minor_i = 0; minor_i < str; minor_i++) {
// //             if(minor_i != i) { 
// //                 for(int minor_k = 0; minor_k < str; minor_k++) {
// //                     if(minor_k != k) {
// //                         matrix_lees->matrix[i][k] = matrix_lees->matrix[i][k];
// //                         printf("%d.%d  ", minor_i, minor_k);
// //                     }
// //                 }
// //             }
// //             printf("\n");
// //     } // minor должен возвращаться в таблицу с кторой начинался отсчет ..

// //         for(int minor_i = 0; minor_i < str; minor_i++) {
// //             for(int minor_k = 0; minor_k < str; minor_k++) {
// //                     if (matrix_lees->rows > 2) algb = s21_matrix_reduction(str - 1, minor_i , minor_k , matrix_lees);
// //             } // сега вылетает потому что у меня i сохраняет изначальное значение а матрица у меня меньше
// //         }
// //     }
// // // //    for( i = 0; i < matrix_lees->rows; i++) {
// // //   //     for( k = 0; k < matrix_lees->rows; k++) {
// // //     //       printf("%f.%f",matrix_lees->matrix[i][k]);
// // //       //     // B.matrix[i][k] = k;
// // //        //}
// // //        //printf("\n");
// // //    //}
// // //    //if (matrix_lees->rows > 2) s21_matrix_reduction(matrix_lees->rows - 1, i , k , matrix_lees);
// // double m1 = matrix_lees->matrix[0][0];
// // double m2 = matrix_lees->matrix[1][1];
// // double m3 = matrix_lees->matrix[1][0];
// // double m4 = matrix_lees->matrix[0][1];
// //         printf("minor = %f * %f - %f * %f = ", m1, m2, m3, m4);
// //         minor = matrix_lees->matrix[0][0] * matrix_lees->matrix[1][1] - matrix_lees->matrix[1][0] * matrix_lees->matrix[0][1];
// //         algb += pow(-1, (i+k)) * minor; 
// //         printf("|-%f-|\n", algb );   
// //     // printf("- %f -\n", minor );
    
// //     return algb;
// //     // printf("- %f -\n", minor );
// // }