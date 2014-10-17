#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

template<typename T>
class Matrix {
    private:
        int numRows;
        int numColumns;
        vector< vector<T> > rows;
    public:
        Matrix() {
            numRows = 0;
            numColumns = 0;
        }
        
        Matrix(int r, int c) {
            numRows = r;
            numColumns = c;
            rows.reserve(numRows);
            for (int i=0; i<numRows; i++) {
                rows.push_back(vector<T>(numColumns));
            }
        }
        
        Matrix(const Matrix & rhs) {
            numRows = rhs.numRows;
            numColumns = rhs.numColumns;
            rows = rhs.rows;
        }
        
        ~Matrix() {
            if (numRows !=0) {
                vector< vector<T> >().swap(rows);
            }
        }
            
        Matrix<T> & operator=(const Matrix<T> & rhs) {
            assert(this != &rhs);
            numRows = rhs.numRows;
            numColumns = rhs.numColumns;
            rows = rhs.rows;
            return *this;
        }

        int getRows() const {
            return numRows;
        }

        int getColumns() const {
            return numColumns;
        }

        const vector<T> & operator[](int index) const {
            assert(index>=0 && index<numRows);
            // don't need to do *(rows[index]), b/c rows[index] returns reference.
            return (rows[index]);
        }

        vector<T> & operator[](int index) {
            assert(index>=0 && index<numRows);
            return (rows[index]);
        }

        bool operator==(const Matrix<T> & rhs) const {
            // can I just do v1 == v2?
            if ( (numRows != rhs.numRows) || (numColumns != rhs.numColumns)) {
                return false;
            }
            for (int i=0; i<numRows; i++) {
                if (rows[i] != rhs[i]) {
                    return false;
                }
            }
            return true;
        }

        Matrix<T> operator+(const Matrix<T> & rhs) const {
            // Here T should be int, double, float for both.
            assert( (numRows == rhs.numRows) && (numColumns == rhs.numColumns));
            Matrix<T> m(numRows, numColumns);
            for (int i=0; i<numRows; i++) {
                for (int j=0; j<numColumns; j++) {
                    m[i][j] = rows[i][j]+rhs.rows[i][j];
                }
            }
            return Matrix<T>(m);
        }

        /*
        Matrix<string> operator+(const Matrix<string> & rhs) const {
            assert( (numRows == rhs.numRows) && (numColumns == rhs.numColumns));
            Matrix<string> m(numRows, numColumns);
            for (int i=0; i<numRows; i++) {
                for (int j=0; j<numColumns; j++) {
                    string s;
                    for (int k=0; k<rows[i][j].length(); k++) {
                        s << (char)((int)rows[i][j][k] + (int)rhs.rows[i][j][k]);
                    }
                    m[i][j] = s;
                }
            }
            return Matrix<string>(m);
        }*/



};


template<typename T>
ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
    s<<"[ ";
    for (int i=0; i<rhs.getRows(); i++) {
        s << "{";
        for (int j=0; j<rhs.getColumns(); j++) {
            if (j<rhs.getColumns()-1) {
                s << rhs[i][j] <<",";
            } else {
                s << rhs[i][j];
            }
        }
        if (i<rhs.getRows()-1) {
            s << "},\n";
        } else {
            s << "}";
        }
    }
    s<<" ]";
    return s;
}

#endif
