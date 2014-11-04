#include "deduplicate.h"
#include <cstdlib>
#include <stdio.h>

void getdir(std::string dir, std::vector<std::string> &files) {
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
                        getdir(dir+entry->d_name, files);
                        files.push_back(dir+entry->d_name); 
                    }
                    else if(S_ISREG(fileInfo.st_mode)) {
                        // add if it's regular file
                        files.push_back(dir+entry->d_name);
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
        // vector to hold all the files from all the directiories.
        std::vector<std::string> files = std::vector<std::string>();
        for (int i=1; i<argc; i++) {
            std::string dir = argv[i];
            getdir(dir,files);
            for(unsigned j=0; j<files.size(); j++) {
                std::cout << files[j] << ": " << getHash(files[j]) << "    SHA256\n";
            }
        }
    }

    return EXIT_SUCCESS;
}
