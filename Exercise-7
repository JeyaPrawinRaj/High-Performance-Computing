#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_THREADS 4

typedef struct {
    int a, b;
    char op;
} Task;

Task buffer[BUFFER_SIZE];
int in = 0, out = 0;
int done = 0;

sem_t empty, full, mutex;

int calculate(int a, int b, char op, int *valid) {
    *valid = 1;
    switch(op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) { *valid = 0; return 0; }
            return a / b;
        default:
            *valid = 0;
            return 0;
    }
}

void* producer(void* arg) {
    char ops[] = {'+', '-', '*', '/'};

    for(int i = 0; i < 10; i++) {
        Task t;
        t.a = rand() % 50;
        t.b = rand() % 50;
        t.op = ops[rand() % 4];

        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in] = t;
        printf("Produced: %d %c %d\n", t.a, t.op, t.b);
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex);
        sem_post(&full);
        sleep(1);
    }

    // Signal done
    sem_wait(&mutex);
    done = 1;
    sem_post(&mutex);

    for(int i = 0; i < NUM_THREADS; i++)
        sem_post(&full);

    return NULL;
}

void* consumer(void* arg) {
    int id = *((int*)arg);

    while(1) {
        sem_wait(&full);
        sem_wait(&mutex);

        if (done && in == out) {
            sem_post(&mutex);
            break;
        }

        Task t = buffer[out];
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&mutex);
        sem_post(&empty);

        int valid;
        int result = calculate(t.a, t.b, t.op, &valid);

        if(valid)
            printf("Thread %d: %d %c %d = %d\n", id, t.a, t.op, t.b, result);
        else
            printf("Thread %d: Invalid (%d %c %d)\n", id, t.a, t.op, t.b);

        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t prod, cons[NUM_THREADS];
    int ids[NUM_THREADS];

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_create(&prod, NULL, producer, NULL);

    for(int i = 0; i < NUM_THREADS; i++) {
        ids[i] = i + 1;
        pthread_create(&cons[i], NULL, consumer, &ids[i]);
    }

    pthread_join(prod, NULL);

    for(int i = 0; i < NUM_THREADS; i++)
        pthread_join(cons[i], NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
