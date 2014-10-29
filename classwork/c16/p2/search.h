#pragma once
#include "function.h"
#include <exception>

class ZeroNotFoundException: public std::exception {
    virtual const char* what() const throw() {
        return "Zero Not Found: Check function monotonicity.";
    }
};

int binarySearchForZero(Function<int, int> *f, int low, int high);

