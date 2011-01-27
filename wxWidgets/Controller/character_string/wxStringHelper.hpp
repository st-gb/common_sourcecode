/* 
 * File:   wxStringHelper.h
 * Author: sgebauer
 *
 * Created on 15. November 2009, 18:53
 */

#ifndef _WXSTRINGHELPER_H
#define	_WXSTRINGHELPER_H

#include <string> //class std::string
#include <wx/string.h> //wxString
#include <Controller/character_string/stdtstr.hpp> //class std::tstring
//#include <winnt.h> //LPCSTR
#include <preprocessor_macros/string_typedefs.h> //LPCSTR

wxString getwxString(const std::string & str ) ;
//wxString getwxString(std::tstring & tstr ) ;
wxString getwxString(const std::wstring & stdwstr ) ;
inline wxString GetwxString_Inline( LPCSTR lpcstr )
{
  //from http://wiki.wxwidgets.org/Converting_everything_to_and_from_wxString#
  // std::string_to_wxString
   wxString wxstr(lpcstr, wxConvUTF8);
  return  wxstr ;
}

std::string GetStdString(const wxString & wxstr) ;
std::wstring GetStdWstring(const wxString & cr_wxstr) ;

inline std::tstring GetStdTstring_Inline( wxString & r_wxstr)
{
#if defined _UNICODE || defined UNICODE
  std::wstring stdwstr = std::wstring( r_wxstr );
  return stdwstr ;
#else
  std::string stdstr = std::string( r_wxstr.mb_str() );
  return stdstr ;
#endif
}

#endif	/* _WXSTRINGHELPER_H */

