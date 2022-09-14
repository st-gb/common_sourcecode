/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */
#pragma once //Include guard.

#ifndef STDTSTR_HPP_ //Include guard.
  #define STDTSTR_HPP_

#include <string> //std::string, std::wstring
#include <string.h> //strlen(...)
#include <tchar.h> //TCHAR
//#include <tchar.h> //for TCHAR
//#include <preprocessor_macros/string_typedefs.h> //LPCTSTR, LPWSTR
//#include <winnt.h> //LPWSTR

typedef unsigned short int WORD;
//char * GetCharPointer( LPCTSTR pstr )
//{
//#ifdef UNICODE
//  std::wstring wstr ( pstr) ;
//  std::string str( wstr.begin(), wstr.end() ) ;
//  return str ;
//#else
//  return pstr ;
//#endif
//}

namespace std
{
  #if defined _UNICODE || defined UNICODE
    typedef std::wstring tstring;
  #else
    typedef std::string tstring;
  #endif
 //class tstring
 //{
 //    tstring( TCHAR * ptch ) ;
 //} ;
}

 #if defined _UNICODE || defined UNICODE
  //typedef wchar_t TCHAR;
   std::tstring operator + (
     const std::tstring & r_tstring,
     const std::string & r_string ) ;
#else
  //typedef char TCHAR;
 #endif

 std::tstring Getstdtstring(const std::string & str ) ;
 std::tstring Getstdtstring(const std::wstring & wstr ) ;

 inline wchar_t ** //GetTCHARarray_Inline
   Get_wchar_t_Array_Inline(const char ** const ar_cp_ch,
   //TODO change to fastestUnsignedDataType?
   WORD wNumberOfStrings)
 {
   wchar_t ** ar_p_tch = new wchar_t * [wNumberOfStrings];
   wchar_t * p_tchCurrentString;
//   char * p_chCurrentString;
   //TODO change to fastestUnsignedDataType?
   WORD wStringLength;
   if( ar_p_tch)
   {
     for( //e.g. for 2 elements: max. index is 1
       -- wNumberOfStrings; wNumberOfStrings < //(WORD) -1
       65535 ; -- wNumberOfStrings )
     {
       wStringLength = (WORD) strlen(ar_cp_ch[wNumberOfStrings] );
//       LOGN("ANSI char string array to wide char array--length of current "
//         "string:" << wStringLength)
       ar_p_tch[wNumberOfStrings] = new wchar_t[ wStringLength //term NULL char
         + 1 ];
       p_tchCurrentString = ar_p_tch[wNumberOfStrings];
       p_tchCurrentString[wStringLength] = L'\0';
       for( //Index for last string character/ element
         -- wStringLength; wStringLength < (WORD) -1 ; -- wStringLength)
         p_tchCurrentString[wStringLength] =
           ar_cp_ch[wNumberOfStrings][wStringLength] ;
     }
   }
   return ar_p_tch ;
 }

#if defined( _UNICODE) || defined(UNICODE)
 //TCHAR = wchar_t
 inline std::tstring GetStdTstring_Inline(const std::string & cr_str )
 {
   std::wstring wstr( cr_str.begin(), cr_str.end() ) ;
   return wstr ;
 }
 inline std::tstring GetStdTstring_Inline(const std::wstring & cr_wstr )
 {
   return cr_wstr ;
 }
 inline std::tstring GetStdTstring_Inline(const char * const cp_ch )
 {
   std::string std_str(cp_ch);
   std::wstring wstr( std_str.begin(), std_str.end() ) ;
   return wstr ;
 }
 inline TCHAR ** GetTCHARarray_Inline(const char ** const ar_cp_ch,
   //TODO change to fastestUnsignedDataType?
     WORD wNumberOfStrings)
  {
     return (TCHAR **) Get_wchar_t_Array_Inline(ar_cp_ch, wNumberOfStrings);
  }
#else //#if defined _UNICODE || defined UNICODE
 //TCHAR = char
 inline std::tstring GetStdTstring_Inline(const std::string & cr_str )
 {
   return cr_str ;
 }
 inline std::tstring GetStdTstring_Inline(const std::wstring & cr_wstr )
 {
   std::string stdstr( cr_wstr.begin(), cr_wstr.end() ) ;
   return stdstr ;
 }
 inline TCHAR ** GetTCHARarray_Inline(const char ** const ar_cp_ch /* ,
    WORD wNumberOfStrings */ )
  {
     return (TCHAR **) ar_cp_ch;
  }
#endif //#if defined _UNICODE || defined UNICODE

 inline void DeleteTCHARarray(int dwArgCount, TCHAR ** p_ptstrArgument)
 {
   if (p_ptstrArgument)
   {
     //TODO change to fastestUnsignedDataType?
     WORD wNumberOfStrings = dwArgCount;
//     LOGN("Freeing memory for array of copied or converted program arguments")
     for ( //e.g. for 2 elements: max. index is 1
         -- wNumberOfStrings; wNumberOfStrings < //(WORD) -1
         65535; -- wNumberOfStrings)
       {
//         LOGN("Freeing memory for " << GetStdString_Inline(
//             p_ptstrArgument[wNumberOfStrings]) )
         delete[] p_ptstrArgument[wNumberOfStrings];
       }
     delete[] p_ptstrArgument;
   }
 }

 //std::wstring GetStdWstring( const std::tstring & cr_stdtstr ) ;
 std::wstring GetStdWstring( const //LPWSTR
   wchar_t * cp_lpwstr ) ;
 std::wstring GetStdWstring( const std::wstring & cr_str ) ;
 std::wstring GetStdWstring( const std::string & cr_str ) ;
 std::string GetStdString(const std::string & cr_str ) ;
 std::string GetStdString(const std::wstring & cr_wstr ) ;
 std::string GetStdString(const std::wstring & cr_wstr ) ;

 //Just 1 instruction inside the function->inline does not waste space if
 //used multiple times, more performant.
 //the return string has lost information if c_r_wstr[i] is > 255
 inline std::string GetStdString_Inline(const std::wstring & c_r_wstr )
 {
   std::string std_str;
   //see http://www.cplusplus.com/reference/string/string/reserve/
   //Prevent array copies if appending and std_str.capacity() < c_r_wstr.size()
   std_str.reserve(c_r_wstr.length()
       //string terminating 0 char
       + 1 );
   const wchar_t * c_p_wch = c_r_wstr.data();
   while( * c_p_wch //++
       )
     std_str.append( 1, //Number of characters to append.
         (char) * c_p_wch ++
         );
//   std_str.append( 1, //Number of characters to append.
//       '\0');
//   return std::string( cr_wstr.begin(), cr_wstr.end() ) ;
   return std_str;
 }

// //Just 1 instruction inside the function->inline does not waste space if
// //used multiple times, more performance.
// inline std::string GetStdString_Inline(const wchar_t * & crp_wchar_t )
// {
//   return std::string( cr_wstr.begin(), cr_wstr.end() ) ;
// }
 inline std::string GetStdString_Inline(const std::string & cr_stdstr )
 {
   return cr_stdstr ;
 }
#endif //STDTSTR_HPP_
