#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void read_from_stream(istream &f, vector<string> & data) {
    data.clear();
    string line;
    while (getline(f, line)) {
        data.push_back(line);
    }
} 

void print_data(vector<string> & data) {
    for (unsigned i=0; i<data.size(); i++) {
        cout << data[i] << '\n';
    }
}


int main(int argc, char ** argv) {
    /* Program behavior:
     * argc == 1:
     *  - read lines from input until EOF,
     *  - sort lines and print results
     *  - free memory and exit (call destructors? delete() for each new())
     *  argc > 1:
     *   - repeat for all the files:
     *       - read lines from input
     *       - sort lines and print results
     *       - free memory
     *  - indicate success and exit.
     */
    if (argc == 1) {
        // read from cin, into a vector of string
        vector<string> data;
        read_from_stream(cin, data);
        sort(data.begin(), data.end());
        print_data(data);
    }
    else if (argc > 1) {
        // read all the files
        for (int i=1; i<argc; i++) {
            ifstream f(argv[i]);
            if (!f.good()) {
                perror("Could not open file!");
                return EXIT_FAILURE;
            }
            vector<string> data;
            read_from_stream(f, data);
            sort(data.begin(), data.end());
            print_data(data);
            // close the file
            f.close();
        }
    }
    return EXIT_SUCCESS;
}


