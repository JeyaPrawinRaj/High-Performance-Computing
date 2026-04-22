#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000

int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];

int main()
{
    int r1, c1, r2, c2, i, j, k;
    struct timespec start, end;

    printf("Enter rows and columns of Matrix A: ");
    scanf("%d %d", &r1, &c1);
    printf("Enter rows and columns of Matrix B: ");
    scanf("%d %d", &r2, &c2);

    if (c1 != r2)
    {
        printf("Multiplication not possible\n");
        return 1;
    }

    srand(time(NULL));

    for (i = 0; i < r1; i++)
        for (j = 0; j < c1; j++)
            A[i][j] = rand() % 10;

    for (i = 0; i < r2; i++)
        for (j = 0; j < c2; j++)
            B[i][j] = rand() % 10;

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (i = 0; i < r1; i++)
        for (j = 0; j < c2; j++)
        {
            C[i][j] = 0;
            for (k = 0; k < c1; k++)
                C[i][j] += A[i][k] * B[k][j];
        }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double t = (end.tv_sec - start.tv_sec) +
               (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Execution Time: %.6f sec\n", t);

    return 0;
}
