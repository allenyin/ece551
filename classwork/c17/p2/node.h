#ifndef __NODE_H__
#define __NODE_H__
#include <queue>
#include <vector>
#include <cstdlib>
#include <stdint.h>
#define NO_SYM 999

class Node {
public:
  unsigned sym;
  int freq;
  Node * left; 
  Node * right;
  Node(): sym(), freq(), left(NULL), right(NULL) {}
  Node(unsigned s, int f): sym(s), freq(f), left(NULL), right(NULL) {}
  Node(Node * l, Node * r): sym(NO_SYM), freq(l->freq+r->freq), left(l), right(r) {}
  ~Node() {
    if (left != NULL) {
      delete left;
    }
    if (right != NULL) {
      delete right;
    }
  }
};


/* This comparison when used with priority_queue implements a min-heap,
 * if operator(x,y)=True, then x is considered "less important" than y.
 */
class NodePtrCompare: std::binary_function <Node *,Node *,bool> {
public:
  bool operator() (Node *const& x,Node*const& y) const {return x->freq>y->freq;}
};

typedef std::priority_queue<Node *,std::vector<Node*>,NodePtrCompare> priority_queue_t;

Node *  buildTree(uint64_t * counts);
#endif
