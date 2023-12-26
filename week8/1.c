#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void processA() {
    printf("Process A is running.\n");
}

void processB() {
    printf("Process B is running.\n");
}

void alarmHandler(int signum) {
    // This handler function will be called when the alarm signal is received
    // It will toggle between Process A and Process B
    static int flag = 0;
    if (flag == 0) {
        processA();
        flag = 1;
    } else {
        processB();
        flag = 0;
    }
    // Set the alarm for the next context switch (1 second)
    alarm(1);
}

int main() {
    // Set up the alarm signal handler
    signal(SIGALRM, alarmHandler);

    // Set the initial alarm for the first context switch (1 second)
    alarm(1);

    // Keep the main process running to allow the alarm to trigger
    while (1) {
        // The main process will be interrupted by the alarm signal
        // and control will be transferred to the alarmHandler function
        pause();  // Suspend the process until a signal is received
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

#define CHUNK_SIZE 64
#define NUM_CHUNKS 10

typedef struct {
    size_t size;
    char data[CHUNK_SIZE];
} FixedChunk;

void* allocateMemory(size_t size) {
    // Use mmap to allocate a larger chunk of memory
    return mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
}

void deallocateMemory(void* ptr, size_t size) {
    // Use munmap to deallocate the memory
    munmap(ptr, size);
}

void* allocateFixedChunk() {
    // Allocate a fixed-size chunk from the larger chunk
    FixedChunk* chunk = (FixedChunk*)allocateMemory(CHUNK_SIZE * NUM_CHUNKS);
    return chunk;
}

void deallocateFixedChunk(void* ptr) {
    // Deallocate the larger chunk
    deallocateMemory(ptr, CHUNK_SIZE * NUM_CHUNKS);
}

void* allocateDynamicMemory(size_t size) {
    // Allocate dynamic memory using malloc
    return malloc(size);
}

void deallocateDynamicMemory(void* ptr) {
    // Deallocate dynamic memory using free
    free(ptr);
}

int main() {
    // Memory management for fixed chunk sizes
    FixedChunk* fixedChunk = (FixedChunk*)allocateFixedChunk();
    printf("Fixed chunk allocated at address: %p\n", (void*)fixedChunk);
    deallocateFixedChunk(fixedChunk);

    // Memory management for dynamic memory
    size_t dynamicSize = 100;
    int* dynamicMemory = (int*)allocateDynamicMemory(dynamicSize);
    printf("Dynamic memory allocated at address: %p\n", (void*)dynamicMemory);
    deallocateDynamicMemory(dynamicMemory);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MATRIX_SIZE 1000
#define NUM_THREADS 4

int matrixA[M_SIZE][M_SIZE];
int matrixB[M_SIZE][M_SIZE];
int resultMatrix[M_SIZE][M_SIZE];

typedef struct {
    int startRow;
    int endRow;
} ThreadInfo;

void* multiplyRows(void* arg) {
    ThreadInfo* threadInfo = (ThreadInfo*)arg;

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
    ThreadInfo threadInfo[NUM_THREADS];

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

    // Using processes for matrix multiplication
    pid_t pid;
    int rowsPerProcess = M_SIZE / NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; i++) {
        pid = fork();

        if (pid == 0) {  // Child process
            int startRow = i * rowsPerProcess;
            int endRow = (i == NUM_THREADS - 1) ? M_SIZE : (i + 1) * rowsPerProcess;

            for (int row = startRow; row < endRow; row++) {
                for (int col = 0; col < M_SIZE; col++) {
                    resultMatrix[row][col] = 0;
                    for (int k = 0; k < M_SIZE; k++) {
                        resultMatrix[row][col] += matrixA[row][k] * matrixB[k][col];
                    }
                }
            }

            exit(0);
        } else if (pid < 0) {
            fprintf(stderr, "Error in forking process\n");
            exit(1);
        }
    }

    // Wait for all child processes to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        wait(NULL);
    }

    // Print the result matrix (just to show the result)
    printf("\nResult Matrix (Using Processes):\n");
    for (int i = 0; i < M_SIZE; i++) {
        for (int j = 0; j < M_SIZE; j++) {
            printf("%d ", resultMatrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>

#define ARRAY_SIZE 10000
#define NUM_THREADS 4

int sharedArray[ARRAY_SIZE];

// Structure to hold thread-specific information
typedef struct {
    int start;
    int end;
} ThreadInfo;

// Function to perform insertion sort on a specific range of the array
void insertionSort(int arr[], int start, int end) {
    int i, key, j;
    for (i = start + 1; i <= end; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= start && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Function to perform merge sort on a specific range of the array
void merge(int arr[], int left, int middle, int right) {
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    // Create temporary arrays
    int L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[middle + 1 + j];

    // Merge the temporary arrays back into arr[left..right]
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        // Same as (left+right)/2, but avoids overflow for large left and right
        int middle = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        // Merge the sorted halves
        merge(arr, left, middle, right);
    }
}

// Function to perform quicksort on a specific range of the array
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            // Swap arr[i] and arr[j]
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // Swap arr[i + 1] and arr[high] (pivot)
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        // Recursively sort elements before and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to be executed by each thread for sorting a specific range
void* threadSort(void* arg) {
    ThreadInfo* threadInfo = (ThreadInfo*)arg;
    int start = threadInfo->start;
    int end = threadInfo->end;

    // Uncomment the desired sorting algorithm
    // insertionSort(sharedArray, start, end);
    // mergeSort(sharedArray, start, end);
    quickSort(sharedArray, start, end);

    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));

    // Initialize the shared array with random values
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sharedArray[i] = rand() % 100;
    }

    // Uncomment to print the original array
    // printf("Original array: ");
    // for (int i = 0; i < ARRAY_SIZE; i++) {
    //     printf("%d ", sharedArray[i]);
    // }
    // printf("\n");

    pthread_t threads[NUM_THREADS];
    ThreadInfo threadInfo[NUM_THREADS];

    // Divide the array into segments for each thread
    int elementsPerThread = ARRAY_SIZE / NUM_THREADS;
    for (int i = 0; i < NUM_THREADS; i++) {
        threadInfo[i].start = i * elementsPerThread;
        threadInfo[i].end = (i == NUM_THREADS - 1) ? ARRAY_SIZE - 1 : (i + 1) * elementsPerThread - 1;

        pthread_create(&threads[i], NULL, threadSort, (void*)&threadInfo[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Merge the sorted segments from each thread
    int start = 0;
    int end = elementsPerThread - 1;
    for (int i = 1; i < NUM_THREADS; i++) {
        merge(sharedArray, start, start + elementsPerThread - 1, end + elementsPerThread);
        end += elementsPerThread;
    }

    // Uncomment to print the sorted array
    // printf("Sorted array: ");
    // for (int i = 0; i < ARRAY_SIZE; i++) {
    //     printf("%d ", sharedArray[i]);
    // }
    // printf("\n");

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5
#define TIME_QUANTUM 2

pthread_t threads[NUM_THREADS];
int currentThread = 0;

void* threadFunction(void* arg) {
    int threadId = ((int)arg);

    for (int i = 0; i < 5; i++) {
        printf("Thread %d is running for time slice %d\n", threadId, i + 1);
        sleep(TIME_QUANTUM);
    }

    printf("Thread %d finished execution\n", threadId);

    pthread_exit(NULL);
}

int main() {
    int threadIds[NUM_THREADS];

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        threadIds[i] = i;
        pthread_create(&threads[i], NULL, threadFunction, (void*)&threadIds[i]);
    }

    // Simulate round-robin scheduling
    for (int i = 0; i < NUM_THREADS * 5; i++) {
        pthread_join(threads[currentThread], NULL);

        // Move to the next thread in a round-robin fashion
        currentThread = (currentThread + 1) % NUM_THREADS;
    }

    return 0;
}