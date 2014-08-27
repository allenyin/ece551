#include <stdio.h>
#include <stdlib.h>

int fib (int n) {
    // assuming we are not doing
    if (n<=0) {
        return 0;
    }
    else if (n==1) {
        return 1;
    }
    else {
        return fib(n-1)+fib(n-2);
    }
}

int main(void) {
    for (int n=-2; n<=30; n++){
       printf("fib(%d) = %d\n",n,fib(n)); 
    }
    return EXIT_SUCCESS;
}
    
