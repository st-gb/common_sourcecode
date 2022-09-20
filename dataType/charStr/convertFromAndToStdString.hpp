/**(c)from 2011 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
*Created ca.25.9.2011 by Stefan Gebauer(TU Berlin matriculation number 361095)*/

///Include guard,see http://en.wikipedia.org/wiki/Include_guard
#ifdef TU_Bln361095usePrgmInclGrd
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
#pragma once
#endif
///Include guard supported by (nearly) all compilers:
#ifndef TU_Bln361095cmnSrcConvertFromAndToStdString_hpp
#define TU_Bln361095cmnSrcConvertFromAndToStdString_hpp

//idea from http://www.codeguru.com/forum/showthread.php?t=231056 /
//  http://www.cplusplus.com/forum/general/12754/  "computerquip" Jul 18, 2009 at 4:22am
///Standard C(++) header files:
#include <string> //class std::string
#include <sstream> //for class std::istringstream
//#include <iostream>

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
#include "stdtstr.hpp" //GetStdWstring

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

#include "ConvertStdStringToTypename.hpp"

namespace TU_Bln361095{namespace charStr{
//Another idea see also http://www.codeguru.com/forum/showthread.php?t=231056
// for a version that can pass a " std::ios_base" function
// (can format as hex digit etc.)
template <typename typenameConvertToString>
std::string convertToStdString(
    typenameConvertToString typename_convert_to_string
  )
{
  /** Do NOT use "static" here to not to create each time this function is
   *  called (what would be faster) because of possible multithreading problems
   *  when multiple threads would access the same std::ostringstream object :
   *  https://stackoverflow.com/questions/4590626/c-static-variables-in-multithreaded-program */
  /* static */ std::ostringstream std_ostringstream;
  /** Set to empty string because the object is a local static variable and may
  * have content from before. */
//  std_ostringstream.str("");
  std_ostringstream << typename_convert_to_string;
//  std::string std_str = std_ostringstream.str() ;
  return std_ostringstream.str();
    //std_str ;
}

template <typename typenameConvertToString>
std::wstring convertToStdWstring(
    typenameConvertToString typename_convert_to_string
  )
{
  return GetStdWstring( convertToStdString(typename_convert_to_string) );
}

////convert std::string to e.g. a float value
//template <typename T>
////T
////void *
//void ConvertStdWstringToTypename(
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
template <typename typenameConvertFromString, typename typenameStringCharacter>
//T
//void *
void ConvertStdTStringToTypename(
  typenameConvertFromString & typename_convert_from_string
  , std::basic_string<typenameStringCharacter> & r_std_t_str
  //, void * pv
  )
{
  std::basic_istringstream<typenameStringCharacter> std_basic_istringstream;
  std_basic_istringstream.str(r_std_t_str) ;
  //iss >> stdstr ;
  std_basic_istringstream >> //(t) *pv ;
    typename_convert_from_string ;
  //std::string str = iss.str() ;
  //return //oss.str();
  //  //str ;
  //  pv ;
}
}}///End namespaces

#endif///#ifndef TU_Bln361095cmnSrcConvertFromAndToStdString_hpp