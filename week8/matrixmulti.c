#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define M_SIZE 1000
#define NUM_THREADS 4

int matrixA[M_SIZE][M_SIZE];
int matrixB[M_SIZE][M_SIZE];
int resultMatrix[M_SIZE][M_SIZE];

typedef struct {
    int startRow;
    int endRow;
} divi;

void* multiplyRows(void* arg) {
    divi* threadInfo = (divi*)arg;

    for (int i = threadInfo->startRow; i < threadInfo->endRow; i++) {
        for (int j = 0; j < M_SIZE; j++) {
            resultMatrix[i][j] = 0;
            for (int k = 0; k < M_SIZE; k++) {
                resultMatrix[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    pthread_exit(NULL);
}
int main() {
    for (int i = 0; i < M_SIZE; i++) {
        for (int j = 0; j < M_SIZE; j++) {
            matrixA[i][j] = rand() % 10;
            matrixB[i][j] = rand() % 10;
        }
    }
    pthread_t threads[NUM_THREADS];
    divi threadInfo[NUM_THREADS];

    int rowsPerThread = M_SIZE / NUM_THREADS;
    for (int i = 0; i < NUM_THREADS; i++) {
        threadInfo[i].startRow = i * rowsPerThread;
        threadInfo[i].endRow = (i == NUM_THREADS - 1) ? M_SIZE : (i + 1) * rowsPerThread;

        pthread_create(&threads[i], NULL, multiplyRows, (void*)&threadInfo[i]);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Result Matrix (Using Pthreads):\n");
    for (int i = 0; i < M_SIZE; i++) {
        for (int j = 0; j < M_SIZE; j++) {
            printf("%d ", resultMatrix[i][j]);
        }
        printf("\n");
    }
}