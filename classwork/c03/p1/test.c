#include <stdio.h>
#include <stdlib.h>

void printArray(int * myArray) {
    for (int i=0; i<4; i++) {
        printf("myArray[%d] = %d\n",i,myArray[i]);
    }
    printf("--------------\n");
}


int main(void) {
  int anArray[] = {5,16,33,99};
  int * p = anArray;
  printf("*p = %d\n", *p);
  p++;
  printf("Now *p = %d\n", *p);
  int * q = &anArray[3];     
  int ** x = &q;            
  **x = 12;                
  *x = p;                 
  **x = 42;              
  q[1] = 9;    
  for (int i =0; i < 4; i++){
    printf("anArray[%d] = %d\n",i, anArray[i]);
  }
  return EXIT_SUCCESS;
}
