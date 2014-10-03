#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
    counts_t * my_counts = malloc(sizeof(*my_counts));
    my_counts->num_counts = 0;
    my_counts->count_entries = NULL;
    return my_counts;
}

void addCount(counts_t * c, const char * name) {
    // traverse the entries in c to find one that matches name
    for (int i=0; i<c->num_counts; i++) {
        if ((name==NULL) && \
           (strcmp(c->count_entries[i]->value, "<unknown>")==0)) {
            c->count_entries[i]->counts++;
            return;
        } else if ((name!=NULL) && \
                   (strcmp(name, c->count_entries[i]->value)==0)) {
            c->count_entries[i]->counts++;
            return;
        }
    }
    // if not found in list, create a new one_count_t entry
    c->num_counts++;
    c->count_entries = realloc(c->count_entries, c->num_counts*sizeof(*(c->count_entries)));
    // initialize new one_count_t
    c->count_entries[c->num_counts-1] = malloc(sizeof(*(c->count_entries[c->num_counts-1])));
    if (name == NULL) {
        c->count_entries[c->num_counts-1]->value = malloc(sizeof(*name)*10);
        strcpy(c->count_entries[c->num_counts-1]->value, "<unknown>");
    }
    else {
        c->count_entries[c->num_counts-1]->value = malloc((sizeof(*name))*(strlen(name)+1));
        strcpy(c->count_entries[c->num_counts-1]->value, name);
    }
    c->count_entries[c->num_counts-1]->counts = 1;
    return;
}

void printCounts(counts_t * c, FILE * outFile) {
    one_count_t *unknown_entry = NULL;
    for (int i=0; i<c->num_counts; i++) {
        if (strcmp(c->count_entries[i]->value, "<unknown>")==0) {
            unknown_entry = c->count_entries[i];
        } else {
            fprintf(outFile, "%s: %d\n", \
                    c->count_entries[i]->value,
                    c->count_entries[i]->counts);
        }
    }
    if (unknown_entry != NULL) {
        // now print out unknown entry
        fprintf(outFile, "%s: %d\n", \
                unknown_entry->value,
                unknown_entry->counts);
    }

    if (fclose(outFile) != 0) {
        perror("Failed to close the input file!");
    }

}

void freeCounts(counts_t * c) {
    for (int i=0; i<c->num_counts; i++) {
        free(c->count_entries[i]->value);
        free(c->count_entries[i]);
    }
    free(c->count_entries);
    free(c);
}
