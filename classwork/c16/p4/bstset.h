#pragma once
#include "set.h"
#include <iostream>
#include <cstdlib>

template<typename K>
class BstSet : public Set<K> {
    private:
        // BstNode class
        class BSTNode {
            public:
                K key;
                BSTNode * left;
                BSTNode * right;
                BSTNode() : key(), left(NULL), right(NULL) {}
                BSTNode(const K& _key): key(_key), left(NULL), right(NULL) {}
                BSTNode(const K& _key, BSTNode* l, BSTNode* r) :
                    key(_key), left(l), right(r) {}
                ~BSTNode() {}
                // no copy constructor or assignment operator
        };

        // private members
        BSTNode * root;
        int size;

    public:
        // constructors
        BstSet() : root(NULL), size(0) {}
        // copy constructor
        BstSet(const BstSet<K> & rhs) {
            root = copytree(rhs.root);
            size = rhs.size;
        }
        BSTNode * copytree(const BSTNode* source) {
            if (source == NULL) {
                return NULL;
            }
            BSTNode *target = new BSTNode(source->key);
            if (source->left != NULL) {
                target->left = copytree(source->left);
            }
            if (source->right != NULL) {
                target->right = copytree(source->right);
            }
            return target;
        }
        // assignment operator
        BstSet<K> & operator=(const BstSet<K> & rhs) {
            assert(this != &rhs);
            cleartree(root);
            root = copytree(rhs.root);
            size = rhs.size;
            return *this;
        }
        void cleartree(BSTNode * source) {
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
        ~BstSet() {
            cleartree(root);
        }

        virtual void add(const K & key) {
            BSTNode * b = new BSTNode(key);
            BSTNode **ptr = & root;
            while (*ptr != NULL) {
                if (key < (*ptr)->key) {
                    ptr = & (*ptr)->left;
                }
                else if (key > (*ptr)->key) {
                    ptr = & (*ptr)->right;
                }
                else {
                    // key is already there, dont do anything
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

        BSTNode * remove(BSTNode * curr, K key) {
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
            if (curr->right== NULL) {
                replace->key = curr->key;
                BSTNode * temp = curr->left;
                delete curr;
                return temp;
            }
            curr->right = twoChildRm(curr->right, replace);
            return curr;
        }

        bool contains(const K& key) const {
            BSTNode * curr = root;
            while (curr != NULL) {
                if (curr->key == key) {
                    return true;
                }
                if (key < curr->key) {
                    curr = curr->left;
                }
                else {
                    curr = curr->right;
                }
            }
            return false;
        }

        const int getSize() const {
            return size;
        }

        const void printMap(void) const {
            inorder(root);
        }

        const void inorder(BSTNode * curr) const {
            if (curr != NULL) {
                inorder(curr->left);
                std::cout << curr->key << std::endl;
                inorder(curr->right);
            }
        }
};

