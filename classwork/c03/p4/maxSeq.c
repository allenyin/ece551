#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a>b)?a:b;
}


int maxSeq(int * array, int n) {
    if (n < 1) {
        return 0;
    }
    int seq = 1;
    int * p = array+1;
    while (p < array + n) {
        if (*p <= *(p-1)) {
            return max(seq, maxSeq(p, array+n-p));
        }
        else {
            seq++;
            p++;
        }
    }
    return seq;
}

void doTest(int * array, int n) {
    printf("maxSeq(");
    if (array == NULL) {
        printf("NULL");
    }
    else {
        printf("{");
        for (int i =0; i < n; i++) {
            printf("%d", array[i]);
            if (i < n -1) {
                printf(", ");
            }
        }
        printf("}");
    }
    printf(", %d) is \n", n);
    int ans = maxSeq (array, n);
    printf("%d\n", ans);
}

int main(void) {
    int array1[] = { 1, 2, 3, 2, 4, 6, 9, 11, 13, 13, 15, 1, 2, 3, 2, 1};
    int array2[] = { -100, -99, -98, -97, -96, -95, -94};
    int array3[] = { 1, 1, 2, 3, 5, 8, 13, 8, 5, 4, 1, 2, 3,9};
    int array4[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1};

    doTest (array1, 16);
    doTest (array2, 7);
    doTest (array3, 14);
    doTest (array4, 9);
    doTest (NULL, 0);
    doTest (array1, 0);

    return EXIT_SUCCESS;
}
