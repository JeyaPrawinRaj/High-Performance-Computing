#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define QUEUE_SIZE 10
#define MAX_WORD_LEN 50
#define RESULT_SIZE 100
#define NUM_THREADS 5

char work_queue[QUEUE_SIZE][MAX_WORD_LEN];
char result_buffer[RESULT_SIZE][MAX_WORD_LEN + 20];

int work_count = 0, result_count = 0;
int head = 0, tail = 0;
int finished = 0;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_not_empty = PTHREAD_COND_INITIALIZER;

const char *dictionary[] = {"java","c++","python","julia","golang"};
int dict_size = 5;

int is_in_dictionary(char *word) {
    for (int i = 0; i < dict_size; i++) {
        if (strcmp(word, dictionary[i]) == 0)
            return 1;
    }
    return 0;
}

void* worker(void* arg) {
    while (1) {
        char word[MAX_WORD_LEN];

        pthread_mutex_lock(&lock);
        while (work_count == 0 && !finished) {
            pthread_cond_wait(&cond_not_empty, &lock);
        }

        if (work_count == 0 && finished) {
            pthread_mutex_unlock(&lock);
            break;
        }

        strcpy(word, work_queue[head]);
        head = (head + 1) % QUEUE_SIZE;
        work_count--;

        pthread_cond_signal(&cond_not_full);
        pthread_mutex_unlock(&lock);

        char result[MAX_WORD_LEN + 20];
        if (is_in_dictionary(word))
            sprintf(result, "%s: Correct", word);
        else
            sprintf(result, "%s: Incorrect", word);

        pthread_mutex_lock(&lock);
        strcpy(result_buffer[result_count++], result);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    const char *input[] = {"java","c","pytho","julia","go"};
    int input_len = 5;

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++)
        pthread_create(&threads[i], NULL, worker, NULL);

    // Producer logic
    for (int i = 0; i < input_len; i++) {
        pthread_mutex_lock(&lock);

        while (work_count == QUEUE_SIZE)
            pthread_cond_wait(&cond_not_full, &lock);

        strcpy(work_queue[tail], input[i]);
        tail = (tail + 1) % QUEUE_SIZE;
        work_count++;

        pthread_cond_signal(&cond_not_empty);
        pthread_mutex_unlock(&lock);
    }

    // Signal completion
    pthread_mutex_lock(&lock);
    finished = 1;
    pthread_cond_broadcast(&cond_not_empty);
    pthread_mutex_unlock(&lock);

    // Join threads
    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    printf("Final Results:\n");
    for (int i = 0; i < result_count; i++) {
        printf("%s\n", result_buffer[i]);
    }

    return 0;
}
