/*
 * GetErrorDescripton.hpp
 *
 *  Created on: 30.11.2013
 *      Author: mr.sys
 */

#ifndef GETERRORDESCRIPTON_HPP_
#define GETERRORDESCRIPTON_HPP_

#include <xercesc/util/Xerces_autoconf_config.hpp> //XMLFileLoc, XMLCh
#include <string> //std::wstring
#include <Xerces/XercesString.hpp> //GET_WCHAR_STRING_FROM_XERCES_STRING(...)

namespace Xerces
{
  std::wstring GetErrorDescription(
    const XMLFileLoc & xmlfilelocColumnNumber,
    const XMLFileLoc & xmlfilelocLineNumber,
    const XMLCh * SystemId,
    const XERCES_CPP_NAMESPACE::SAXParseException & cr_saxparseexception
    )
  {
    std::wstring stdwstrInputSourceName =
      GET_WCHAR_STRING_FROM_XERCES_STRING(SystemId);
    std::wstring stdwstrMessage = L"SAX parse exception in document \""
      + stdwstrInputSourceName
      + L"\"\n"
      L"in line " + convertToStdWstring( xmlfilelocLineNumber )
      + L", column " + convertToStdWstring(xmlfilelocColumnNumber )
      + L":\n\"" +
      GET_WCHAR_STRING_FROM_XERCES_STRING(cr_saxparseexception.getMessage() )
      ;
    if( ! xmlfilelocColumnNumber && ! xmlfilelocLineNumber)
    {
      stdwstrMessage += L"\n\nThis probably means that this document/ file does "
        "not exist";
    }
    stdwstrMessage += L"\n\n"//"Sorry, no further information.\n"
      "In order to solve "
      "this problem you may look into the XML specifications for element names "
      "etc.";
    return stdwstrMessage;
  }
}

#endif /* GETERRORDESCRIPTON_HPP_ */
