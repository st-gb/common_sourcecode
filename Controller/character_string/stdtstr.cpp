//#ifdef _MSC_VER
//  #include "stdafx.h"
//#endif//#ifdef _MSC_VER

#include "stdtstr.hpp"
#include <preprocessor_macros/string_typedefs.h> //LPCWSTR

 #if defined _UNICODE || defined UNICODE

 std::tstring operator + (
  const std::tstring & r_tstring,
   const std::string & r_string
  )
 {
   std::tstring tstr = r_tstring + std::wstring( r_string.begin(),
     r_string.end() ) ;
   return tstr ;
 }

 std::tstring Getstdtstring(const std::string & cr_str )
 {
   std::wstring wstr( cr_str.begin(), cr_str.end() ) ;
   return wstr ;
 }
 std::tstring Getstdtstring(const std::wstring & cr_wstr )
 {
   return cr_wstr ;
 }
// tstring::tstring( TCHAR * ptch )
// {
//   wstring()
// }

 #else //#if defined _UNICODE || defined UNICODE
 std::tstring Getstdtstring(const std::string & cr_str )
 {
   return cr_str ;
 }
 std::tstring Getstdtstring(const std::wstring & cr_wstr )
 {
   std::string stdstr( cr_wstr.begin(), cr_wstr.end() ) ;
   return stdstr ;
 }
 #endif //#if defined _UNICODE || defined UNICODE

 std::wstring GetStdWstring( LPCWSTR cp_lpwstr )
 {
   return std::wstring(cp_lpwstr);
 }

 std::wstring GetStdWstring( const std::wstring & cr_wstr )
 {
   return cr_wstr ;
 }

 std::wstring GetStdWstring( const std::string & cr_str )
 {
   std::wstring wstr( cr_str.begin(), cr_str.end() ) ;
   return wstr ;
 }

 std::string GetStdString(const std::string & cr_str )
 {
   return cr_str ;
 }
 std::string GetStdString(const std::wstring & cr_wstr )
 {
//   std::string stdstr( cr_wstr.begin(), cr_wstr.end() ) ;
//   return stdstr ;
   return GetStdString_Inline( cr_wstr) ;
 }
 //Let newline below to avoid g++ warning "no newline at end of file".
