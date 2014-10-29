#include "bstset.h"
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string>

int main(void) {
    // create a set of ints
    BstSet<int> *s1 = new BstSet<int>();
    s1->add(2);
    s1->add(4);
    s1->add(1);
    s1->add(7);
    s1->add(3);
    s1->add(9);
    s1->add(-1);
    s1->add(88);
    s1->add(17);
    s1->add(-23);
    s1->add(16);
    s1->add(44);
    s1->add(77);
    std::cout << "Created a set s1 with " << s1->getSize() << " entries\n";
    s1->printMap();

    std::cout << "s1 contains 3? " << s1->contains(3) << std::endl;
    std::cout << "s1 contains 0? " << s1->contains(0) << std::endl;
    std::cout << "Adding 3 again to s1\n";
    s1->printMap();

    // test remove
    std::cout << "\nTesting Remove\n";
    std::cout << "Removing root node 2, should be fine\n";
    s1->remove(2);
    s1->printMap();
    std::cout << "Removing nonexisting 0, nothing should change\n";
    s1->remove(0);
    s1->printMap();

    // test copy constructor
    std::cout << "\nTesting copy constructor\n";
    std::cout << "Make s1(s2)\n";
    BstSet<int> s2(*s1);
    std::cout << "s1 is\n";
    s1->printMap();
    std::cout << "s2 is \n";
    s2.printMap();
    std::cout << "Add 2 to s2\n";
    s2.add(2);
    std::cout << "s1 is\n";
    s1->printMap();
    std::cout << "s2 is \n";
    s2.printMap();

    // assignment operator
    std::cout << "\nTesting assignment operaotr\n";
    std::cout << "Let s3=s2, then adding 0 to s3\n";
    BstSet<int> s3 = s2;
    s3.add(0);
    std::cout << "s2 is\n";
    s2.printMap();
    std::cout << "s3 is\n";
    s3.printMap();


    delete s1;
    return EXIT_SUCCESS;
}
