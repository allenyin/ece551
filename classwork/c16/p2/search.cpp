#include "search.h"
#include <assert.h>
#include <exception>
#include <iostream>
#include <cmath>

int binarySearchForZero(Function<int, int> * f, int low, int high) {
    assert(high >= low);
    if (f->invoke(low)<0 && f->invoke(high-1)<0) {
        return high-1;
    }
    if (f->invoke(low)>0 && f->invoke(high-1)>0) {
        return low;
    }
    int mid;
    while (low < high) {
        mid = (low+high)/2;
        int y = f->invoke(mid);
        if (y == 0) {
            return mid;
        }
        if (y<0) {
            int z = f->invoke(mid+1);
            low =  std::abs(z)<std::abs(y) ? mid+1 : mid;
            /*
            if (z>0) {
                return (std::abs(z)<std::abs(y))? mid+1 : mid;
            }
            low = mid+1;*/
        }
        else if (y>0) {
            int x = f->invoke(mid-1);
            high = std::abs(x) < std::abs(y) ? mid-1 : mid;
            /*
            if (x<0) {
                return (std::abs(x)<std::abs(y))? mid-1 : mid;
            }
            high = mid;
            */
        }
    }
    //return mid;
    return low;
}
