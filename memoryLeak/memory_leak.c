#include <stdio.h>
#include <stdlib.h>

void memoryLeakFunction() {
    int* ptr;
    for (int i = 0; i < 5; i++) {
        ptr = (int*) malloc(sizeof(int)); 
        if (ptr == NULL) {
            printf("Memory allocation failed\n");
            return;
        }
        *ptr = i;
        printf("Value at ptr: %d\n", *ptr);
        printf("%p\n",&ptr);
    }
}

int main() {
    memoryLeakFunction();
    printf("Program finished. Memory has been leaked.\n");
    return 0;
}