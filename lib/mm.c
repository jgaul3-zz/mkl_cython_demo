#define min(x,y) (((x) < (y)) ? (x) : (y))

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "mkl.h"

#define LOOP_COUNT 1000

int test1(void)
{
    struct timeval start, end;
    gettimeofday(&start, NULL);

    double *A, *B, *C;
    int m, n, p, i, j, k, r;
    double alpha, beta;
    double sum;
    double s_initial, s_elapsed;

    m = 2000, p = 200, n = 1000;
    alpha = 1.0; beta = 0.0;

    A = (double *)mkl_malloc( m*p*sizeof( double ), 64 );
    B = (double *)mkl_malloc( p*n*sizeof( double ), 64 );
    C = (double *)mkl_malloc( m*n*sizeof( double ), 64 );
    if (A == NULL || B == NULL || C == NULL) {
        printf( "\n ERROR: Can't allocate memory for matrices. Aborting... \n\n");
        mkl_free(A);
        mkl_free(B);
        mkl_free(C);
        return 1;
    }

    for (i = 0; i < (m*p); i++) {
        A[i] = (double)(i+1);
    }

    for (i = 0; i < (p*n); i++) {
        B[i] = (double)(-i-1);
    }

    for (i = 0; i < (m*n); i++) {
        C[i] = 0.0;
    }

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            sum = 0.0;
            for (k = 0; k < p; k++)
                sum += A[p*i+k] * B[n*k+j];
            C[n*i+j] = sum;
        }
    }

    s_initial = dsecnd();
    for (r = 0; r < LOOP_COUNT; r++) {
        for (i = 0; i < m; i++) {
            for (j = 0; j < n; j++) {
                sum = 0.0;
                for (k = 0; k < p; k++)
                    sum += A[p*i+k] * B[n*k+j];
                C[n*i+j] = sum;
            }
        }
    }
    s_elapsed = (dsecnd() - s_initial) / LOOP_COUNT;

    printf (" == Matrix multiplication using triple nested loop completed == \n"
            " == at %.5f milliseconds == \n\n", (s_elapsed * 1000));

    mkl_free(A);
    mkl_free(B);
    mkl_free(C);

    if (s_elapsed < 0.9/LOOP_COUNT) {
        s_elapsed=1.0/LOOP_COUNT/s_elapsed;
        i=(int)(s_elapsed*LOOP_COUNT)+1;
        printf(" It is highly recommended to define LOOP_COUNT for this example on your \n"
               " computer as %i to have total execution time about 1 second for reliability \n"
               " of measurements\n\n", i);
    }
    gettimeofday(&end, NULL);
    double time_taken; 
  
    time_taken = (end.tv_sec - start.tv_sec) * 1e6; 
    time_taken = (time_taken + (end.tv_usec -  
                              start.tv_usec)) * 1e-6;

    printf (" Example completed in %.1f milliseconds. \n\n", time_taken);
    return 0;
}

int test2(void)
{
    struct timeval start, end; 
    gettimeofday(&start, NULL);

    double *A, *B, *C;
    int m, n, p, i, j, k, r;
    double alpha, beta;
    double sum;
    double s_initial, s_elapsed;

    m = 2000, p = 200, n = 1000;
    alpha = 1.0; beta = 0.0;

    A = (double *)mkl_malloc( m*p*sizeof( double ), 64 );
    B = (double *)mkl_malloc( p*n*sizeof( double ), 64 );
    C = (double *)mkl_malloc( m*n*sizeof( double ), 64 );
    if (A == NULL || B == NULL || C == NULL) {
        printf( "\n ERROR: Can't allocate memory for matrices. Aborting... \n\n");
        mkl_free(A);
        mkl_free(B);
        mkl_free(C);
        return 1;
    }

    for (i = 0; i < (m*p); i++) {
        A[i] = (double)(i+1);
    }

    for (i = 0; i < (p*n); i++) {
        B[i] = (double)(-i-1);
    }

    for (i = 0; i < (m*n); i++) {
        C[i] = 0.0;
    }

    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                m, n, p, alpha, A, p, B, n, beta, C, n);

    s_initial = dsecnd();
    for (r = 0; r < LOOP_COUNT; r++) {
        cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                    m, n, p, alpha, A, p, B, n, beta, C, n);
    }
    s_elapsed = (dsecnd() - s_initial) / LOOP_COUNT;

    printf (" == Matrix multiplication using Intel(R) MKL dgemm completed == \n"
            " == at %.5f milliseconds == \n\n", (s_elapsed * 1000));

    mkl_free(A);
    mkl_free(B);
    mkl_free(C);

    if (s_elapsed < 0.9/LOOP_COUNT) {
        s_elapsed=1.0/LOOP_COUNT/s_elapsed;
        i=(int)(s_elapsed*LOOP_COUNT)+1;
        printf(" It is highly recommended to define LOOP_COUNT for this example on your \n"
               " computer as %i to have total execution time about 1 second for reliability \n"
               " of measurements\n\n", i);
    }
    
    gettimeofday(&end, NULL); 
    double time_taken; 
  
    time_taken = (end.tv_sec - start.tv_sec) * 1e6; 
    time_taken = (time_taken + (end.tv_usec -  
                              start.tv_usec)) * 1e-6;

    printf (" Example completed in %.1f milliseconds. \n\n", time_taken);
    return 0;
}

int main(void)
{
    return test2();
}

