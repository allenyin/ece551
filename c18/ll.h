#pragma once
#include <cstdlib>
#include <exception>
#include <assert.h>
#include <vector>
#include <utility>
#include <iostream>
#include <sstream>
#include <stdio.h>

class MyException: public std::exception {
    virtual const char* what() const throw() {
        return "Requested item does not exist";
    }
};

template<typename T>
class LinkedList {
    private:
        // private class
        class Node {
            public: 
                T data;
                Node * next;
                Node * prev;
                Node() : data(), next(NULL), prev(NULL) {}
                Node (const T & d) : data(d), next(NULL), prev(NULL) {}
                Node(const T & d, Node *n, Node *p) : data(d),
                next(n),
                prev(p) {}
                ~Node() {}
        };

        // private methods
        void clear_nodes() {
            if (head == NULL) {
                return;
            }
            while (head != NULL) {
                Node * temp = head;
                head = head->next;
                delete temp;
            }
            tail = NULL;
        }

        // private members.
        Node * head;
        Node * tail;
        int size;

    public:
        // public class
        class iterator {
            private:
                Node * curr;
            public:
                iterator(Node *n): curr(n) {}
                ~iterator() {} // no need to deallocate anything
                iterator(const iterator & rhs): curr(rhs.curr) {}
                iterator & operator=(const iterator & rhs) {
                    curr = rhs.curr;
                    return *this;
                }
                T & operator*() {
                    return curr->data;
                }
                bool operator!=(const iterator &rhs) const {
                    return curr != rhs.curr;
                }
                iterator & operator++() {
                    // for use like ++iter
                    curr = curr->next;
                    return *this;
                }
        };

        // costructors and destructors
        LinkedList() : head(NULL), tail(NULL), size(0) {}
        LinkedList(const LinkedList<T> & rhs) {
            //std::cout << "Copy constructor, rhs is: ";
            //rhs.printList();
            head = NULL;
            tail = NULL;
            size = rhs.size;
            if (rhs.head != NULL) {
                Node * curr;
                Node * prev;
                Node * rhs_curr = rhs.head;
                for (int i=0; i<size; i++) {
                    // tail always points at the newly created Node.
                    if (head == NULL) {
                        head = new Node();
                        head->data = rhs_curr->data;
                        prev = head;
                        tail = head;
                    }
                    else {
                        curr = new Node();
                        curr->data = rhs_curr->data;
                        prev->next = curr;
                        curr->prev = prev;
                        prev = curr;
                        tail = curr;
                    }
                    rhs_curr = rhs_curr->next;
                }
            }
        } 

        ~LinkedList() {
            clear_nodes();
        }

        // public methods
        const int getSize() const {
            return size;
        }

        void printList() const {
            iterator iter = begin();
            while(iter != end()) {
                std::cout << *iter << ",";
                ++iter;
            }
            std::cout << "\n";
        }


        LinkedList<T> & operator=(const LinkedList<T> & rhs) {
            assert((this != &rhs));
            size = rhs.size;
            clear_nodes();  // clear nodes regardless
            if (rhs.head != NULL) {
                head = NULL;
                Node * curr;
                Node * prev;
                Node * rhs_curr = rhs.head;
                for (int i=0; i<size; i++) {
                    if (head == NULL) {
                        head = new Node();
                        head->data = rhs_curr->data;
                        prev = head;
                    }
                    else {
                        curr = new Node();
                        curr->data = rhs_curr->data;
                        prev->next = curr;
                        curr->prev = prev;
                        prev = curr;
                    }
                    rhs_curr = rhs_curr->next;
                }
                tail = curr;
            } 
            else {
                head = NULL;
                tail = NULL;
            }
            return *this;
        }


        void addFront(const T& item) {
            Node *temp = new Node(item, NULL, NULL);
            if (head == NULL) {
                head = temp;
                tail = temp;
            }
            else {
                head->prev = temp;
                temp->next = head;
                head = temp;
            }
            ++size;
        }

        void addBack(const T& item) {
            Node *temp = new Node(item, NULL, NULL);
            if (tail == NULL) {
                head = temp;
                tail = temp;
            }
            else {
                tail->next = temp;
                temp->prev = tail;
                tail = temp;
            }
            ++size;
        }

        bool remove(const T &item) {
            if (head == NULL) {
                return false;
            }
            Node * cur = head;
            while (cur->next != NULL && cur->data != item) {
                cur = cur->next;
            }
            if (cur->data == item) {
                if (cur->prev == NULL) {
                    // if item is the first node
                    head = cur->next;
                    if (cur->next != NULL) {
                        cur->next->prev = NULL;
                    }
                    else {
                        // no more items left;
                        tail = head;
                    }
                }
                else if (cur->next == NULL) {
                    // if item is the last node
                    tail = cur->prev;
                    if (cur->prev != NULL) {
                        cur->prev->next = NULL;
                    }
                    else {
                        // no more items left;
                        head = tail;
                    }
                }
                else {
                    cur->prev->next = cur->next;
                    cur->next->prev = cur->prev;
                }
                delete cur;
                size--;
                return true;
            }
            else {
                // at end of the list, item not found
                return false;
            }
        }

        const T& operator[](int index) const {
            if (index >= size || index<0) {
                throw MyException(); 
            }
            int i=0;
            Node * cur = head;
            while (i != index) {
                cur = cur->next;
                i++;
            }
            return cur->data;
        }

        T& operator[](int index) {
            if (index >= size || index<0) {
                throw MyException();
            }
            int i=0;
            Node * cur = head;
            while (i != index) {
                cur = cur->next;
                i++;
            }
            return cur->data;
        }

        int find(const T &item) {
            Node * cur = head;
            for (int i=0; i<size; i++) {
                if (cur->data == item) {
                    return i;
                }
                cur = cur->next;
            }
            return -1;
        }

        // iterator methods
        iterator begin() const {
            iterator b = iterator(head);
            return b;
        }

        iterator end() const {
            iterator e = iterator(NULL);
            return e;
        } 

};


