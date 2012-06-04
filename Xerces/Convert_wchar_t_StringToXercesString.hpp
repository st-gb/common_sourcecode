/*
 * Convert_wchar_t_StringToXercesString.hpp
 *
 *  Created on: 04.04.2012
 *      Author: Stefan
 */

#ifndef CONVERT_WCHAR_T_STRINGTOXERCESSTRING_HPP_
#define CONVERT_WCHAR_T_STRINGTOXERCESSTRING_HPP_

namespace Xerces
{
  //The array returned must be deleted by the caller!
  inline XMLCh * Convert_wchar_t_StringToXercesString(
    const wchar_t * cpc_wchar_t
    )
  {
    size_t size_tStringLength = wcslen (cpc_wchar_t) ;
    XMLCh * arp_xmlch = new XMLCh[ size_tStringLength + 1 ] ;
    unsigned short wIndex = 0 ;
    while( //char not NULL / no string end
      * cpc_wchar_t )
    {
      arp_xmlch[ wIndex] = * cpc_wchar_t ;
      ++ wIndex ;
      //Advance 1 character
      ++ cpc_wchar_t ;
    }
    //Set string terminating NULL char.
    arp_xmlch[ size_tStringLength ] = 0 ;
//    std::wstring stdwstr( arwch) ;
    return arp_xmlch ;
  }
} //namespace Xerces

#endif /* CONVERT_WCHAR_T_STRINGTOXERCESSTRING_HPP_ */
