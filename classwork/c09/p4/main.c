#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  counts_t * c = createCounts();
  FILE * f = fopen(filename,"r");
  char * line = NULL;
  size_t sz = 0;
  while(getline(&line, &sz, f) >= 0) {
    char * ptr = strchr(line, '\n');
    if (ptr != NULL) {
      *ptr = '\0';
    }
    char * value = lookupValue(kvPairs, line);
    addCount(c, value);
  }
  fclose(f);
  free(line);
  return c;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
 //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kvs = readKVs(argv[1]);
 //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kvs);
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);

    //open the file named by outName (call that f)
    FILE * f = fopen(outName,"w");
    //print the counts from c into the FILE f
    printCounts(c,f);
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }
 //free the memory for kv
  freeKVs(kvs);
  return EXIT_SUCCESS;
}
