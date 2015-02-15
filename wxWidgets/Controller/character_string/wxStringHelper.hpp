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

namespace wxWidgets
{
  wxString getwxString(const char * const str );
  wxString getwxString(const std::string & str );

  //wxString getwxString(std::tstring & tstr ) ;
  wxString getwxString(const std::wstring & stdwstr ) ;
  inline wxString getwxString_inline(const std::wstring & cr_stdwstr)
  {
    //#ifdef wxUSE_WCHAR_T
    //see wx/chartype.h:wxUSE_UNICODE_WCHAR->"typedef wchar_t wxStringCharType;"
    //#ifdef wxUSE_UNICODE_WCHAR
    #if wxUSE_UNICODE == 1
      //std::wstring wstr(str.begin(), str.end() ) ;
      wxString wxstr( cr_stdwstr.c_str() ) ;
    #else
      std::string stdstr(cr_stdwstr.begin(), cr_stdwstr.end() ) ;
      wxString wxstr(( const unsigned char * ) stdstr.c_str() ) ;
    #endif
    return wxstr;
  }

  inline wxString GetwxString_Inline( LPCSTR lpcstr )
  {
    //from http://wiki.wxwidgets.org/Converting_everything_to_and_from_wxString#
    // std::string_to_wxString
     wxString wxstr(lpcstr, wxConvUTF8);
    return wxstr ;
  }
  inline wxString GetwxString_Inline( const std::string & str )
  {
    return GetwxString_Inline(str.c_str() ) ;
  }

  std::string GetStdString(const wxString & wxstr) ;
  inline std::string GetStdString_Inline(const wxString & cr_wxstr)
  {
    std::string std_str = std::string( cr_wxstr.mb_str() );
    return std_str ;
  }
  inline std::wstring GetStdWstring_Inline(const wxString & cr_wxstr)
  {
#ifdef UNICODE
    std::wstring stdwstr = std::wstring( cr_wxstr.wc_str() ) ;
#else
    //see http://wiki.wxwidgets.org/Converting_everything_to_and_from_wxString
    // #wxString_to_char.2A
    std::string stdstr = std::string( cr_wxstr.mb_str() ) ;
    std::wstring stdwstr( stdstr.begin(), stdstr.end() ) ;
#endif
    return stdwstr ;
  }
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
}

#endif	/* _WXSTRINGHELPER_H */

