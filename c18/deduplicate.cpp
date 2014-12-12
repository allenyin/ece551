#include "deduplicate.h"
#include <cstdlib>
#include <stdio.h>

void getdir(std::string dir, filemap * my_map, std::ofstream & ofs) {
    // directory pointer
    DIR *dp;    
    // dir entry pointer
    struct dirent *entry;   
    // file stat struct
    struct stat fileInfo;

    dp = opendir(dir.c_str());
    if(dir.at(dir.length()-1) != '/') {
        dir=dir+"/";
    }
    if (dp!=NULL) {
        while((entry = readdir(dp))) {
            if(strcmp(entry->d_name, ".") != 0 &&
                    strcmp(entry->d_name, "..") != 0) {
                // use lstat because stat follows the link
                if(lstat((dir+entry->d_name).c_str(), &fileInfo) != -1) {
                    if(S_ISDIR(fileInfo.st_mode)) {
                        // entry is directory, recurse into it
                        getdir(dir+entry->d_name, my_map, ofs);
                    }
                    else if(S_ISREG(fileInfo.st_mode)) {
                        // entry is regular file,
                        // add to my_map if not duplicate
                        std::string fname_in_map = is_duplicate(my_map, dir+entry->d_name);
                        if (fname_in_map != "") {
                            write_to_script(fname_in_map, dir+entry->d_name, ofs);
                        }
                        else {
                            add_to_map(my_map, dir+entry->d_name);
                        }
                    }
                }
                else {
                    perror("Cannot get file info!");
                }
            }
        }
        closedir(dp);   // close directory
    }
    else {
        perror("Couldn't open the directory!");
    }
}

bool isSameFile(std::string fname1, std::string fname2) {
    struct stat fileInfo1;
    struct stat fileInfo2;
    if (lstat(fname1.c_str(), &fileInfo1) != -1 && lstat(fname2.c_str(), &fileInfo2) != -1) {
        // compare the inode
        return (fileInfo1.st_ino == fileInfo2.st_ino);
    }
    else {
        return false;
    }
}

const std::string getHash(std::string fname) {
    // Make SHA256 Hash of the file given by fname.
    std::ifstream fs;
    fs.open(fname.c_str());
    SHA256 digestSHA256;
    // Buffer about 1MBytes, divisible by 144 increases SHA3 performance
    const size_t BufferSize = 144*7*1024;
    char* buffer = new char[BufferSize];
    if (fs != NULL) {
        fs.read(buffer, BufferSize);
        std::size_t numBytesRead = size_t(fs.gcount());
        digestSHA256.add(buffer, numBytesRead);
    }
    fs.close();
    delete[] buffer;
    return digestSHA256.getHash();
}

// methods for operating on my hashmap
void add_to_map(filemap * map, std::string fname) {
    std::string hash_string = getHash(fname);
    (*map)[hash_string] = fname;
}


std::string is_duplicate(filemap * map, std::string fname) {
    // if fname is a duplicate of something already inside map
    // return that item inside the map.
    // otherwise, return NULL.
    std::string hash_string = getHash(fname);
    if (map->find(hash_string) == map->end()) {
        // hash not in map, not duplicate
        return "";
    }
    else {
        // otherwise hash in map
        if (!isSameFile((*map)[hash_string], fname)) {
            return (*map)[hash_string];
        }
        //std::cout << "Comparing against self!\n";
        return "";
    }
}

void write_to_script(std::string fname_in_map, std::string fname, std::ofstream & ofs) {
    // file indicated by fname is a duplicate of an entry already in map
    // write to ofs the appropriate shell commands to remove it.

    ofs << "#Removing " << fname << " (duplicate of " << fname_in_map << ")\n";
    ofs << "rm " << fname << std::endl;
}

int main(int argc, char* argv[]) {
    // Open the folder indicated by command line arguments (1 or more)
    // Find all regular files (recursively) contained within those directories.
    // Make HASH and put these files into a HASHTABLE.
    // Go through HASHTABLE and output script file.
    if (argc < 2) {
        fprintf(stderr, "Usage: deduplicate dir\n");
        return EXIT_FAILURE;
    }
    else {
        std::ofstream ofs("deduplicate.sh", std::ofstream::out);
        ofs << "#!/bin/bash" << std::endl;
        // vector to hold all the files from all the directiories.
        filemap * my_map = new filemap();
        for (int i=1; i<argc; i++) {
            std::string dir = argv[i];
            getdir(dir, my_map, ofs);
        }
        ofs.close();
        delete my_map;
        std::cout << "Finished generating shell script\n";
    }

    return EXIT_SUCCESS;
}
