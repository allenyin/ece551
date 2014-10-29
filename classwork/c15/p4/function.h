#ifndef __GRADER_FUNCTION_H__
#define __GRADER_FUNCTION_H__
#include <iostream>
#include <string>
#include <sstream>

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}
#ifndef __FUNCTION_H__
#define __FUNCTION_H__
template<typename R, typename A> 
class Function {
public:
  virtual R invoke(A arg) = 0;
  virtual ~Function() {}
};
#endif

class PrintIntFunction:public Function<void, const int &>
{

 virtual void invoke(const int & arg)
 {
         std::cout << "Applying an int print: " << arg << std::endl;
 }

 ~PrintIntFunction(){}
};

class PrintStrFunction:public Function<void, const std::string &>
{

 virtual void invoke(const std::string & arg)
 {
         std::cout << "Applying an string print: " << arg << std::endl;
 }

 ~PrintStrFunction(){}
};


class StrToUpper: public Function<std::string, const std::string &>
{
 virtual std::string invoke(const std::string &str)
 {
  std::locale loc;
  
 std::string retStr(str.length(), ' ');
   for (std::string::size_type i=0; i<str.length(); ++i)
   {
    retStr[i] = std::toupper(str[i],loc);
    }
    return retStr;
 }

~StrToUpper(){}

};

class StrToLower: public Function<std::string , const std::string &>
{
 virtual std::string  invoke(const std::string &str)
 {
  std::locale loc;
  std::string retStr(str.length(), ' ');
   for (std::string::size_type i=0; i<str.length(); ++i)
   {
    retStr[i] = std::tolower(str[i],loc);
    }
    return retStr;
 }

~StrToLower(){}

};

class StrSplit: public Function<unsigned , const std::string &>
{
 virtual unsigned invoke(const std::string &str)
 {
  return str.length(); 
 }

~StrSplit(){}

};



class IntTimes2: public Function<int, const int &>
{
 virtual int  invoke(const int & data)
 {
         return data * 2;
 }

~IntTimes2(){}

};

class IntSum: public Function<int, std::pair<const int&,const int&> >
{
 virtual int  invoke(std::pair<const int&,const int&> data)
 {
         return data.first + data.second;
 }

~IntSum(){}

};



class IntToDollar: public Function<std::string , const int &>
{
 virtual std::string  invoke(const int & data)
 {
    return "$" + patch::to_string(data) + ".00";
 }

~IntToDollar(){}

};
class IntEven: public Function<bool, const int &>
{
 virtual bool  invoke(const int & data)
 {
  if(data%2 == 0)
  {
    return true;
    }
    else
    {
    
     return false;
    }
 }

~IntEven(){}

};



#endif
