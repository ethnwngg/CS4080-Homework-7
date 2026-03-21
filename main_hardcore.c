#include <assert.h>
#include <stdio.h>
#include "memory_hardcore.h"

int main(void) {
    assert(allocator_init(256));
    printf("init ok (256 bytes)\n");

    int* a = (int*)reallocate(NULL, 0, sizeof(int) * 4);
    assert(a != NULL);
    for (int i = 0; i < 4; i++) a[i] = i + 1;
    printf("alloc 4 ints at %p\n", (void*)a);

    int* b = (int*)reallocate(a, sizeof(int) * 4, sizeof(int) * 8);
    assert(b != NULL);
    assert(b[0] == 1 && b[1] == 2 && b[2] == 3 && b[3] == 4);
    printf("Grow to 8 ints at %p (copied old values)\n", (void*)b);

    void* freed = reallocate(b, sizeof(int) * 8, 0);
    assert(freed == NULL);
    printf("Free request NULL\n");

    void* tooBig = reallocate(NULL, 0, 1000);
    assert(tooBig == NULL);
    printf("Oversized alloc returned NULL\n");

    free_allocator();
    printf("Allocator demo passed\n");
    return 0;
}