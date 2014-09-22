#include <stdio.h>
#include <stdlib.h>

struct _point_t {
  long x;
  long y;
};

typedef struct _point_t point_t;
typedef point_t vector_t;

//start: the point to start from
//directions: the (backwards) directions (as an array)
//n: how many directions are in the array directions
point_t follow(point_t start, vector_t * directions, int n) {
}

//given a line (e.g. ("3,4") convert it to a vector_t
vector_t lineToPoint(const char * line) {

}

//given a FILE *f, read all the lines.
//v is the memory allocated to hold all the previous lines
// (as an array of vector_t)s
//n points at an int, which says how many items are already in v.
//that is *n is the length of v.
// this function will update *n whenever it reads more items,
// so that when it returns to its original caller, the int
// whose address was passed in will indicate the lenght of the
// returned array
vector_t * readVector(FILE * f, vector_t * v, int * n) {

}

int main(int argc, char ** argv) {

}
