#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000

int A[MAX][MAX], B[MAX][MAX];
int Add[MAX][MAX], Sub[MAX][MAX];

double time_diff(struct timespec s, struct timespec e)
{
    return (e.tv_sec - s.tv_sec) +
           (e.tv_nsec - s.tv_nsec) / 1e9;
}

int main()
{
    int r, c, i, j;

    printf("Enter number of rows and columns: ");
    scanf("%d %d", &r, &c);

    srand(time(NULL));

    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
        {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }

    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
        {
            Add[i][j] = A[i][j] + B[i][j];
            Sub[i][j] = A[i][j] - B[i][j];
        }

    clock_gettime(CLOCK_MONOTONIC, &end);

    printf("Execution Time: %.6f sec\n", time_diff(start, end));

    return 0;
}
