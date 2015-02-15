/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany
 * ("Trilobyte SE") 2010-at least 2012.
 * You are allowed to modify and use the source code from Trilobyte SE for free
 * if you are not making profit directly or indirectly with it or its adaption.
 * Else you may contact Trilobyte SE. */
//#include <wxWidgets/wxStringHelper.h>
#include "wxStringHelper.hpp"

namespace wxWidgets
{
  wxString getwxString(const char * const str )
  {
  ////#ifdef wxUSE_WCHAR_T
  ////see wx/chartype.h:wxUSE_UNICODE_WCHAR->"typedef wchar_t wxStringCharType;"
  ////#ifdef wxUSE_UNICODE_WCHAR
  //#if wxUSE_UNICODE == 1
  //  std::wstring wstr(str.begin(), str.end() ) ;
  //  wxString wxstr( wstr.c_str() ) ;
  //#else
  //  wxString wxstr(( const unsigned char * ) str.c_str() ) ;
  //#endif

    /** from http://wiki.wxwidgets.org/Converting_everything_to_and_from_wxString#std::string_to_wxString */
    wxString wxstr(str, wxConvUTF8);
    return wxstr ;
  }

  wxString getwxString(const std::string & str )
  {
    return getwxString(str.c_str() );
  }

  //wxString getwxString(std::tstring & tstr )
  //{
  //#ifdef wxUSE_UNICODE_WCHAR
  //  std::wstring wstr(str.begin(), str.end() ) ;
  //  wxString wxstr( wstr.c_str() ) ;
  //#else
  //  wxString wxstr(( const unsigned char * ) tstr.c_str() ) ;
  //#endif
  //}

  wxString getwxString(const std::wstring & cr_stdwstr )
  {
    const wxString wxstr = getwxString_inline(cr_stdwstr);
    return wxstr;
  }

//  std::wstring GetStdWstring_Inline(const wxString & cr_wxstr)
//  {
//    //see http://wiki.wxwidgets.org/Converting_everything_to_and_from_wxString
//    // #wxString_to_wchar_t.2A:
//  #ifdef UNICODE
//    std::wstring stdwstr = std::wstring( cr_wxstr.wc_str() ) ;
//  #else
//    //see http://wiki.wxwidgets.org/Converting_everything_to_and_from_wxString
//    // #wxString_to_char.2A
//    std::string stdstr = std::string( cr_wxstr.mb_str() ) ;
//    std::wstring stdwstr( stdstr.begin(), stdstr.end() ) ;
//  #endif
//    return stdwstr ;
//  }

  std::string GetStdString(const wxString & cr_wxstr)
  {
  ////#ifdef wxUSE_WCHAR_T
  ////see wx/chartype.h:wxUSE_UNICODE_WCHAR->"typedef wchar_t wxStringCharType;"
  //#ifdef wxUSE_UNICODE_WCHAR
  //  std::wstring wstr( //(wchar_t *) //wxstr.c_str().AsWChar()
  //    //wxstr.c_str()
  //    //wc_str() returns wchar_t no matter if wxString uses "char" or "wchar_t".
  //    wxstr.wc_str()
  //    ) ;
  //  std::string str(wstr.begin(), wstr.end() ) ;
  //#else
  //  std::string str(( const char * ) wxstr.c_str() ) ;
  //#endif
    //from http://wiki.wxwidgets.org/Converting_everything_to_and_from_wxString#
    //  wxString_to_std::string:
    std::string str = std::string( cr_wxstr.mb_str() );
   return str ;
  }
}

