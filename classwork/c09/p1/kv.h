#ifndef __KV_H__
#define __KV_H__


struct _kvpair_t { 
    char * key;
    char * value;

};
typedef struct _kvpair_t kvpair_t;

struct _kvarray_t { 
    int num_entries;
    // pairs is an array of POINTERS to kvpair_t.
    kvpair_t ** pairs;
};
typedef struct _kvarray_t kvarray_t;

kvpair_t * make_pair(char * line);

kvarray_t * readKVs(const char * fname);

void freeKVs(kvarray_t * pairs);

void printKVs(kvarray_t * pairs);

char * lookupValue(kvarray_t * pairs, const char * key);

#endif
