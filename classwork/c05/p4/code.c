#include "code.h"

void f(int * a, int n, int v) {
  int i =-1;
  int j = n; 
  int tmp;
  do {
    i = i+1;
  } while( a[i] < v && i < n-1);
  do{
    j = j-1;
  } while( a[j] > v && j > 0);
  if( i >= j ) {
    tmp = a[i]; 
    a[i] = a[j]; 
    a[j] = tmp;
  }
}


