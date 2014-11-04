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
#include <map>

const std::string getHash(std::string fname);

typedef std::map<std::string, std::string> filemap;
// methods to operate on filemap.
void add_to_map(filemap * map, std::string fname);
std::string is_duplicate(filemap * map, std::string fname);
void write_to_script(std::string fname_in_map, std::string fname, std::ofstream & ofs);

