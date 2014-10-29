#pragma once
#include "map.h"
#include <iostream>
#include <cstdlib>
#include <assert.h> 

template<typename K, typename V>
class BstMap : public Map<K, V> {
    private:
        // BstNode class
        class BSTNode {
            public:
                K key;
                V value;
                BSTNode * left;
                BSTNode * right;
                BSTNode() : key(), value(), left(NULL), right(NULL) {}
                BSTNode (const K & _key, const V & _value) : 
                    key(_key), value(_value), left(NULL), right(NULL) {}
                BSTNode(const K & _key, const V & _value, BSTNode *l, BSTNode *r) :
                    key(_key), value(_value), left(l), right(r) {}
                ~BSTNode() {}
                // no copy constructor or assignment operator, add if I need them
        };

        // private memebers
        BSTNode * root;
        int size;

    public:
        // constructors
        BstMap() : root(NULL), size(0) {}
        // copy constructor
        BstMap(const BstMap<K, V> & rhs) {
            root = copytree(rhs.root);
            size = rhs.size;
        }
        BSTNode * copytree(const BSTNode *source) {
            if (source == NULL) {
                return NULL;
            }
            BSTNode *target = new BSTNode(source->key, source->value);
            if (source->left != NULL) {
                target->left = copytree(source->left);
            }
            if (source->right != NULL) {
                target->right = copytree(source->right);
            }
            return target;
        }
        // assignment operator
        BstMap<K, V> & operator=(const BstMap<K,V> & rhs) {
            assert(this != &rhs);
            cleartree(root);
            root = copytree(rhs.root);
            size = rhs.size;
            return *this;
        }

        /* this can only be called from inside even though it's public,
         * because the only method that gives a BSTNode reference is the
         * assignement operator
         */
        void cleartree(BSTNode *source) {
            // delete all the nodes in tree originating from source
            if (source == NULL) {
                return;
            }
            if (source->left != NULL) {
                cleartree(source->left);
            }
            if (source->right != NULL) {
                cleartree(source->right);
            }
            delete source;
        }

        // destructor
        ~BstMap() {
            cleartree(root);
        }

        virtual void add(const K & key, const V & value) {
            BSTNode * b = new BSTNode(key, value);
            BSTNode **ptr = & root;
            while (*ptr != NULL) {
                if (key < (*ptr)->key) {
                    ptr = & (*ptr)->left;
                }
                else if (key > (*ptr)->key) {
                    ptr = & (*ptr)->right;
                }
                else {
                    // the key is already there, replace the value
                    (*ptr)->value = value;
                    delete b;
                    return;
                }

            }
            *ptr = b;
            ++size;
        }
        
        virtual void remove(const K& key) {
            root = remove(root, key);
            if (size > 0 && root != NULL) {
                --size;
            }
        }

        BSTNode * remove(BSTNode *curr, K key) {
            if (curr == NULL) {
                return NULL;
            }
            if (curr->key == key) {
                BSTNode * temp;
                if (curr->left == NULL) {
                    temp = curr->right;
                    delete curr;
                    return temp;
                }
                if (curr->right == NULL) {
                    temp = curr->left;
                    delete curr;
                    return temp;
                }
                // otherwise have to decide more
                curr->left = twoChildRm(curr->left, curr);
                return curr;
            }
            else if (key < curr->key) {
                curr->left = remove(curr->left, key);
            }
            else {
                curr->right = remove(curr->right, key);
            }
            return curr;
        }

        BSTNode * twoChildRm(BSTNode * curr, BSTNode * replace) {
            // replace is the node that will be replaced
            // our protocol is to replace with rightmost left-child
            if (curr->right == NULL) {
                replace->key = curr->key;
                replace->value = curr->value;
                BSTNode * temp = curr->left;
                delete curr;
                return temp;
            }
            curr->right = twoChildRm(curr->right, replace);
            return curr;
        }


        virtual const V & lookup(const K& key) const throw (std::invalid_argument) {
            BSTNode * curr = root;
            while (curr != NULL) {
                if (curr->key == key) {
                    return curr->value;
                }
                if (key < curr->key) {
                    curr = curr->left;
                }
                else {
                    curr = curr->right;
                }
            }
            throw std::invalid_argument("Key not found!");
        }

        const int getSize() const {
            return size;
        }

        const void printMap(void) const {
            inorder(root);
        }
        
        const void inorder(BSTNode * curr) const{
            if (curr != NULL) {
                inorder(curr->left);
                std::cout << curr->key << ":" << curr->value << std::endl;
                inorder(curr->right);
            }
        }

};
