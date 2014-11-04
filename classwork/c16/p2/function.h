#ifndef __FUNCTION_H__
#define __FUNCTION_H__
template<typename R, typename A> 
class Function {
public:
  virtual R invoke(A arg) = 0;
  virtual ~Function() {}
  // used for counting how mnay invokes is called.
  //virtual const int getCount() const = 0;
};
#endif
