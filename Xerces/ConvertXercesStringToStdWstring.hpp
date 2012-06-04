/*
 * ConvertXercesStringToStdWstring.hpp
 *
 *  Created on: 04.04.2012
 *      Author: Stefan
 */

#ifndef CONVERTXERCESSTRINGTOSTDWSTRING_HPP_
#define CONVERTXERCESSTRINGTOSTDWSTRING_HPP_

#include <preprocessor_macros/inline.h>
#include <string> //std::wstring
#include <xercesc/util/XMLString.hpp> //XMLString::stringLen(...)

namespace Xerces
{
  //The following function because one can not always cast "XMLCh *" to
  //"wchar_t *" because "wchar_t" has 2 bytes and "XMLCh" has 4 bytes under
  //Linux.
  FORCE_INLINE std::wstring ConvertXercesStringToStdWstring_inline(
    const XMLCh * cpc_xmlch
    )
  {
    XMLSSize_t xmlssize_tStringLength = XERCES_CPP_NAMESPACE::XMLString::
      stringLen(cpc_xmlch) ;
    wchar_t arwch[ xmlssize_tStringLength + 1 ] ;
    unsigned short wIndex = 0 ;
    while( //char not NULL / no string end
      * cpc_xmlch )
    {
      arwch[ wIndex] = * cpc_xmlch ;
      ++ wIndex ;
      //Advance 1 character
      ++ cpc_xmlch ;
    }
    //Set string terminating NULL char.
    arwch[ xmlssize_tStringLength ] = L'\0' ;
    std::wstring stdwstr( arwch) ;
    return stdwstr ;
  }
  std::wstring ConvertXercesStringToStdWstring(
    const XMLCh * cpc_xmlch
    );
} //namespace Xerces

//namespace Apache_Xerces
//{
//  namespace character_string
//  {
//    std::wstring ConvertToStdWstring(
//      const XMLCh * cpc_xmlch
//      )
//    {
//      return Xerces::ConvertXercesStringToStdWstring_inline(cpc_xmlch);
//    }
//  }
//}

#endif /* CONVERTXERCESSTRINGTOSTDWSTRING_HPP_ */
