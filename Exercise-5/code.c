#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int **A, **B, **Add, **Mul;
int r1, c1, r2, c2;

void* matrixAddition(void* arg) {
    for(int i = 0; i < r1; i++) {
        for(int j = 0; j < c1; j++) {
            Add[i][j] = A[i][j] + B[i][j];
        }
    }
    pthread_exit(NULL);
}

void* matrixMultiplication(void* arg) {
    for(int i = 0; i < r1; i++) {
        for(int j = 0; j < c2; j++) {
            Mul[i][j] = 0;
            for(int k = 0; k < c1; k++) {
                Mul[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    pthread_exit(NULL);
}

int** allocateMatrix(int r, int c) {
    int** mat = (int**)malloc(r * sizeof(int*));
    for (int i = 0; i < r; i++)
        mat[i] = (int*)malloc(c * sizeof(int));
    return mat;
}

void printMatrix(int** mat, int r, int c) {
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
}

int main() {
    pthread_t t1, t2;

    printf("Enter rows and columns of Matrix A: ");
    scanf("%d %d", &r1, &c1);

    printf("Enter rows and columns of Matrix B: ");
    scanf("%d %d", &r2, &c2);

    A = allocateMatrix(r1, c1);
    B = allocateMatrix(r2, c2);

    printf("Enter Matrix A:\n");
    for(int i = 0; i < r1; i++)
        for(int j = 0; j < c1; j++)
            scanf("%d", &A[i][j]);

    printf("Enter Matrix B:\n");
    for(int i = 0; i < r2; i++)
        for(int j = 0; j < c2; j++)
            scanf("%d", &B[i][j]);

    if (r1 == r2 && c1 == c2)
        Add = allocateMatrix(r1, c1);

    if (c1 == r2)
        Mul = allocateMatrix(r1, c2);

    if (r1 == r2 && c1 == c2)
        pthread_create(&t1, NULL, matrixAddition, NULL);

    if (c1 == r2)
        pthread_create(&t2, NULL, matrixMultiplication, NULL);

    if (r1 == r2 && c1 == c2)
        pthread_join(t1, NULL);

    if (c1 == r2)
        pthread_join(t2, NULL);

    if (r1 == r2 && c1 == c2) {
        printf("\nAddition Result:\n");
        printMatrix(Add, r1, c1);
    }

    if (c1 == r2) {
        printf("\nMultiplication Result:\n");
        printMatrix(Mul, r1, c2);
    } else {
        printf("\nMultiplication not possible\n");
    }

    return 0;
}
