#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define MAX_QUEUE 100
#define MAX_LINE 256

int NUM_PRODUCERS;
int NUM_CONSUMERS;

char queue[MAX_QUEUE][MAX_LINE];
int front = 0, rear = 0, count = 0;

int done_producers = 0;

omp_lock_t lock;

void enqueue(char *line)
{
    while (1) {
        omp_set_lock(&lock);

        if (count < MAX_QUEUE) {
            strcpy(queue[rear], line);
            rear = (rear + 1) % MAX_QUEUE;
            count++;
            omp_unset_lock(&lock);
            break;
        }

        omp_unset_lock(&lock);
    }
}

int dequeue(char *line)
{
    int got = 0;

    omp_set_lock(&lock);

    if (count > 0) {
        strcpy(line, queue[front]);
        front = (front + 1) % MAX_QUEUE;
        count--;
        got = 1;
    }

    omp_unset_lock(&lock);
    return got;
}

void producer(int id, char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp) return;

    char line[MAX_LINE];

    while (fgets(line, MAX_LINE, fp)) {
        enqueue(line);
    }

    fclose(fp);

    #pragma omp atomic
    done_producers++;
}

void consumer(int id)
{
    char line[MAX_LINE];

    while (1) {
        if (dequeue(line)) {

            #pragma omp critical
            {
                char *token = strtok(line, " \t\n");
                while (token != NULL) {
                    printf("Consumer %d: %s\n", id, token);
                    token = strtok(NULL, " \t\n");
                }
            }

        } else {
            #pragma omp flush(done_producers)
            if (done_producers == NUM_PRODUCERS)
                break;
        }
    }
}

int main()
{
    printf("Enter number of producers: ");
    scanf("%d",&NUM_PRODUCERS);

    printf("Enter number of consumers: ");
    scanf("%d",&NUM_CONSUMERS);

    char *files[2] = {"file1.txt","file2.txt"};

    omp_init_lock(&lock);

    #pragma omp parallel num_threads(NUM_PRODUCERS + NUM_CONSUMERS)
    {
        int tid = omp_get_thread_num();

        if (tid < NUM_PRODUCERS)
            producer(tid, files[tid]);
        else
            consumer(tid - NUM_PRODUCERS);
    }

    omp_destroy_lock(&lock);

    return 0;
}
