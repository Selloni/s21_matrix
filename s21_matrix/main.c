#include "s21_matrix.h"
// #include <time.h>


int main ()
{   
// srand(time(NULL));   // Initialization, should only be called once.
// int r = rand();      // Returns a pseudo-random integer between 0 and RAND
    matrix_t A, result;
    // A.count = 0;
    int i, k;
    int n = 3, d = n;
    double minor = 0;
    // int count = 0;
    // double res;
    // matrix_t B;
    // double A = 3, B = 3, result; 
    s21_create_matrix (n, d, &A);
    s21_create_matrix (n, d, &result);
    // s21_create_matrix (n, d, &tmp);
    // s21_create_matrix (3, 3, &B);
    // s21_create_matrix (3, 3, &result);
    // s21_create_matrix(3, 3, &A);
    // s21_create_matrix(3, 3, &B);
    for( i = 0; i < n; i++) {
        for( k = 0; k < d; k++) {
            A.matrix[i][k] = rand()%20;
            printf("%f ",A.matrix[i][k]);
            // B.matrix[i][k] = k;
        }
        printf("\n");
    }
    // for( i = 0; i < 3; i++) {
    //     for( k = 0; k < 3; k++) {
    //         printf("%f ",A.matrix[i][k]);
    //     }
    //     printf("\n");
    // }
    printf("___.____.___.__\n");
    // for( i = 0; i < n; i++) {
        for(k = 0; k < d; k++) {
            // A.matrix[i][k] = s21_matrix_reduction(A.rows, i, k, result);
            minor = s21_less_matrix(0, k, &A);
            
            // result.matrix[i][k] = s21_matrix_reduction(A.rows, i, k, &A, count);
            printf("minor%f\n", minor);
            // printf("i=%d. k=%d. res = %f \n", i, k, res);
        }
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