#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int N = 20;
    int *array = NULL;
    int *sub_array;
    int search_num;
    int local_count = 0, total_count = 0;
    double start_time, end_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int chunk_size = N / size;
    sub_array = (int *)malloc(chunk_size * sizeof(int));

    if (rank == 0) {
        array = (int *)malloc(N * sizeof(int));

        printf("Enter number to search: ");
        scanf("%d", &search_num);

        srand(time(NULL));
        for (int i = 0; i < N; i++) {
            array[i] = rand() % 10;
            printf("%d ", array[i]);
        }
        printf("\n");
    }

    MPI_Bcast(&search_num, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(array, chunk_size, MPI_INT,
                sub_array, chunk_size, MPI_INT,
                0, MPI_COMM_WORLD);

    start_time = MPI_Wtime();

    for (int i = 0; i < chunk_size; i++) {
        if (sub_array[i] == search_num)
            local_count++;
    }

    MPI_Reduce(&local_count, &total_count, 1,
               MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    end_time = MPI_Wtime();

    printf("Process %d -> Count: %d\n", rank, local_count);

    if (rank == 0) {
        printf("Total Frequency: %d\n", total_count);
        printf("Execution Time: %f seconds\n", end_time - start_time);
    }

    free(sub_array);
    if (rank == 0) free(array);

    MPI_Finalize();
    return 0;
}
