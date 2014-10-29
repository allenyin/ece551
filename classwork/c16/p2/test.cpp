#include "function.h"
#include "search.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

template <typename T>
class SinFunction : public Function<int, int> {
    public:
        virtual int invoke(int arg) {
            return 10000000 * (sin(arg/100000.0) - 0.5);
        }
};

template <typename T>
class LineFunction : public Function<int, int> {
    public:
        virtual int invoke(int arg) {
            //return arg-2;
            return 6*arg+17;
        }
};

template <typename T>
class SimpleFunction : public Function<int, int> {
    public:
        virtual int invoke(int arg) {
            return 2*arg-3;
        }
};

// test file for binarySearchForZero
int main(void) {
    SinFunction<int> *sf = new SinFunction<int>();
    int x_value = binarySearchForZero(sf, 0, 150000);
    std::cout << "0 for SinFunction in [0,150000) is " << x_value << std::endl;

    LineFunction<int> *lf = new LineFunction<int>();
    x_value = binarySearchForZero(lf, -10, 9);
    std::cout << "0 for lineFunction in [-10,10) is " << x_value << std::endl;

    SimpleFunction<int> *spf = new SimpleFunction<int>();
    x_value = binarySearchForZero(spf, 1, 2);
    std::cout << "0 for simpleFunction in [1, 2) is " << x_value << std::endl;

    delete sf;
    delete lf;
    delete spf;
    return EXIT_SUCCESS;

}

