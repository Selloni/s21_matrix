#include "s21_matrix.h"
// #include <time.h>


int main ()
{   
// srand(time(NULL));   // Initialization, should only be called once.
// int r = rand();      // Returns a pseudo-random integer between 0 and RAND
    matrix_t A, result;
    // double  res;
    // A.count = 0;
   int i, k;
    int n = 4, d = n;
    int  err = 0;
    // int count = 0;
    // double res;
    // matrix_t B;
    // double A = 3, B = 3, result; 
    s21_create_matrix (n, d, &A);
    // s21_create_matrix (n, d, &result);
    // s21_create_matrix (n, d, &tmp);
    // s21_create_matrix (3, 3, &B);
    // s21_create_matrix (3, 3, &result);
    // s21_create_matrix(3, 3, &A);
    // s21_create_matrix(3, 3, &B);
    A.matrix [0][0] = 1;
    A.matrix [0][1] = 2;
    A.matrix [0][2] = 2;
    A.matrix [0][3] = 2;
    A.matrix [1][0] = 4;
    A.matrix [1][1] = 0;
    A.matrix [1][2] = 9;
    A.matrix [1][3] = 9;
    A.matrix [2][0] = 0;
    A.matrix [2][1] = 9;
    A.matrix [2][2] = 2;
    A.matrix [2][3] = 7;
    A.matrix [3][0] = 2;
    A.matrix [3][1] = 4;
    A.matrix [3][2] = 3;
    A.matrix [3][3] = 2;

//    for( i = 0; i < n; i++) {
//        for( k = 0; k < d; k++) {
//            A.matrix[i][k] = rand()%20;
//            printf("%f ",A.matrix[i][k]);
//            // B.matrix[i][k] = k;
//        }
//        printf("\n");
//    }
    for( i = 0; i < n; i++) {
        for( k = 0; k < n; k++) {
            printf("%f ",A.matrix[i][k]);
        }
        printf("\n");
    }
    printf("___.____.___.__\n");
    // for( i = 0; i < n; i++) {
//        for(int k = 0; k < d; k++) {
            // A.matrix[i][k] = s21_matrix_reduction(A.rows, i, k, result);
            err = s21_calc_complements(&A, &result);
            
            // result.matrix[i][k] = s21_matrix_reduction(A.rows, i, k, &A, count);
            printf("err%d\n", err);
            // printf("i=%d. k=%d. res = %f \n", i, k, res);
//        }
    // }
    
    // for( i = 0; i < 3; i++) {
    //     for( k = 0 ; k < 3; k++) {
    //         printf("%f ",B.matrix[i][k]);
    //     }
    //     printf("\n");
    // }
    // printf("____________\n");
    // s21_sub_matrix(&A, &B, &result);
   // s21 _transpose(&A, &result);
   ////// exit done matrix ///////
    // for( i = 0; i < n; i++) {
    //     for( k = 0; k < d; k++) {
    //         printf("%f ",result.matrix[i][k]);
    //     }
    //     printf("exit\n");
    // }
    return 0;      
}