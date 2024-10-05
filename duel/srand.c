#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main() {
    srand(time(NULL) * getpid());  // Seed the RNG with the current time
    printf("Random number 1: %d\n", rand() % 1000);
    printf("Random number 2: %d\n", rand());
    printf("Random number 3: %d\n", rand());
    return 0;
}
