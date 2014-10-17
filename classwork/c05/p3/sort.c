#include <stdio.h>
#include <stdlib.h>
void swap (int* a, int* b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void bubbleSort(int * array, int n) {
  int done = 0;
  while (!done) {
    for (int i = 1; i < n ; i++) {
      if (array[i-1] > array[i]) {
	    swap(&array[i-1], &array[i]);
      }
    }
    n--;
    done = (n==0)?1:0;
  }
}

int main(int argc, char ** argv) {
  int data[argc-1];
  for (int i = 0; i < argc-1; i++) {
    data[i] = atoi(argv[i+1]);
  }
  bubbleSort(data, argc-1);
  for (int i =0; i < argc-1; i++) {
    printf("%d\n", data[i]);
  }
  return EXIT_SUCCESS;
}
