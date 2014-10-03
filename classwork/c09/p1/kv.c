#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

kvpair_t *make_pair(char * line) {
    char *space = strchr(line, '=');    // need to free
    char *newline = strchr(line, '\n'); // need to free
    if (space != NULL) {
        // correct line input, initialize a new pair
        kvpair_t *entry = malloc(sizeof(*entry));
        entry->key = malloc((space-line+1)*sizeof(*(entry->key)));
        // copy the key into the intialized memory
        int i;
        for (i=0; i<(space-line); i++) {
            entry->key[i] = line[i];
        }
        // i=space-line now, put in the terminating char
        entry->key[i] = '\0'; 
        
        // now make the value
        if (newline != NULL) {
            // here line buffer is in the form of [?,?...,?,\n,\0]
            entry->value = malloc((newline-space)*sizeof(*(entry->value)));
            for (i=0; i<newline-space-1; i++) {
                entry->value[i] = *(space+1+i);
            }
            entry->value[i] = '\0';
        }else {
            // here the last character in the buffer is '\0'
            entry->value = malloc((strlen(line)-strlen(entry->key))*sizeof(*(entry->value)));
            for (i=1; i<strlen(line)-strlen(entry->key)+1; i++) {
                entry->value[i] = *(space+i);
            }
        }
        return entry;
    }
    else {
        perror("Incorrect input file type!");
        return NULL;
    }
}

kvarray_t * readKVs(const char * fname) {
    FILE * f = fopen(fname, "r");
    if (f == NULL) {
        perror("Could not open file!");
        return NULL;
    }
    // otherwise start reading file
    kvarray_t *myKV = malloc(sizeof(*myKV));
    myKV->num_entries = 0;
    myKV->pairs= NULL;
    // line will be filled by getline; need to free
    char *line = NULL;
    size_t sz;
    while(getline(&line, &sz, f) >= 0) {
        kvpair_t *new_pair = make_pair(line);
        if (new_pair != NULL) {
            myKV->num_entries++;
            myKV->pairs= realloc(myKV->pairs, myKV->num_entries*sizeof(*(myKV->pairs)));
            myKV->pairs[myKV->num_entries-1] = new_pair;
        }
    }
    free(line);
    if (fclose(f) != 0) {
        perror("Failed to close the input file!");
        return NULL;
    }
    return myKV;
}

void freeKVs(kvarray_t * pairs) {
    for (int i=0; i<pairs->num_entries; i++) {
        // go through each kvarray entry and free each pairing
        free(pairs->pairs[i]->key);
        free(pairs->pairs[i]->value);
        free(pairs->pairs[i]);
    }
    free(pairs->pairs);
    free(pairs);
}

void printKVs(kvarray_t * pairs) {
    for (int i=0; i<pairs->num_entries; i++) {
        printf("key= '%s' value = '%s'\n", \
                pairs->pairs[i]->key, pairs->pairs[i]->value);
    }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
    for (int i=0; i<pairs->num_entries; i++) {
        if (strcmp(key, pairs->pairs[i]->key)==0) {
            return pairs->pairs[i]->value;
        }
    }
    return NULL;
}
