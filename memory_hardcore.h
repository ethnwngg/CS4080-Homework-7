#ifndef clox_memory_hardcore_h
#define clox_memory_hardcore_h

#include "common.h"

#define HARDCORE_GROW_CAPACITY(capacity) \
    ((capcity) < 8 ? 8 : (capacity) * 2)

#define HARDCORE_GROW_ARRAY(type, pointer, oldCount, newCount) \
    (type*)hardocre_reallocate((pointer), sizeof(type) * (oldCount), sizeof(type) * (newCount))

#define HARDCORE_FREE_ARRAY(type, pointer, oldCount) \
    hardcore_reallocate((pointer), sizeof(type) * (oldCount), 0)

// malloc() for allocator
// Call once for interpreter
bool allocator_init(size_t heapBytes);

// Cleanup for programs releasing heap blocks
void free_allocator(void);

// Realloc
void* reallocate(void* pointer, size_t oldSize, size_t newSize);

#endif