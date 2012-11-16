/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */
/*
 * getUTF8string.hpp
 *
 *  Created on: 07.05.2011
 *      Author: Stefan
 */

#ifndef GETUTF8STRING_HPP_
#define GETUTF8STRING_HPP_

#include <string>
//SUPPRESS_UNUSED_VARIABLE_WARNING(...)
#include <preprocessor_macros/suppress_unused_variable.h>

//inline //std::string
//  //std::vector<unsigned char>
//  void getUTF8string(const std::wstring & cr_std_wstr,
//      std::vector<unsigned char> & r_std_vec_byUTF8)
//{
////  std::string std_str;
//  //see http://www.cplusplus.com/reference/string/string/begin/
//  std::wstring::const_iterator ci = cr_std_wstr.begin();
//  BYTE by;
//  while( ci != cr_std_wstr.end() )
//  {
//#ifdef _DEBUG
//    const wchar_t wch = * ci;
//    SUPPRESS_UNUSED_VARIABLE_WARNING(wch)
//#endif //#ifdef _DEBUG
//      //see http://de.wikipedia.org/wiki/UTF-8
//    if( *ci < 127 )
//      //std_str += *ci;
//      r_std_vec_byUTF8.push_back(* ci);
//    //"0000 0080 – 0000 07FF   110xxxxx 10xxxxxx"
//    else if( *ci < 0x07FF ) //7FF: 111 1111 1111bin
////      std_str +=
////        (char) ( 192 //bin: 110 00000
////            + ( *ci >> 6 )) + (char) (128 + ( *ci & 63 //bin: 111111
////            )
////          );
//    { //e.g. see http://de.wikipedia.org/wiki/UTF-8#Kodierung, table "Beispiele für UTF-8 Kodierungen": German 'ä' = dec. 228 = 00000000 11100100 bin hex 0xE4 = Unicode: U+00E4 -> to UTF-8: 11000011 10100100 bin = 0xC3 0xA4 hex
////        std_str +=
//        by = (char) ( 192 //bin: 110 00000
//            + ( * ci >> 6 )
//            );
//        r_std_vec_byUTF8.push_back(by);
////        std_str +=
//        by = (char) ( 128 + ( *ci & 63 //bin: 111111
//            )
//          );
//        r_std_vec_byUTF8.push_back(by);
//    }
//    //0000 0800 – 0000 FFFF   1110xxxx 10xxxxxx 10xxxxxx
//    else if( *ci < 0xFFFF )
//    {
////      std_str +=
////      (char)  +
//       by = 224 //bin: 1110 0000
//          + ( * ci >> 12 );
//       r_std_vec_byUTF8.push_back(by);
//       by = 128 + ( ( *ci >> 6 ) & 63 ) //bin: 111111
//         ;
//       r_std_vec_byUTF8.push_back(by);
////        (char) (
////        + (char)
//       by = 128 + ( * ci & 63 //bin: 111111
//        );
//       r_std_vec_byUTF8.push_back(by);
//    }
//    ++ ci;
//  }
////  return std_str;
//}

inline void getUTF8string_inline(const wchar_t cr_wstr [], int size,
  std::string & std_str)
{
  //see http://www.cplusplus.com/reference/string/string/begin/
//  std::wstring::const_iterator ci = cr_std_wstr.begin();
  unsigned char by;
//  while( ci != cr_std_wstr.end() )
//  wchar_t currentChar;
  wchar_t * ci = (wchar_t *) cr_wstr;
  const wchar_t * beyondLastChar = cr_wstr + size;
  while( //size
      ci < beyondLastChar)
  {
#ifdef _DEBUG
//    const wchar_t wch = * ci;
//    SUPPRESS_UNUSED_VARIABLE_WARNING(wch)
#endif //#ifdef _DEBUG
      //see http://de.wikipedia.org/wiki/UTF-8
    if( *ci < 127 )
      std_str += *ci;
    //"0000 0080 – 0000 07FF   110xxxxx 10xxxxxx"
    else if( *ci < 0x07FF ) //7FF: 111 1111 1111bin
//      std_str +=
//        (char) ( 192 //bin: 110 00000
//            + ( *ci >> 6 )) + (char) (128 + ( *ci & 63 //bin: 111111
//            )
//          );
    { //e.g. see http://de.wikipedia.org/wiki/UTF-8#Kodierung,
        //table "Beispiele für UTF-8 Kodierungen":
        //German 'ä' = dec. 228 = 00000000 11100100 bin hex 0xE4 =
        //Unicode: U+00E4 -> to UTF-8: 11000011 10100100 bin = 0xC3 0xA4 hex
        by =  ( 192 //bin: 110 00000
            + ( * ci >> 6 )
            );
        std_str += (char) by;
        by = (char) ( 128 + ( *ci & 63 //bin: 111111
            )
          );
        std_str += by;
    }
    //0000 0800 – 0000 FFFF   1110xxxx 10xxxxxx 10xxxxxx
    else if( *ci < 0xFFFF )
    {
//      std_str +=
//      (char)  +
       by = 224 //bin: 1110 0000
          + ( * ci >> 12 );
        std_str += by;
       by = 128 + ( ( *ci >> 6 ) & 63 ) //bin: 111111
         ;
       std_str += by;
//        (char) (
//        + (char)
       by = 128 + ( * ci & 63 //bin: 111111
        );
       std_str += by;
    }
    ++ ci;
//    ++ currentChar;
  }
}

inline void getUTF8string_inline(const std::wstring & cr_std_wstr,
  std::string & std_str)
{
  getUTF8string_inline(cr_std_wstr.c_str(), cr_std_wstr.length(),
    std_str);
}

inline std::string getUTF8string(const std::wstring & cr_std_wstr)
{
  std::string std_str;
  getUTF8string_inline(cr_std_wstr, std_str);
  return std_str;
}

#endif /* GETUTF8STRING_HPP_ */
