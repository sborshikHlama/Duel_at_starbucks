#include <stdio.h>
#include <stdlib.h>

// When we use just rand, it uses 

int main() {
    // No srand() here
    printf("Random number 1: %d\n", rand());
    printf("Random number 2: %d\n", rand());
    printf("Random number 3: %d\n", rand());
    return 0;
}
