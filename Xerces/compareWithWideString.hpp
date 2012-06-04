/*
 * compareWithWideChar.hpp
 *
 *  Created on: 04.04.2012
 *      Author: Stefan
 */

#ifndef COMPAREWITHWIDECHAR_HPP_
#define COMPAREWITHWIDECHAR_HPP_

  //@return 0=strings equal.
  inline int ansi_or_wchar_string_compare(
    const XMLCh * const cpc_xmlch,
    const wchar_t * const cpc_wch
    )
  {
    #ifdef __linux__//wcscmp(...) does not work correctly under Linux->strcmp(...)
    //    char * p_ch = XERCES_CPP_NAMESPACE::XMLString::transcode(
    //      cpc_xmlch) ;
    //    return strcmp(p_ch, ) ;
      return 1 ;
    #else //#ifdef __linux__

    //http://www.gnu.org/s/libc/manual/html_node/
    //String_002fArray-Comparison.html:
    //"If the two strings are equal, wcscmp returns 0."
    return wcscmp(
      //Explicitly cast to "wchar_t *" to avoid Linux g++ warning.
      (wchar_t *) cpc_xmlch, cpc_wch ) ;
    #endif //#ifdef __linux__
    return 1 ;
  }

#endif /* COMPAREWITHWIDECHAR_HPP_ */
