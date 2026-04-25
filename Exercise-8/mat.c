#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define N 1000

int main(int argc, char* argv[])
{
    if(argc < 2) {
        fprintf(stderr, "Usage: %s <thread_count>\n", argv[0]);
        return 1;
    }

    int thread_count = atoi(argv[1]), i;

    double *A = (double*)malloc(N * sizeof(double));
    double *B = (double*)malloc(N * sizeof(double));
    double *C = (double*)malloc(N * sizeof(double));

    if (!A || !B || !C) {
        fprintf(stderr, "Memory Allocation failed\n");
        return 1;
    }

    #pragma omp parallel for num_threads(thread_count)
    for(i = 0; i < N; i++) {
        A[i] = i * 1.0;
        B[i] = i * 2.0;
    }

    double *thread_times = (double*)calloc(thread_count, sizeof(double));

    FILE *fout = fopen("file1.txt", "w");

    double start_time = omp_get_wtime();

    #pragma omp parallel num_threads(thread_count)
    {
        int tid = omp_get_thread_num();
        double t_start = omp_get_wtime();

        #pragma omp for
        for (i = 0; i < N; i++) {
            C[i] = A[i] + B[i];

            #pragma omp critical
            fprintf(fout,"Thread %d calculated C[%d] = %.2f\n", tid, i, C[i]);
        }

        double t_end = omp_get_wtime();
        thread_times[tid] = t_end - t_start;
    }

    double end_time = omp_get_wtime();

    fclose(fout);

    free(A); 
    free(B); 
    free(C); 
    free(thread_times);

    return 0;
}
