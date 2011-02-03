#pragma once //Include guard.
#ifndef STDTSTR_HPP_ //Include guard.
  #define STDTSTR_HPP_

#include <string> //std::string, std::wstring
//#include <tchar.h> //for TCHAR
//#include <preprocessor_macros/string_typedefs.h> //LPCTSTR, LPWSTR
//#include <winnt.h> //LPWSTR

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
   std::tstring operator + (
     const std::tstring & r_tstring,
     const std::string & r_string ) ;
 #endif

 std::tstring Getstdtstring(const std::string & str ) ;
 std::tstring Getstdtstring(const std::wstring & wstr ) ;

#if defined _UNICODE || defined UNICODE
 inline std::tstring GetStdTstring_Inline(const std::string & cr_str )
 {
   std::wstring wstr( cr_str.begin(), cr_str.end() ) ;
   return wstr ;
 }
 inline std::tstring GetStdTstring_Inline(const std::wstring & cr_wstr )
 {
   return cr_wstr ;
 }
#else //#if defined _UNICODE || defined UNICODE
 inline std::tstring GetStdTstring_Inline(const std::string & cr_str )
 {
   return cr_str ;
 }
 inline std::tstring GetStdTstring_Inline(const std::wstring & cr_wstr )
 {
   std::string stdstr( cr_wstr.begin(), cr_wstr.end() ) ;
   return stdstr ;
 }
#endif //#if defined _UNICODE || defined UNICODE

 //std::wstring GetStdWstring( const std::tstring & cr_stdtstr ) ;
 std::wstring GetStdWstring( const //LPWSTR
   wchar_t * cp_lpwstr ) ;
 std::wstring GetStdWstring( const std::wstring & cr_str ) ;
 std::wstring GetStdWstring( const std::string & cr_str ) ;
 std::string GetStdString(const std::string & cr_str ) ;
 std::string GetStdString(const std::wstring & cr_wstr ) ;
 std::string GetStdString(const std::wstring & cr_wstr ) ;
 //Just 1 instruction inside the function->inline does not waste space if
 //used multiple times, more performance.
 inline std::string GetStdString_Inline(const std::wstring & cr_wstr )
 {
   return std::string( cr_wstr.begin(), cr_wstr.end() ) ;
//   //from http://www.codeproject.com/KB/string/UtfConverter.aspx
//   std::string stdstr ;
//   stdstr.assign( cr_wstr.begin(), cr_wstr.end() ) ;
//   return stdstr ;
 }
 inline std::string GetStdString_Inline(const std::string & cr_stdstr )
 {
   return cr_stdstr ;
 }
#endif //STDTSTR_HPP_
