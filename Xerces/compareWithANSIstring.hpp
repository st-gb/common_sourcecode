/*
 * compareWithANSIstring.hpp
 *
 *  Created on: 04.04.2012
 *      Author: Stefan
 */

#ifndef COMPAREWITHANSISTRING_HPP_
#define COMPAREWITHANSISTRING_HPP_

  inline int ansi_string_compare(
    const XMLCh * cpc_xmlch,
    const char * cpc_ch
    )
  {
    while( //char not NULL / no string end
      * cpc_xmlch && * cpc_ch )
    {
      if( * cpc_xmlch != * cpc_ch )
        return 1 ;
      //Advance 1 character
      ++ cpc_xmlch ;
      ++ cpc_ch ;
    }
    if( ! * cpc_xmlch && ! * cpc_ch  )
      return //n ;
        0 ;
    return 1 ;
  }

  //@return 0=strings equal.
  inline int ansi_or_wchar_string_compare(
//    const XMLCh * const cpc_xmlch,
//    const char * const cpc_ch
    const XMLCh * cpc_xmlch,
    const char * cpc_ch
    )
  {
//    #ifdef __linux__//wcscmp(...) does not work correctly under Linux->strcmp(...)
//      char * p_ch = XERCES_CPP_NAMESPACE::XMLString::transcode(cpc_xmlch) ;
//      int n = strcmp(p_ch, cpc_ch ) ;
//      XERCES_CPP_NAMESPACE::XMLString::release( & p_ch ) ;
//      int n ;
    return ansi_string_compare(cpc_xmlch, cpc_ch);
    //  #else //#ifdef __linux__
    //    /If strings equal.
    //  return wcscmp(
    //    //Explicitly cast to "wchar_t *" to avoid Linux g++ warning.
    //    (wchar_t *) cpc_xmlch, cpc_wch ) ;
//    #else
//      return 1 ;
//    #endif //#ifdef __linux__
  } //inline int ansi_or_wchar_string_compare(...)


#endif /* COMPAREWITHANSISTRING_HPP_ */
