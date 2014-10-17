#include <stdio.h>
#include <stdlib.h>



int * initArray(int * array, int n){
  for (int i = 0; i < n; i++){
    array[i] = i;
  }
  return array;                     
}

int * aFunction(int n) {
  int myArray[n];
  
  int * ptr = initArray(myArray, n-1);  
  int total = 0;
  for (int i = 0; i <= n; i++) {
    printf("%d\n", myArray[i]);         // 19: use of uninitialized value, when i=7
    total += ptr[i];                    // 19: index out of bounds, when i=8
  }
  printf("Total = %d\n", total);
  return myArray;                       // 23: return dangling pointer
}

int main (void) {
  int * ptr = aFunction(8);             
  printf("%d\n", ptr[0]);               // 28: use of dangling pointer 
  return EXIT_SUCCESS;
}
