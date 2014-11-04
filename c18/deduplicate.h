// c library
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <dirent.h>
// c++ library
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
// hashing functions
#include "hash-library/md5.h"
#include "hash-library/sha256.h"
// unordered hash-map
#include <unordered-map>

const std::string getHash(std::string fname);

typedef std::unordered_map<std::string, std::string> filemap;
// methods for operating on my hashmap
void add_to_map(filemap map, std::string fname) {
    std::string hash_string = getHash(fname);
    filemap[hash_string] = fname;
}

bool is_duplicate(filemap map, std::string fname) {
    std::string hash_string = getHash(fname);
    if (map.find(hash_string) == map.end()) {
        // hash not in map, not duplicate
        return false;
    }
    else {
        // otherwise hash in map, compare actual filenames
        return map[hash_string] == fname;
    }
}

void generate_shell_script
