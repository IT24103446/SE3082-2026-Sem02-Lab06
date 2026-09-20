#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1000000
#define STRIP_SIZE 8

int main()
{
    float *A = malloc(N * sizeof(float));
    float *B = malloc(N * sizeof(float));
    float *C = malloc(N * sizeof(float));

    if (A == NULL || B == NULL || C == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < N; i++) {
        A[i] = i * 1.0f;
        B[i] = 2.0f;
    }

    double start = omp_get_wtime();

    #pragma omp parallel for
    for (int i = 0; i < N; i += STRIP_SIZE) {

        int end = i + STRIP_SIZE;

        if (end > N)
            end = N;

        for (int j = i; j < end; j++) {
            C[j] = A[j] * B[j];
        }
    }

    double end = omp_get_wtime();

    printf("C[0] = %.2f\n", C[0]);
    printf("C[999999] = %.2f\n", C[999999]);
    printf("Time = %.6f seconds\n", end - start);

    free(A);
    free(B);
    free(C);

    return 0;
}
