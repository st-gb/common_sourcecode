/**(c)from 2009 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
 * Created 15Nov2009,18:53
 * @author Stefan Gebauer(TU Berlin matriculation number 361095)*/

///Include guard,see http://en.wikipedia.org/wiki/Include_guard :

/**Bln=BerLiN:http://www.acronymfinder.com/Berlin-(Bln).html
 * Prgm=PRaGMa
 * Incl=INCLude:http://www.abbreviations.com/abbreviation/include
 * Grd=GuaRD:http://www.abbreviations.com/abbreviation/guard */
#ifdef TU_Bln361095usePrgmInclGrd
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
  #pragma once
#endif
#if defined TU_Bln361095usePrgmInclGrd ||\
/**Include guard supported by (nearly) all compilers*/\
/**Bln=BerLiN:https://www.acronymfinder.com/Berlin-(Bln).html
 * cmn=CoMmoN:http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe:http://www.abbreviations.com/abbreviation/Source
 * char=CHARacter: http://www.abbreviations.com/abbreviation/CHARacter
 * Str=STRing: http://www.abbreviations.com/abbreviation/string*/\
 ! defined TU_Bln361095cmnSrc_wxWidgets_charStr_wxStringHelper_h
   #define TU_Bln361095cmnSrc_wxWidgets_charStr_wxStringHelper_h

///Standard C(++) library header files:
#include <string>///class std::string

///wxWidgets header files:
#include <wx/string.h>///class wxString

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
#include <dataType/charStr/stdtstr.hpp>///class std::tstring
#include <preprocessor_macros/string_typedefs.h> //LPCSTR

namespace TU_Bln361095{namespace wxWidgets
{
  wxString getwxString(const char * const str );
  wxString getwxString(const std::string & str );

  //wxString getwxString(std::tstring & tstr ) ;
  wxString getwxString(const std::wstring & stdwstr ) ;
  inline wxString GetwxString_inln(const std::wstring & cr_stdwstr)
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

  inline wxString GetwxString_inln( LPCSTR lpcstr )
  {
    //from http://wiki.wxwidgets.org/Converting_everything_to_and_from_wxString#
    // std::string_to_wxString
     wxString wxstr(lpcstr, wxConvUTF8);
    return wxstr ;
  }
  inline wxString GetwxString_inln(const std::string & str )
  {
    return GetwxString_inln(str.c_str() ) ;
  }

  std::string GetStdString(const wxString & wxstr) ;
  inline std::string GetStdString_inln(const wxString & cr_wxstr)
  {
    std::string std_str = std::string( cr_wxstr.mb_str() );
    return std_str ;
  }
  inline std::wstring GetStdWstring_inln(const wxString & cr_wxstr)
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
}}

#endif///include guard