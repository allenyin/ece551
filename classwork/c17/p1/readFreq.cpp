#include <stdio.h>
#include <cstdlib>
#include "readFreq.h"
#include <iostream>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256 ) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
    // create an array of 257 entries
    uint64_t *ans = new uint64_t[257];
    for (unsigned i=0; i<257; i++) {
        ans[i] = 0;
    }

    // open file
    std::ifstream fs(fname);

    // get characters
    while (fs.good()) {
        unsigned char c = fs.get();  // get character from file
        if (fs.good()) {
           ans[static_cast<int>(c)] += 1;
        }
    }
   // add the EOF character in the end
   ans[256] = 1; 

    // end of file
    fs.close();
    return ans;
}
