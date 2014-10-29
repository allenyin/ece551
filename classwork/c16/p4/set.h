#ifndef __SET_H__
#define __SET_H__
#include <stdexcept>

template<typename K>
class Set{
public:
  virtual void add(const K & key) = 0;
  virtual bool contains(const K& key) const = 0;
  virtual void remove(const K& key) = 0;
};
#endif
