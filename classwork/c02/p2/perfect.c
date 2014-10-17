#include <stdio.h>
#include <stdlib.h>

int isPerfect(int x) {
    if (x<=0) {
        return 0;
    }
    // find all of x' divisors first.
    int sum = 0;
    for (int i=1; i<x; i++) {
        if (x%i == 0) {
            sum += i;
        }
    }
    return (sum == x);
}

int main(void) {
    for (int i=1; i<=10000; i++) {
        if (isPerfect(i)) {
            printf("%d is perfect!\n", i);
        }
    }
    return EXIT_SUCCESS;
}
