#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
void count_freq(FILE * f, int * freq_table) {
    int c;
    while ((c = fgetc(f)) != EOF) {
        if (isalpha(c)) {
            freq_table[tolower(c)-'a']++;
        }
    }
}

int find_max(int * freq_table, int array_size) {
    int k = 0;
    int max = freq_table[k];
    for (int i=0; i<array_size; i++) {
        if (freq_table[i] > max) {
            max = freq_table[i];
            k = i;
        }
    }
    return k;
}

int solve_key(int idx_e) {
    return ((idx_e-4)+26)%26;
}

void breaker(FILE * f) {
    int freq_table[26] = {0};   // initialize all freq to 0
    count_freq(f, freq_table);
    int idx_e = find_max(freq_table, 26);
    int key = solve_key(idx_e);
    fprintf(stdout, "%d\n", key);
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
    breaker(f);
    if (fclose(f) != 0) {
        perror("Failed to close the input file!");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
