#include <stdio.h>
#include <stdlib.h>

/* Prime number definition:
 * A prime number is a natural number, greater than 1 that has no
 * POSITIVE divisor other than 1 and itself.
 *
 * Given this, the appropriate behaviors would be:
 * 1) n<0: return the factors for |n|
 * 2) n=0: nothing. Because 0 is neither a composite or prime number
 * 3) n=1: nothing. 1 has no prime factors.
 * 4) n>1: Return factors between 1 and n, inclusive. Othwerise, none.
 */

int isPrime(int n);

void printFactors(int n) {
    // Do special/corner cases first.
    if (n<0) {
        /* for negative numbers, return the prime factors
         * of the absolute value
         */
        printFactors(-n);
        return;
    }
    else if ((n==0) || (n==1)){
        // 0 is a product of 0 primes
        printf("\n");
        return;
    }
    else {
        /* Algorithm using recursion:
         * Go from i=2 to n-1,
         * 1) check if it's prime, if it is, save it.
         * 2) then do printFactors on the quotient.
         */
        int i;
        for (i=2; i<=n-1; i++){
            if (isPrime(i) && (n%i==0)) {
                printf("%d * ", i);
                break;
            }
        }
        if (isPrime(n/i)) {
            printf("%d\n", n/i);
            return;
        }
        printFactors(n/i);
        return;
    }
}

int isPrime(int n) {
    if (n<=1) {return 0;}
    for (int x=2; x<=n-1; x++) {
        if (n%x==0) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
  //printf("Factorization of 0:\n");
  //printFactors(0);
  printf("Factorization of 1:\n");
  printFactors(1);
  printf("Factorization of 60:\n");
  printFactors(60);
  printf("Factorization of 132:\n");
  printFactors(132);
  printf("Factorization of 11726:\n");
  printFactors(11726);
  printf("Factorization of 2169720:\n");
  printFactors(2169720);
  printf("Factorization of 1789220887:\n");
  printFactors(1789220887);
  //printf("Facotrization of -1789220887:\n");
  //printFactors(-1789220887);
  return EXIT_SUCCESS;
}
