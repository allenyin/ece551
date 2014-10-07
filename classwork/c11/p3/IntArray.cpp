#include "IntArray.h"
#include <assert.h>
#include <ostream>

IntArray::IntArray() {
    numElements = 0;
    data = NULL;
}

IntArray::IntArray(int n) {
    numElements = n;
    data = new int[numElements];
}

IntArray::IntArray(const IntArray & rhs)  {
    numElements = rhs.numElements;
    data = new int[numElements];
    for (int i=0; i<numElements; i++) {
        data[i] = rhs.data[i];
    }
}

IntArray::~IntArray() {
    delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
    assert(this != &rhs);
    delete[] data;
    numElements = rhs.numElements;
    data = new int[numElements];
    for (int i=0; i<numElements; i++) {
        data[i] = rhs.data[i];
    }
    return *this;
}

const int & IntArray::operator[](int index) const {
    assert(index>=0 && index<numElements);
    return data[index];
}

int & IntArray::operator[](int index) {
    assert(index>=0 && index<numElements);
    return data[index];
}

int IntArray::size() const {
    return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
    if (numElements != rhs.numElements) {
        return false;
    }
    for (int i=0; i<numElements; i++) {
        if (data[i] != rhs.data[i]) {
            return false;
        }
    }
    return true;
}

bool IntArray::operator!=(const IntArray & rhs) const {
    return !((*this) == rhs);
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
    s<<"{";
    for (int i=0; i<rhs.size(); i++) {
        if (i < rhs.size()-1) {
            s << rhs[i]<<", ";
        } else {
            s << rhs[i];
        }
    }
    s<<"}";
    return s;
}
