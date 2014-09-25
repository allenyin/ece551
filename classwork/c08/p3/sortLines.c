#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}

/* This function will sort and print data (whose length is count).
   data: array of strings.
   count: length of array - how many strings it contains
*/
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

char ** read_from_stream(FILE * f, int *nlines) {
    char **data = NULL;
    char *line = NULL;
    size_t sz;
    while (getline(&line, &sz, f) >= 0) {
        (*nlines)++;
        data = (char **) realloc(data, (*nlines)*sizeof(*data));
        // need extra byte for '/0'
        data[*nlines-1] = malloc(strlen(line)+sizeof(line[0]));
        strcpy(data[*nlines-1], line);
    }
    if (line != NULL) {
        free(line);
        line = NULL;
    }
    return data;
}

void print_and_free(char **data, int nlines) {
    if (data != NULL) {
        for (int i=0; i<nlines; i++) {
            printf("%s", data[i]);
            free(data[i]);
            data[i] = NULL;
        }
        free(data);
        data = NULL;
    }
}

int main(int argc, char ** argv) {
    /* prgram behavior:
     * argc == 1:
     *  - read lines from input until EOF,
     *  - sort lines and print results
     *  - free memory and exit
     * argc > 1:
     *  - repeat for all the files:
     *      - read lines from input
     *      - sort lines and print results
     *      - free memory
     *  - indicate success and exit.
     */
    if (argc == 1) {
        // read from stdin
        int nlines = 0;
        char **data = read_from_stream(stdin, &nlines);
        sortData(data, nlines);
        print_and_free(data, nlines);
    } 
    else if (argc > 1) {
        // read all the files
        for (int i=1; i < argc; i++) {
            FILE * f = fopen(argv[i], "r");
            if (f == NULL) {
                perror("Could not open file!");
                return EXIT_FAILURE;
            }
            int nlines = 0;
            char **data = read_from_stream(f, &nlines);
            sortData(data, nlines);
            print_and_free(data, nlines);
        }
        printf("Finished sorting all files.\n");
    }
  return EXIT_SUCCESS;
}
