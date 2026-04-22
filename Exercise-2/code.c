#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <mpi.h>

#define MAX 100

void toUpperCase(char str[])
{
    for (int i = 0; str[i] != '\0'; i++)
        str[i] = toupper(str[i]);
}

int isPalindrome(char str[])
{
    int i = 0, j = strlen(str) - 1;
    while (i < j)
    {
        if (str[i] != str[j])
            return 0;
        i++; j--;
    }
    return 1;
}

int main(int argc, char *argv[])
{
    char str[MAX];
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Status status;

    if (rank != 0)
    {
        if (rank == 1) strcpy(str, "p-p comm");
        else if (rank == 2) strcpy(str, "tenet");
        else if (rank == 3) strcpy(str, "madam");
        else if (rank == 4) strcpy(str, "cse-a");
        else strcpy(str, "hello");

        int tag = (rank % 2 == 0) ? 2 : 1;
        MPI_Send(str, MAX, MPI_CHAR, 0, tag, MPI_COMM_WORLD);
    }
    else
    {
        for (int i = 1; i < size; i++)
        {
            MPI_Recv(str, MAX, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG,
                     MPI_COMM_WORLD, &status);

            if (status.MPI_TAG == 1)
            {
                toUpperCase(str);
                printf("Process %d: %s\n", status.MPI_SOURCE, str);
            }
            else
            {
                if (isPalindrome(str))
                    printf("Process %d: %s (Palindrome)\n", status.MPI_SOURCE, str);
                else
                    printf("Process %d: %s (Not Palindrome)\n", status.MPI_SOURCE, str);
            }
        }
    }

    MPI_Finalize();
    return 0;
}
