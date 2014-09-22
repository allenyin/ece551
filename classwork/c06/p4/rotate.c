#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void make_matrix(FILE * f, char matrix[][10]) {
    int c;
    int row = 0;
    int col = 0;
    while ((c = fgetc(f)) != EOF) {
        if (c != '\n') {
            matrix[row][col] = c;
            col++;
        }
        else {
            row++;
            col = 0;
        }
    }
}

void swap(char * i, char * j) {
    char t = *i;
    *i = *j;
    *j = t;
}

void transpose(char matrix[][10]) {
    for (int i=0; i<10; i++) {
        for (int j=i; j<10; j++) {
            if (i != j) {
                swap(&matrix[i][j], &matrix[j][i]);
            }
        }
    }
}

void reverse_row(char row[10]) {
    for (int i=0; i<10/2; i++) {
        swap(&row[i], &row[10-i-1]);
    }
}

void do_rotate(char matrix[][10]) {
    transpose(matrix);
    for (int i=0; i<10; i++) {
        reverse_row(matrix[i]);
    }
}

void print_matrix(char matrix[][10]) {
    for (int i=0; i<10; i++) {
        for (int j=0; j<10; j++) {
            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }
}

void rotate(FILE * f) {
   char matrix[10][10];
   make_matrix(f, matrix);
   do_rotate(matrix);
   print_matrix(matrix);
}


int main(int argc, char ** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: breaker inputFileName\n");
        return EXIT_FAILURE;
    }

    FILE * f = fopen(argv[1], "r");
    if (f == NULL) {
        perror("Could not open file!");
        return EXIT_FAILURE;
    }
    rotate(f);
    if (fclose(f) != 0) {
        perror("Failed to close the input file!");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
