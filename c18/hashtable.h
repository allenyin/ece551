#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__
#include "ll.h"
#include <stdio.h>


template<typename T> 
class SetADT {
    public:
        virtual void add(const T & item) = 0;
        virtual bool contains(const T &item) const = 0;
        virtual void remove(const T & item) = 0;
};

template<typename R, typename A>
class Function {
    public:
        virtual R invoke(A arg) = 0;
};



template<typename T>
class HashSet : public SetADT<T> {
    private:
        int numBuckets;
        LinkedList<T> * buckets;
        int numItems;
        Function<unsigned, const T &> * hashFunction;
        void rehash() {
            printf("Rehashing from %d to %d\n", numBuckets, numBuckets*2);
            //make a new array (newBuckets) which is twice as large
            LinkedList<T> * newBuckets = new LinkedList<T>[numBuckets * 2];
            //copy everthing from our current buckets
            // count (i) from 0 to numBuckets
            for(int i = 0; i < numBuckets; i++) {
                //   get every item from the list (buckets[i])
                for (int j = 0; j < buckets[i].getSize(); j++) {
                    //   for each of these items
                    const T & item = buckets[i][j];
                    //      - compute its new index in the new array
                    unsigned newIndex = hashFunction->invoke(item) % (numBuckets * 2);
                    //      - put that item into newBuckets[newIndex]
                    newBuckets[newIndex].addFront(item);
                }
            }
            // delete[] buckets
            delete[] buckets;
            // update buckets and numBuckets
            buckets = newBuckets;
            numBuckets = numBuckets * 2;
        }
    public:
        HashSet(Function<unsigned, const T&>* f): numBuckets(47),
                                                  buckets(new LinkedList<T>[numBuckets]),
                                                  numItems(0),
                                                  hashFunction(f) {}
        HashSet(const HashSet & rhs): numBuckets(0),
                                      buckets(NULL),
                                      numItems(0),
                                      hashFunction(NULL) {
            *this = rhs;
        }
        ~HashSet() {
            delete[] buckets;
        }
        HashSet & operator=(const HashSet& rhs) {
            if (this != &rhs) {
                delete[] buckets;
                numBuckets = rhs.numBuckets;
                buckets = new LinkedList<T>[numBuckets];
                numItems = rhs.numItems;
                hashFunction = rhs.hashFunction;
                for (int i = 0; i < numBuckets; i++) {
                    buckets[i] = rhs.buckets[i];
                }
            }
            return *this;
        }

        virtual void add(const T & item) {
            if (!contains(item)) {
                //turn item into "number"
                unsigned hashedItem = hashFunction->invoke(item);
                //mod that number by the array size (number of Buckets)
                unsigned index = hashedItem % numBuckets;
                //index into the array at that bucket
                //add the item to the list at that array index
                buckets[index].addFront(item);
                //update our item count
                numItems++;
                //check if we should rehash
                if (numItems >= numBuckets / 2) {
                    //if so, do it.
                    rehash();
                }
            }
        }
        virtual bool contains(const T &item) const {
            unsigned hashedItem = hashFunction->invoke(item);
            unsigned index = hashedItem % numBuckets;
            return buckets[index].find(item) != -1;
        }
        virtual void remove(const T & item) {
            unsigned hashedItem = hashFunction->invoke(item);
            unsigned index = hashedItem % numBuckets;
            buckets[index].remove(item);
        }

};



#endif
