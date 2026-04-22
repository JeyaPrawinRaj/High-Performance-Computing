#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <stddef.h>

typedef struct {
    char name[20];
    int rno;
    int marks;
    char grade;
} Student;

char calculate_grade(int marks) {
    if (marks >= 90) return 'A';
    else if (marks >= 80) return 'B';
    else if (marks >= 70) return 'C';
    else if (marks >= 60) return 'D';
    else return 'E';
}

int main(int argc, char *argv[]) {
    int rank, size, n, i;
    Student *students = NULL;
    Student *sub_students;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        FILE *fp = fopen("input.txt", "r");
        if (!fp) {
            printf("Error opening file\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        fscanf(fp, "%d", &n);
        students = (Student *)malloc(n * sizeof(Student));

        for (i = 0; i < n; i++) {
            fscanf(fp, "%s %d %d",
                   students[i].name,
                   &students[i].rno,
                   &students[i].marks);
        }
        fclose(fp);
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int chunk = n / size;
    sub_students = (Student *)malloc(chunk * sizeof(Student));

    int blocklengths[] = {20, 1, 1, 1};
    MPI_Aint offsets[] = {
        offsetof(Student, name),
        offsetof(Student, rno),
        offsetof(Student, marks),
        offsetof(Student, grade)
    };
    MPI_Datatype types[] = {MPI_CHAR, MPI_INT, MPI_INT, MPI_CHAR};
    MPI_Datatype MPI_STUDENT;

    MPI_Type_create_struct(4, blocklengths, offsets, types, &MPI_STUDENT);
    MPI_Type_commit(&MPI_STUDENT);

    MPI_Scatter(students, chunk, MPI_STUDENT,
                sub_students, chunk, MPI_STUDENT,
                0, MPI_COMM_WORLD);

    for (i = 0; i < chunk; i++) {
        sub_students[i].grade = calculate_grade(sub_students[i].marks);
    }

    MPI_Gather(sub_students, chunk, MPI_STUDENT,
               students, chunk, MPI_STUDENT,
               0, MPI_COMM_WORLD);

    if (rank == 0) {
        FILE *out = fopen("output.txt", "w");
        fprintf(out, "Name Roll Marks Grade\n");
        for (i = 0; i < n; i++) {
            fprintf(out, "%s %d %d %c\n",
                    students[i].name,
                    students[i].rno,
                    students[i].marks,
                    students[i].grade);
        }
        fclose(out);
        free(students);
    }

    free(sub_students);
    MPI_Type_free(&MPI_STUDENT);
    MPI_Finalize();
    return 0;
}
