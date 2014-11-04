#include "node.h"
#include <iostream>

Node *  buildTree(uint64_t * counts) {
    // make a priority queue
    priority_queue_t *pq = new priority_queue_t();
    
    // create nodes for all zero characters
    for (unsigned i=0; i<257; i++) {
        // make a new node if entry not 0
        if (counts[i]>0) {
            Node *n = new Node(i, counts[i]);
            pq->push(n);
        }
    }

    // build the tree until pq's size is 1
    while (pq->size() > 1) {
        Node *child1 = pq->top();
        pq->pop();
        Node *child2 = pq->top();
        pq->pop();
        Node *parent = new Node(child1, child2);
        pq->push(parent);
    }
    
    // return the tree
    Node * ans = pq->top();
    pq->pop();
    delete pq;
    return ans;
}  
