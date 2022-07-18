#include "s21_matrix.h"
#include <time.h>


int main ()
{   

srand(time(NULL));   // Initialization, should only be called once.
int r = rand();      // Returns a pseudo-random integer between 0 and RAND
    matrix_t A, B, result;
    // double A = 3, B = 3, result; 
    s21_create_matrix (3, 6, &A);
    s21_create_matrix (3, 3, &B);
    // s21_create_matrix (3, 3, &result);
    // s21_create_matrix(3, 3, &A);
    // s21_create_matrix(3, 3, &B);
    for(int i = 0; i < 3; i++) {
        for(int k = 0 ; k < 6; k++) {
            A.matrix[i][k] = r % 33;
            B.matrix[i][k] = k;
        }
    }
    for(int i = 0; i < 3; i++) {
        for(int k = 0 ; k < 6; k++) {
            printf("%f ",A.matrix[i][k]);
        }
        printf("\n");
    }
    printf("____________\n");
    // for(int i = 0; i < 3; i++) {
    //     for(int k = 0 ; k < 3; k++) {
    //         printf("%f ",B.matrix[i][k]);
    //     }
    //     printf("\n");
    // }
    // printf("____________\n");
    // s21_sub_matrix(&A, &B, &result);
    s21_transpose(&A, &result);
    for(int i = 0; i < 6; i++) {
        for(int k = 0 ; k < 3; k++) {
            printf("%f ",result.matrix[i][k]);
        }
        printf("\n");
    }
    return 0;      
}