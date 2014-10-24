#include "ll.h"
#include "function.h"
#include <stdio.h>
#include <string> 
#include <cstdlib>
#include <iostream>
#include <sstream>

// function to test app
template<typename T>
class PrinterFunction : public Function<void, const T&> {
    // no need for constructors because no data
    public:
        virtual void invoke(const T& arg) {
            std::cout << arg << "\n";
        }
};

// function to test update
template<typename T>
class AddToEach: public Function<T, const T&> {
    private:
        T v;
    public:
        AddToEach(T _v): v(_v) {}
        AddToEach(const AddToEach & rhs): v(rhs.v) {} 
        AddToEach & operator=(const AddToEach & rhs) {
            T * temp_v = new T(rhs.v);
            delete v;
            v = *temp_v;
            return *this;
        } 

        virtual T invoke(const T& x){
            // assume there's a method for R+x;
            return x+v;
        }
};

// function to test map
template<typename T>
class ConvertToString : public Function<std::string, const T&> {
    public:
        // no constructor, because no resources to manage.
        virtual std::string invoke(const T& x) {
            std::ostringstream os;
            os << "\"" << x << "\"";
            return os.str();
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
    l1->addBack(1);
    l1->addBack(2);
    l1->addFront(3);
    l1->addFront(4);
    std::cout << "l1 created: ";
    printList(l1);

    // test app
    std::cout << "Printing l1 with generic traversal:\n";
    PrinterFunction<int> *p1 = new PrinterFunction<int>();
    l1->app(p1);

    // test update
    std::cout << "l1 is now: ";
    printList(l1);
    std::cout << "Testing Update, adding 2 to all items:\n";
    AddToEach<int> *a1 = new AddToEach<int>(2);
    l1->update(a1);
    std::cout << "l1 is now: ";
    printList(l1);

    // test map
    std::cout << "Testing Map, put quotemarks around string rep of items:\n";
    ConvertToString<int> *c1 = new ConvertToString<int>();
    LinkedList<std::string> *l2 = l1->map(c1);
    std::cout << "l1 is now: ";
    printList(l1);
    std::cout << "l2 is now: ";
    printList(l2);

    // string linked list
    LinkedList<std::string> *l3 = new LinkedList<std::string>();
    l3->addBack("Allen");
    l3->addBack("Yin");
    l3->addBack("isBest!");
    l3->addFront("Truth");
    std::cout << "l3 created: ";
    printList(l3);

    // test app
    std::cout << "Print l3 with generic traversal:\n";
    PrinterFunction<std::string> *p2 = new PrinterFunction<std::string>();
    l3->app(p2);

    // test update
    std::cout << "Testing Update, adding 9000 to all items:\n";
    AddToEach<std::string> *a2 = new AddToEach<std::string>("9000");
    l3->update(a2);
    std::cout << "l3 is now: ";
    printList(l3);

    // test map
    std::cout << "Testing Map, put quotemarks around string rep of items:\n";
    ConvertToString<std::string> *c2 = new ConvertToString<std::string>();
    LinkedList<std::string> *l4 = l3->map(c2);
    std::cout << "l3 is now: ";
    printList(l3);
    std::cout << "l4 is now: ";
    printList(l4);

    
    delete l1;
    delete p1;
    delete a1;
    delete c1;
    delete l2;
    delete l3;
    delete p2;
    delete a2;
    delete c2;
    delete l4;
    return EXIT_SUCCESS;
}
