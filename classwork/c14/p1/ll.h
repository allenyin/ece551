#pragma once
#include <cstdlib>
#include <exception>
#include <assert.h>

class MyException: public std::exception {
    virtual const char* what() const throw() {
        return "Requested item does not exist";
    }
};

template<typename T>
class LinkedList {
    private:
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
        Node * head;
        Node * tail;
        int size;
        
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

    public:
        LinkedList() : head(NULL), tail(NULL), size(0) {}
        
        LinkedList(const LinkedList<T> & rhs) {
            head = NULL;
            size = rhs.size;
            if (rhs.head != NULL) {
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
        } 
                
        ~LinkedList() {
            clear_nodes();
        }
        
        const int getSize() const {
            return size;
        }
        
        LinkedList<T> & operator=(const LinkedList<T> & rhs) {
            assert((this != &rhs) && (rhs.head != NULL));
            size = rhs.size;
            if (rhs.head != NULL) {
                clear_nodes();
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
            } else {
                head = NULL;
                tail = NULL;
            }
            return *this;
        }
        
        void addFront(const T &item) {
            Node * temp = head;
            head = new Node(item, temp, NULL);
            if (temp != NULL) {
                temp->prev = head;
            }
            size++;
            if (size==1) {
                tail = head;
            }
        }

        void addBack(const T &item) {
            Node * temp = tail;
            tail = new Node(item, NULL, temp);
            if (temp != NULL) {
                temp->next = tail;
            }
            size++;
            if (size==1) {
                head = tail;
            }
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

};


