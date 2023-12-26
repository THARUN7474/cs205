#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

/*#include <sys/mman.h>.............format to use

void *mmap(void *addr, size_t length, int prot, int flags,
           int fd, off_t offset);
int munmap(void *addr, size_t length); */

#define FIXED_CHUNK_SIZE 1024  // Fixed c_piece_block(chunk) size in bytes
#define NUM_FIXED_CHUNKS 10    // Number of fixed-size chunks

typedef struct FixedChunk {
    struct FixedChunk* next;
} FixedChunk;

FixedChunk* free_list_fixed = NULL;//like array link
void* memory_pool_fixed = NULL;//starting pointer

// Initialize the memory pool for fixed-size chunks
void init_memory_pool_fixed() {
    size_t pool_size = FIXED_CHUNK_SIZE * NUM_FIXED_CHUNKS;
    memory_pool_fixed = mmap(NULL, pool_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if (memory_pool_fixed == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Initialize the free list with all fixed-size chunks
    for (int i = 0; i < NUM_FIXED_CHUNKS; i++) {
        FixedChunk* c_piece_block = (FixedChunk*)((char*)memory_pool_fixed + i * FIXED_CHUNK_SIZE);
        c_piece_block->next = free_list_fixed;
        free_list_fixed = c_piece_block;//its like merging and joining
    }
}//upto here just creating space to allocate(for using)

// Allocate a fixed-size c_piece_block
void* allocate_fixed_chunk() {
    if (free_list_fixed == NULL) {
        printf("Out of memory for fixed-size chunks!\n");
        return NULL;
    }

    FixedChunk* c_piece_block = free_list_fixed;
    free_list_fixed = free_list_fixed->next;
    return c_piece_block;
}

// Free a fixed-size c_piece_block
void free_fixed_chunk(void* ptr) {
    FixedChunk* c_piece_block = (FixedChunk*)ptr;
    c_piece_block->next = free_list_fixed;
    free_list_fixed = c_piece_block;
}

// Clean up and release the memory pool for fixed-size chunks
void cleanup_memory_pool_fixed() {
    munmap(memory_pool_fixed, FIXED_CHUNK_SIZE * NUM_FIXED_CHUNKS);
}

int main() {
    init_memory_pool_fixed();

    // Allocate and free fixed-size chunks
    void* fixed_chunk1 = allocate_fixed_chunk();
    void* fixed_chunk2 = allocate_fixed_chunk();

    printf("Allocated fixed-size chunks: %p, %p\n", fixed_chunk1, fixed_chunk2);

    free_fixed_chunk(fixed_chunk1);
    free_fixed_chunk(fixed_chunk2);

    // Cleanup memory pool for fixed-size chunks
    cleanup_memory_pool_fixed();

    // Now, let's demonstrate dynamic memory allocation
    int* dynamic_chunk1 = (int*)malloc(sizeof(int));
    int* dynamic_chunk2 = (int*)malloc(sizeof(int));

    *dynamic_chunk1 = 42;
    *dynamic_chunk2 = 100;

    printf("Allocated dynamic-size chunks: %p (%d), %p (%d)\n", dynamic_chunk1, *dynamic_chunk1, dynamic_chunk2, *dynamic_chunk2);

    free(dynamic_chunk1);
    free(dynamic_chunk2);

    return 0;
}