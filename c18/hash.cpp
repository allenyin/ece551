#include "deduplicate.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: hash filename\n");
        return EXIT_FAILURE;
    }
    // make a SHA256 hash of a file
    //SHA256 sha256;
    MD5 digestMd5;
    std::ifstream file;
    file.open(argv[1]);
    const size_t BufferSize = 144*7*1024;
    char* buffer = new char[BufferSize];

    if (file != NULL) {
        file.read(buffer, BufferSize);
        std::size_t numBytesRead = size_t(file.gcount());
        digestMd5.add(buffer, numBytesRead);
    }
    file.close();
    delete[] buffer;

    //show results
    std::cout << "MD5: " << digestMd5.getHash() << std::endl;
    return EXIT_SUCCESS;
}

