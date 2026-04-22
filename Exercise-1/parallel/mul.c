#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define MAX 1000
#define ROWS_PER_CHILD 10

int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];

double time_diff(struct timespec s, struct timespec e)
{
    return (e.tv_sec - s.tv_sec) +
           (e.tv_nsec - s.tv_nsec) / 1e9;
}

int main()
{
    int r1, c1, r2, c2, i, j, k, c;
    pid_t pid;

    printf("Enter rows and columns of Matrix A: ");
    scanf("%d %d", &r1, &c1);
    printf("Enter rows and columns of Matrix B: ");
    scanf("%d %d", &r2, &c2);

    if (c1 != r2)
    {
        printf("Not possible\n");
        exit(1);
    }

    srand(time(NULL));

    for (i = 0; i < r1; i++)
        for (j = 0; j < c1; j++)
            A[i][j] = rand() % 10;

    for (i = 0; i < r2; i++)
        for (j = 0; j < c2; j++)
            B[i][j] = rand() % 10;

    int num_children = (r1 + ROWS_PER_CHILD - 1) / ROWS_PER_CHILD;

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (c = 0; c < num_children; c++)
    {
        pid = fork();

        if (pid == 0)
        {
            int start_row = c * ROWS_PER_CHILD;
            int rows = ROWS_PER_CHILD;

            if (start_row + rows > r1)
                rows = r1 - start_row;

            for (i = 0; i < rows; i++)
                for (j = 0; j < c2; j++)
                {
                    C[start_row + i][j] = 0;
                    for (k = 0; k < c1; k++)
                        C[start_row + i][j] += A[start_row + i][k] * B[k][j];
                }

            exit(0);
        }
    }

    for (i = 0; i < num_children; i++)
        wait(NULL);

    clock_gettime(CLOCK_MONOTONIC, &end);

    printf("Execution Time: %.6f sec\n", time_diff(start, end));

    return 0;
}
