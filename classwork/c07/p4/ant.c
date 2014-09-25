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
    if (n == 1) {
        start.x = start.x + (-1)*directions->x;
        start.y = start.y + (-1)*directions->y;
        printf("Go to (%ld,%ld)\n", start.x, start.y);
        return start;
    }
    else {
        point_t new_start = follow(start, directions+1, n-1);
        new_start.x = new_start.x + (-1)*directions->x;
        new_start.y = new_start.y + (-1)*directions->y;
        printf("Go to (%ld,%ld)\n", new_start.x, new_start.y);
        return new_start;
    }
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
    // n is initialized to be 0,
    // v is initialized to be NULL.
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *line2 = NULL;
    char *line3 = NULL;
    while ((read = getline(&line, &len, f)) != -1) {
        long x = strtol(line, &line2, 10);
        if ((line2 == line) || (*line2 == '\0') || (*line2 != ',')) {
            fprintf(stderr, "Invalid input line!\n");
            return NULL;
        }
        long y = strtol(line2+1, &line3, 10);
        if ((line3 == line2+1) || (*line3 != '\n')) {
            fprintf(stderr, "Invalid input line!\n");
            return NULL;
        }
        //printf("(%ld,%ld)\n",x,y);
        // initialize this new vector, and increment number of total vectors
        (*n)++;
        v = (vector_t *) realloc(v, (*n)*sizeof(*v));
        v[(*n)-1].x = x;
        v[(*n)-1].y = y;
    }
    if (line != NULL) {
        free(line);
        line = NULL;
        line2 = NULL;
        line3 = NULL;
    }
    return v;
}

int main(int argc, char ** argv) {
    if (argc == 1) {
        fprintf(stderr, "No file name entered!\n");
        return EXIT_FAILURE;
    }
    else if (argc == 2) {
        FILE *f = fopen(argv[1], "r");
        if (f == NULL) {
            fprintf(stderr, "Could not open file!\n");
            return EXIT_FAILURE;
        }
        vector_t * all_vecs = NULL;
        int num_vecs = 0;
        all_vecs = readVector(f, all_vecs, &num_vecs);
        if (all_vecs == NULL) {
            fprintf(stderr, "Error reading vector files!\n");
            return EXIT_FAILURE;
        }
        point_t start = {0,0};
        start = follow(start, all_vecs, num_vecs);
        printf("Food at (%ld,%ld)\n", start.x, start.y);
        // free memory
        free(all_vecs);
        all_vecs = NULL;
        
        if (fclose(f) != 0) {
            perror("Failed to close the input file!");
            return EXIT_FAILURE;
        }
    } 
    return EXIT_SUCCESS;
}
