#include "ll.h"
#include "function.h"
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <iostream>
#include <sstream>

// function to test filter
template<typename T>
class IsEven : public Function<bool, const T&> {
    // no need for constructors because no data
    public:
        virtual bool invoke(const T& arg) {
            return arg%2==0;
        }
};

// function to test split
template<typename T>
class Mod3 : public Function<unsigned, const T&> {
    // no need for constructors because no data
    public:
        virtual unsigned invoke(const T& arg) {
            return arg%3;
        }
};

// function to test foldl
template<typename T>
class Sum : public Function<T, std::pair<const T&, const T&> > {
    // no need for constructors because no data
    public:
        virtual T invoke(std::pair<const T&, const T&> p) {
            return (p.first + p.second);
        }
};

template<typename T>
void printList(LinkedList<T> * ll) {
    typename LinkedList<T>::iterator iter = ll->begin();
    while(iter != ll->end()) {
        std::cout << *iter << ",";
        ++iter;
    }
    std::cout << "\n";
}

int main(void) {
   
    // integer linked list
    LinkedList<int> *l1 = new LinkedList<int>();
    for (int i=1; i<8; i++) {
        l1->addBack(i);
    }
    std::cout << "l1 created: ";
    printList(l1);

    // test filter first
    std::cout << "Testing filter, keeping only even numbers in l1:\n";
    IsEven<const int&> *f1 = new IsEven<const int&>(); 
    l1->filter(f1);
    std::cout << "l1 after filtering: ";
    printList(l1); 
    
    // test split
    LinkedList<int> *l2 = new LinkedList<int>();
    for (int i=1; i<8; i++) {
        l2->addBack(i);
    }
    std::cout << "l2 created: ";
    printList(l2);

    /*
    std::cout << "Testing copy constructor, making l1=l2\n";
    LinkedList<int> *l1 = new LinkedList<int>(*l2);
    std::cout << "l1 is: ";
    printList(l1);
    */

    std::cout << "Testing split, using mod 3:\n";
    Mod3<const int&> *f2 = new Mod3<const int&>();
    std::vector<LinkedList<int> > sp = l2->split(f2);
    //std::vector<LinkedList<int> > sp = l2->split2(f2);
    for (unsigned i=0; i<sp.size(); i++) {
        std::cout << "sp["<<i<<"] is: ";
        printList(&sp[i]);
    }
    std::cout << "l2 is now: ";
    printList(l2);

    // test foldl
    const int start = 0;
    std::cout<< "Testing foldl on l2\n";
    Sum<int> *f3 = new Sum<int>();
    int l2_sum = l2->foldl(f3, start);
    std::cout<<"Sum of l2 from fold l is "<<l2_sum<<"\n";
    
    delete l1;
    delete f1;
    delete l2;
    delete f2;
    delete f3;
    return EXIT_SUCCESS;
}
            
