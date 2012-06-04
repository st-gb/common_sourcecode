/*
 * DocumentLocationSAX2Handler.hpp
 *
 *  Created on: 12.05.2012
 *      Author: Stefan
 */

#ifndef DOCUMENTLOCATIONSAX2HANDLER_HPP_
#define DOCUMENTLOCATIONSAX2HANDLER_HPP_

//class "XERCES_CPP_NAMESPACE::Attributes"
#include <xercesc/sax2/Attributes.hpp>
//class "XERCES_CPP_NAMESPACE::DefaultHandler
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/sax/Locator.hpp> //class XERCES_CPP_NAMESPACE::Locator

//convertFromAndToStdString(...)
#include <Controller/character_string/convertFromAndToStdString.hpp>
#include <Controller/character_string/stdtstr.hpp> //GetStdWstring(...)

#include <Xerces/XercesString.hpp> //Xerces::ToStdString
//ConvertXercesStringToStdWstring(.
#include <Xerces/ConvertXercesStringToStdWstring.hpp>

namespace Apache_Xerces
{
  class DocumentLocationSAX2Handler
    : public XERCES_CPP_NAMESPACE::DefaultHandler
  {
  protected:
    const XERCES_CPP_NAMESPACE::Locator * m_c_p_c_locator;
  public:
    DocumentLocationSAX2Handler();
    virtual
    ~DocumentLocationSAX2Handler();

    std::string GetColumnNumber()
    {
      return convertToStdString<XMLFileLoc>(m_c_p_c_locator->getColumnNumber()
        );
    }
    std::string GetLineNumber()
    {
      return convertToStdString<XMLFileLoc>(m_c_p_c_locator->getLineNumber()
        );
    }
    void GetDocumentIDandLocation(
//      const char * const cpc_chMessage,
      std::wstring & r_std_wstrDocumentIDandLocation
      )
    {
      r_std_wstrDocumentIDandLocation =
        L"\nIt is referenced in document\n"
//        + Xerces::ToStdString( m_c_p_c_locator->getSystemId() )
        + //Xerces::ConvertXercesStringToStdWstring( m_c_p_c_locator->getSystemId() )
        GET_WCHAR_STRING_FROM_XERCES_STRING( m_c_p_c_locator->getSystemId() )
        + L"\nin line:" + GetStdWstring( GetLineNumber() )
        + L", column:" + GetStdWstring( GetColumnNumber() )
        ;
    }
    void setDocumentLocator(
      const XERCES_CPP_NAMESPACE::Locator * const cpc_locator )
    {
      m_c_p_c_locator = cpc_locator ;
    }
  };
} /* namespace Apache_Xerces */
#endif /* DOCUMENTLOCATIONSAX2HANDLER_HPP_ */
