/** ConvertToTypename.hpp
 *  Created on: 31.01.2019
 *      Author: Stefan */
#pragma once///Include guard
#ifndef CONVERTTOTYPENAME_HPP_
#define CONVERTTOTYPENAME_HPP_

//idea from http://www.codeguru.com/forum/showthread.php?t=231056 /
// http://www.cplusplus.com/forum/general/12754/ "computerquip" Jul 18, 2009 at
// 4:22am
#include <string> //class std::string
#include <sstream> //for class std::istringstream

/** @brief Convert char array to e.g. a float value:
* float fValue ; std::string stdstr = "8.0";
* ConvertToTypename<float>(fValue , stdstr ) ; */
template <typename typenameConvertFromString>
/** @return true: succeeded. */
bool ConvertToTypename(
   typenameConvertFromString & r_typename_convert_from_string,
   const char charString []
   //,std::ios_base& (*f)(std::ios_base&)
  )
{
  //DEBUG("ConvertStdStringToTypename:%s\n",s);
//  LOG("ConvertStdStringToTypename:" << s << "\n" );
  //"static" : To not to create each time this function is called->faster.

  //Did not convert sometimes when the string stream object was "static".
//  static std::istringstream std_istringstream; //(c_r_std_str);
  std::istringstream std_istringstream;

  std_istringstream.str(charString);

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
#ifdef DEBUG
  if( ! bGood )
  {
    std::string std_str = std_istringstream.str();
    int n = std_str.length();
    n += 0;
  }
#endif
  return bGood;
}

namespace NS_ConvertStdStringToTypename
{
  enum ConvertStdStringToTypename
  {
    failed = 0,
    succeeded
  };
}
/** @brief Convert std::string to e.g. a float value:
* float fValue ; std::string stdstr = "8.0";
* ConvertStdStringToTypename<float>(fValue , stdstr ) ; */
template <typename typenameConvertFromString>
/** @return true: succeeded. */
bool ConvertCharStringToTypename(
   typenameConvertFromString & r_typename_convert_from_string,
   const char * const c_str
   //,std::ios_base& (*f)(std::ios_base&)
  )
{
  bool bGood = false;
  if(c_str )
    bGood = ConvertStdStringToTypename(r_typename_convert_from_string,
      std::string(c_str) );
  return bGood;
}

#endif /* CONVERTTOTYPENAME_HPP_ */
