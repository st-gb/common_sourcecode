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

wxString getwxString(const std::string & str ) ;
//wxString getwxString(std::tstring & tstr ) ;
wxString getwxString(const std::wstring & stdwstr ) ;

std::string GetStdString(wxString & wxstr) ;

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

