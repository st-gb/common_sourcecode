#pragma once //Include guard
#ifndef STDSTRING_FORMAT_HPP_ //Include guard
  #define STDSTRING_FORMAT_HPP_

//from http://www.codeguru.com/forum/showthread.php?t=231056:
#include <string> //std::string
#include <sstream> //for std::istringstream
//#include <iostream>

//  #include <exception> //for class std::exception
//  #ifndef WIN32
//    #include <stdexcept> //for class "runtime_error"
//  #endif //#ifndef WIN32
//
//  //#ifdef WIN32
//  class NumberFormatException
//    : public
//    #if defined(_MSC_VER) //if MicroSoft (C) Compiler
//      std::runtime_error
//    #else //Linux, MinGW, Cygwin (,...)
//      //  ::RuntimeException
//      std::exception
//    #endif
//  {
//  public:
//    NumberFormatException(const std::string& s)
//      #ifdef __CYGWIN__
//      //  ::RuntimeException
//      //  std::exception()
//      #else
//        #ifdef _MSC_VER
//        :
//        std::runtime_error(s)
//        #endif
//      #endif
//      {}
//  };
//  //#endif

template <class T>
std::string to_stdstring(T t//, std::ios_base & (*f)(std::ios_base&)
                      )
{
  std::ostringstream oss;
  oss << //f 
    //std::hex << 
    t;
  std::string str = oss.str() ;
  return //oss.str();
    str ;
}

//Convert std::string to e.g. a float value:
//float fValue ; std::string stdstr = "8.0";
// from_stdstring<float>(fValue , stdstr ) ;
//template <class T>
////T
////void *
//void from_stdstring(
//  T & t
//  , std::string & stdstr//, std::ios_base & (*f)(std::ios_base&)
//  //, void * pv
//  )
//{
//  std::istringstream iss;
//  iss.str(stdstr) ;
//  //iss >> stdstr ;
//  iss >> //(t) *pv ;
//    t ;
//  //std::string str = iss.str() ;
//  //return //oss.str();
//  //  //str ;
//  //  pv ;
//}

template <class T>
//true: succeeded.
bool from_stdstring(
   T & r_templateType,
   const std::string & r_stdstr
   //,std::ios_base& (*f)(std::ios_base&)
  )
{
  //DEBUG("from_string:%s\n",s);
//  LOG("from_string:" << s << "\n" );
  std::istringstream iss(r_stdstr);
  return ! ( iss //>> f
    >> r_templateType
    ).fail();
}

////convert std::string to e.g. a float value
//template <class T>
////T
////void *
//void from_stdtstring(
//  T & t
//  , std::wstring & stdwstr//, std::ios_base & (*f)(std::ios_base&)
//  //, void * pv
//  )
//{
//  std::wistringstream iss;
//  iss.str(stdwstr) ;
//  //iss >> stdstr ;
//  iss >> //(t) *pv ;
//    t ;
//  //std::string str = iss.str() ;
//  //return //oss.str();
//  //  //str ;
//  //  pv ;
//}

//convert std::string to e.g. a float value
template <class T>
//T
//void *
void from_stdtstring(
  T & t
  , std::string & stdstr//, std::ios_base & (*f)(std::ios_base&)
  //, void * pv
  )
{
  std::istringstream iss;
  iss.str(stdstr) ;
  //iss >> stdstr ;
  iss >> //(t) *pv ;
    t ;
  //std::string str = iss.str() ;
  //return //oss.str();
  //  //str ;
  //  pv ;
}
#endif //STDSTRING_FORMAT_HPP_
