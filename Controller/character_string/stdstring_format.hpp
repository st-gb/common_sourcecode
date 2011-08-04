#pragma once //Include guard

#ifndef STDSTRING_FORMAT_HPP_ //Include guard
  #define STDSTRING_FORMAT_HPP_

//idea from http://www.codeguru.com/forum/showthread.php?t=231056 /
//  http://www.cplusplus.com/forum/general/12754/  "computerquip" Jul 18, 2009 at 4:22am
#include <string> //class std::string
#include <sstream> //for class std::istringstream
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

//Another idea see also http://www.codeguru.com/forum/showthread.php?t=231056
// for a version that can pass a " std::ios_base" function
// (can format as hex digit etc.)
template <typename typenameConvertToString>
std::string convertToStdString(
    typenameConvertToString typename_convert_to_string
  )
{
  //"static" : To not to create each time this function is called->faster.
  static
    std::ostringstream std_ostringstream;
  //Set to empty string because the object is a local static variable and may
  //have content from before.
  std_ostringstream.str("");
  std_ostringstream <<
    typename_convert_to_string;
//  std::string std_str = std_ostringstream.str() ;
  return std_ostringstream.str();
    //std_str ;
}

//Convert std::string to e.g. a float value:
//float fValue ; std::string stdstr = "8.0";
// ConvertStdStringToTypename<float>(fValue , stdstr ) ;
template <typename typenameConvertFromString>
//true: succeeded.
bool ConvertStdStringToTypename(
   typenameConvertFromString & r_typename_convert_from_string,
   const std::string & c_r_std_str
   //,std::ios_base& (*f)(std::ios_base&)
  )
{
  //DEBUG("ConvertStdStringToTypename:%s\n",s);
//  LOG("ConvertStdStringToTypename:" << s << "\n" );
  //"static" : To not to create each time this function is called->faster.

  //Did not convert sometimes when the string stream object was "static".
//  static std::istringstream std_istringstream; //(c_r_std_str);
  std::istringstream std_istringstream;

  std_istringstream.str(c_r_std_str);

  //atof returned 1 for "1.2" on Linux on German because the decimal
  //point is a "," in German.
  //http://stackoverflow.com/questions/1333451/c-locale-independent-atof:
  //"localeconv (in <locale.h>) returns a pointer to struct whose
  //decimal_point member contains that value. Note that the pointer
  //is valid until the next localeconv() or setlocale() – "
  //fAtofResult = (float) atof(pchAttributeValue ) ;

  //Ensure a "." is interpreted as decimal point no matter what the
  //current locale is.
//  std_istringstream.imbue( std::locale("C") );

//  return ! ( std_istringstream //>> f
//    >> r_typename_convert_from_string
//    ).fail();
  std_istringstream >> r_typename_convert_from_string;
  bool bGood = //std_istringstream.good();
    ! std_istringstream.fail();
  if( ! bGood )
  {
    std::string std_str = std_istringstream.str();
    int n = std_str.length();
    n += 0;
  }
  return bGood;
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
#endif //STDSTRING_FORMAT_HPP_
