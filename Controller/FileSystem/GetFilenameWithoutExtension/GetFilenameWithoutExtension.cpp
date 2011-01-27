/*
 * GetFilenameWithoutExtension.cpp
 *
 *  Created on: Jan 23, 2011
 *      Author: Stefan
 */
#include <string> //class std::string

std::string GetFilenameWithoutExtension(
  const std::string & cr_stdstrFilePath )
{
  std::string stdstrFilenameWithoutExtension ;
  std::string::size_type basic_string_size_typeLastSlash = cr_stdstrFilePath.
    //"Find last position of a character."
    //"If not found, returns npos."
    rfind('/') ;
  std::string::size_type basic_string_size_typeLastBackSlash =
    cr_stdstrFilePath.
    //"Find last position of a character."
    //"If not found, returns npos."
    rfind('\\') ;
  std::string::size_type basic_string_size_typeLastPoint = cr_stdstrFilePath.
    //"Find last position of a character."
    //"If not found, returns npos."
    rfind('.') ;
  std::string::size_type basic_string_size_typeIndexOfLastChar ;
  std::string::size_type basic_string_size_typeIndexOf1stChar ;

  if( basic_string_size_typeLastPoint == std::string::npos )
    basic_string_size_typeIndexOfLastChar = cr_stdstrFilePath.length() - 1 ;
  else
    basic_string_size_typeIndexOfLastChar = basic_string_size_typeLastPoint
      - 1 ;

  if( basic_string_size_typeLastSlash == std::string::npos )
  {
    if( basic_string_size_typeLastBackSlash == std::string::npos )
      basic_string_size_typeIndexOf1stChar = 0 ;
    else
      basic_string_size_typeIndexOf1stChar =
        basic_string_size_typeLastBackSlash + 1 ;
  }
  else
    basic_string_size_typeIndexOf1stChar = basic_string_size_typeLastSlash
      + 1 ;

  stdstrFilenameWithoutExtension = cr_stdstrFilePath.substr(
    //basic_string_size_typeLastSlash + 1 ,
    basic_string_size_typeIndexOf1stChar ,
    //cr_stdstrFilePath.length() - basic_string_size_typeLastSlash - 1
    basic_string_size_typeIndexOfLastChar -
      basic_string_size_typeIndexOf1stChar + 1
    ) ;
  return stdstrFilenameWithoutExtension ;
}
