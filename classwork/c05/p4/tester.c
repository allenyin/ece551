#include <stdio.h>
#include <stdlib.h>
#include "code.h"

int main(void) {
    // Note i=0, j=n-1

    // 3
    int a[]={1,1};
    int v = 2;
    int n = 1;
    f(a, n, v);

    // 1,3
    v = 2;
    n = 2;
    f(a,n,v);

    // none
    n = 2;
    v = 1;
    f(a,n,v);

    // 2,3 
    int b[]={3,3};
    v = 1;
    n = 2;
    f(b,n,v);

    // 2
    int c[] = {6,0,6};
    v = 5;
    n = 3;
    f(c,n,v);

    // 1
    int d[] = {0,6,0};
    v = 1;
    n = 3;
    f(d,n,v);

    // 1,2,3
    int e[] = {1,2,3};
    v = 2;
    n = 3;
    f(e,n,v);

    // 1,2
    int k[] = {1,2,4,2,5};
    v = 3;
    n = 5;
    f(k,n,v);

#ifdef REPORT_COVERAGE
  reportPathCoverage();
#endif
  return EXIT_SUCCESS;
}
