#pragma once
#include <cstdlib>
#include <exception>
#include <assert.h>
#include "function.h"
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
        
        /*
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
            ++size;
            //std::cout << "size increased here!\n";
            if (size==1) {
                head = tail;
            }
        }
        */

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

        // generic traversals p3
        void app(Function<void,const T&> * f) const {
            /* invoke f on each item of list; const so doesnt change
             * item
             */
            Node * curr = head;
            while (curr != NULL) {
                f->invoke(curr->data);
                curr = curr->next;
            }
        }

        void update(Function<T, const T&> *f) {
            /* invoke f on each item of the list and replace with return value
             * of f on that item.
             */
            Node * curr = head;
            while (curr != NULL) {
                curr->data = f->invoke(curr->data);
                curr = curr->next;
            }
        }

        template<typename R>
        LinkedList<R> * map(Function<R, const T&> *f) const {
            /* Create and return a *new* LinkedList (hold Rs), where
             * each item of the returned list is determined by invoking
             * f on the items of this linked list.
             */
            LinkedList<R> *ll = new LinkedList<R>();
            Node * curr = head;
            while (curr != NULL) {
                ll->addBack(f->invoke(curr->data));
                curr = curr->next;
            }
            return ll;
        }

        // generic traverslas p4
        void filter(Function<bool, const T&> *f) {
            /* Traverse the list, and invoke f on each item.
             * If f returns true, it remain in the list. Else, remove it.
             */
            Node * curr = head;
            while (curr != NULL) {
                if (!(f->invoke(curr->data))) {
                    // remove item if f returns true
                    Node * temp = curr->next;
                    remove(curr->data);
                    /*
                    temp->next = curr->next;
                    if (curr->next != NULL) {
                        temp->next = curr->next;
                    }
                    delete curr;
                    size--;
                    */
                    curr = temp;
                }
                else {
                    curr = curr->next;
                }
            }
        }

        
        //std::vector<LinkedList<T> > split(Function<unsigned, const T&> *f) const {
            /* Splits the elements of the LinkedList into multiple LinkedLists,
             * determined by the return value of f.
             * 
             * The vector has length equal to the possible return values of f,
             * the return value of f determines which  index of the return vector 
             * an item is put into.
             */
        /*    std::vector<unsigned> item_idx;
            // first pass to find what index each elements go
            Node * curr = head;
            while (curr != NULL) {
                item_idx.push_back(f->invoke(curr->data));
                curr = curr->next;
            }

            // find max number of bins we need:
            unsigned max = 0;
            std::vector<unsigned>::iterator it = item_idx.begin();
            while (it != item_idx.end()) {
                if (*it>max) {
                    max = *it;
                }
                ++it;
            }

            // second pass to get the right ans to return
            std::vector< LinkedList<T> > ans(max+1);
            curr = head;
            it = item_idx.begin();
            while (curr != NULL) {
                ans[*it].addBack(curr->data);
                curr = curr->next;
                ++it;
            }
            // everything is local variable, no need to free anything.
            return ans;
        }*/

        std::vector<LinkedList<T> > split(Function<unsigned, const T&> *f) const {
            /* Splits the elements of the LinkedList into multiple LinkedLists,
             * determined by the return value of f.
             * 
             * The vector has length equal to the possible return values of f,
             * the return value of f determines which  index of the return vector 
             * an item is put into.
             */
            std::vector< LinkedList<T> > ans;
            Node * curr = head;
            while (curr != NULL) {
                unsigned idx = f->invoke(curr->data);
                if (ans.size() < idx+1) {
                    // default constructor of LinkedList called in resize.
                    //std::cout << "curr->data is: " << curr->data << "\n";
                    ans.resize(idx+1);
                    //std::cout << "resize over\n";
                }
                //std::cout << "Adding curr->data=" << curr->data << "\n";
                ans[idx].addBack(curr->data);
                curr = curr->next;
            }
            return ans;
        }

        
        
        template<typename R>
        R foldl(Function<R, std::pair<const T&, const R&> > *f, const R& start) {
            /* foldl from functional programming/reduce from Python
             * If a list is [e1,e2,,e3, ... eN], then
             * ans1 = f(pair(e1,start)), start is initial value.
             * ans2 = f(pair(e2, ans1))
             * ans3 = f(pair(e3, ans2))
             * ...
             * ansN = f(pair(eN, ansN_Minus1))
             * return ansN.
             */
            return foldl_helper(f, tail, start);
        }

        template<typename R>
        R foldl_helper(Function<R, std::pair<const T&, const R&> > *f, 
                       Node * n, const R& start) {
            if (n->prev == NULL) {
                return f->invoke(std::pair<const T&, const R&>(n->data, start));
            }
            else {
                R prev_ans = foldl_helper(f, n->prev, start);
                return f->invoke(std::pair<const T&, const R&>(n->data, prev_ans));
            }
        }
};


