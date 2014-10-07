#include "IntMatrix.h"

IntMatrix::IntMatrix(){
    numRows = 0;
    numColumns = 0;
}

IntMatrix::IntMatrix(int r, int c) {
    numRows = r;
    numColumns = c;
    rows = new IntArray*[r];
    for (int i=0; i<numRows; i++) {
        rows[i] = new IntArray(c);
    }
}

IntMatrix::IntMatrix(const IntMatrix & rhs)  {
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    rows = new IntArray*[numRows];
    for (int i=0; i<numRows; i++) {
        rows[i] = new IntArray(*rhs.rows[i]);
    }
}

IntMatrix::~IntMatrix() {
    if (numRows != 0) {
        for (int i=0; i<numRows; i++) {
            delete rows[i];
        }
        delete[] rows;
    }
}

IntMatrix &IntMatrix::operator=(const IntMatrix & rhs) {
    assert(this != &rhs);
    if (numRows != 0) {
        for (int i=0; i<numRows; i++) {
            delete rows[i];
        }
        delete[] rows;
    }
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    rows = new IntArray*[numRows];
    for (int i=0; i<numRows; i++) {
        rows[i] = new IntArray(*rhs.rows[i]);
    }
    return *this;
}

int IntMatrix::getRows() const {
    return numRows;
}

int IntMatrix::getColumns() const {
    return numColumns;
}

const IntArray & IntMatrix::operator[](int index) const {
    assert(index>=0 && index<numRows);
    return *(rows[index]);
}

IntArray & IntMatrix::operator[](int index){
    assert(index>=0 && index<numRows);
    return *(rows[index]);
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
    if ( (numRows != rhs.numRows) || (numColumns != rhs.numColumns)) {
        return false;
    }
    for (int i=0; i<numRows; i++) {
        if (*(rows[i]) != rhs[i]) {
            return false;
        }
    }
    return true;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
    assert( (numRows == rhs.numRows) && (numColumns == rhs.numColumns));
    for(int i=0; i<numRows; i++) {
        for(int j=0; j<numColumns; j++) {
            (*(rows[i]))[j] += rhs[i][j];
        }
    }
    return *this;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
    s<<"[ ";
    for (int i=0; i<rhs.getRows(); i++) {
        if (i<rhs.getRows()-1) {
            s << rhs[i] << ",\n";
        } else {
            s << rhs[i];
        }
    }
    s<<" ]";
    return s;
}
