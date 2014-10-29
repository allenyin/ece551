#include "bstmap.h"
#include <stdio.h> 
#include <cstdlib>
#include <iostream>
#include <string>

int main(void) {
    // create a map of int to their English version
    BstMap<int, std::string> *m1 = new BstMap<int, std::string>();
    m1->add(7, "seven");
    m1->add(2, "two");
    m1->add(5, "five");
    m1->add(6, "six");
    m1->add(1, "one");
    m1->add(9, "nine");
    m1->add(3, "three");
    std::cout << "Created a map m1 with " << m1->getSize() << " entries\n";
    std::cout << "m1 contains:\n";
    m1->printMap();

    // test adding
    std::cout << "Adding another copy of 6, with value=s\n";
    m1->add(6, "s");
    m1->printMap();

    // test look up
    std::cout << "\nTesting lookup\n";
    std::cout << "Value of 3 is " << m1->lookup(3) << std::endl;
    //std::cout << "Value of 0 should be throwing exception..." << m1->lookup(0) << std::endl;

    // test remove
    std::cout << "\nTesting remove\n";
    m1->remove(6);
    std::cout << "After removing 6, m1 is now:\n";
    m1->printMap();
    std::cout << "Adding 6 back...\n";
    m1->add(6, "six");
    m1->printMap();
    std::cout << "Removing 7, which is the root node, the map should still work...\n";
    m1->remove(7);
    m1->printMap();

    // test copy constructor:
    std::cout << "\nTesting Copy Constructor\n";
    std::cout << "Creating m2=m1\n";
    BstMap<int, std::string> m2(*m1); 
    std::cout << "m1 is now\n";
    m1->printMap();
    std::cout << "m2 is now\n";
    m2.printMap();

    std::cout << "Adding 10 to m2\n";
    m2.add(10, "ten");
    std::cout << "m1 is\n";
    m1->printMap();
    std::cout << "m2 is \n";
    m2.printMap();

    // test assignment operator:
    std::cout << "\nTesting assignement operator...making m1=m2\n";
    *m1 = m2;
    std::cout << "m1 is\n";
    m1->printMap();
    std::cout << "m2 is \n";
    m2.printMap();
    std::cout << "Removing 10 from m1\n";
    m1->remove(10);
    std::cout << "m1 is\n";
    m1->printMap();
    std::cout << "m2 is \n";
    m2.printMap();





    delete m1;
    return EXIT_SUCCESS;
}
