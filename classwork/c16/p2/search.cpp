#include "search.h"
#include <assert.h>
#include <exception>
#include <iostream>
#include <cmath>
#include <stdio.h>

int binarySearchForZero(Function<int, int> *f, int low, int high) {
    /*
    assert(high>=low);
    std::cout << "Invoked times in beginning: " << f->getCount() << std::endl;
    if (f->invoke(low) >= 0) {
        std::cout << "Edge 1\n";
        std::cout << "Invoked times: "<< f->getCount() << std::endl;
        return low;
    }
    if (f->invoke(high-1) <= 0) {
        std::cout << "Edge 2\n";
        std::cout << "Invoked times: "<< f->getCount() << std::endl;
        return high-1;
    }*/
    int mid;
    int y;
    while (high-low > 2) {
        mid = low+(high-1-low)/2;
        y = f->invoke(mid);
        if (y==0)
            return mid;
        if (y<0)
            low = mid+1;
        else
            high = mid;
    }
    
    //printf("low=%d, mid=%d, high=%d\n", low, mid, high);
    //printf("y=%d\n", y);
    int ans = (std::abs(f->invoke(low))<std::abs(f->invoke(low+1))) ? low : low+1;
    //std::cout << "Invoked times: "<< f->getCount() << std::endl;
    return ans;
}

/*
int binarySearchForZero(Function<int, int> *f, int low, int high) {
    int left = low;
    int right = high -1;
    int same;
    bool isLeft;
    while (left <= right) {
        int mid = left+(right-left)/2;
        int y = f->invoke(mid);
        if (left==right) 
            same = y;
        if (y==0) {
            std::cout << "Invoked times: "<< f->getCount() << std::endl;
            return mid;
        }
        if (y<0) {
            left = mid+1;
            isLeft = false;
        }
        else {
            right = mid-1;
            isLeft = true;
        }
    }
    if (left >= high)  {
        std::cout << "Invoked times: "<<f->getCount() << std::endl;
        return high-1;
    }
    if (right < low) {
        std::cout << "Invoked times: "<<f->getCount() << std::endl;
        return low;
    }
    if (isLeft) {
        std::cout << "Invoked times: "<<f->getCount() << std::endl;
        return (std::abs(f->invoke(right))<same)?right:left;
    }
    std::cout << "Invoked times: "<<f->getCount() << std::endl;
    return (same<std::abs(f->invoke(left)))?right:left;
}*/
