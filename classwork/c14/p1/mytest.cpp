#include "ll.h"
#include <iostream>
#include <stdio.h>

template <typename T> 
void print_LinkedList(LinkedList<T> l) {
    std::cout << "{";
    for (int i=0; i<l.getSize(); i++) {
        if (i==l.getSize()-1) {
            std::cout << l[i];
        }else {
            std::cout << l[i] << ", ";
        }
    }
    std::cout << "}\n";
}


int main(int argc, char ** argv) {
    LinkedList<int> * l1 = new LinkedList<int>();
    l1->addFront(1);
    l1->addFront(2);
    l1->addFront(3);
    l1->addBack(4);  // l1 should be: 3->2->1->4
    std::cout << "l1 is: ";
    print_LinkedList(*l1);

    LinkedList<int> l2 = *l1;
    std::cout << "l2 is: ";
    print_LinkedList(l2);

    std::cout << "Adding 5 to l2\n";
    l2.addBack(5);
    std::cout << "l2 is now: ";
    print_LinkedList(l2);
    std::cout << "l1 is now: ";
    print_LinkedList(*l1);

    if (l2.remove(5)) {
        std::cout << "Removing 5 successful!\n";
        std::cout << "l2 is now: ";
        print_LinkedList(l2);
        std::cout << "l1 is now: ";
        print_LinkedList(*l1);
    }

    std::cout << "Removing 2 from l1\n";
    l1->remove(2);
    std::cout << "l1 is now: ";
    print_LinkedList(*l1);
    std::cout << "l2 is now: ";
    print_LinkedList(l2);

    std::cout << "Making a list with node=1\n";
    LinkedList<int> * l3 = new LinkedList<int>();
    l3->addFront(1);
    std::cout << "l3 is now: ";
    print_LinkedList(*l3);
    l3->remove(1);
    std::cout << "l3 is now: ";
    print_LinkedList(*l3);

    //std::cout << (*l3)[1];


    delete l3;
    delete l1;
    return EXIT_SUCCESS;
}
