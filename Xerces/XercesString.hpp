/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */
/*
 * XercesString.hpp
 *
 *  Created on: 30.09.2010
 *      Author: sgebauer
 */

#ifndef XERCESSTRING_HPP_
#define XERCESSTRING_HPP_

//for XERCES_CPP_NAMESPACE::XMLString::transcode(...)
#include <xercesc/util/XMLString.hpp> //XMLCh
#include <string> //class std::string
#include <wchar.h> //wcslen(...)

#include "Convert_wchar_t_StringToXercesString.hpp"
#include "ConvertXercesStringToStdWstring.hpp"
#include <preprocessor_macros/expand_and_stringify.h> //EXPAND_AND_STRINGIFY(...)

namespace Xerces
{
  //from Xerces sourcecode (CreateDOMDocument sample, CreateDOMDocument.cpp) :
  // ---------------------------------------------------------------------------
  //  This is a simple class that lets us do easy (though not terribly efficient)
  //  trancoding of char* data to XMLCh data.
  // ---------------------------------------------------------------------------
  class XercesString
  {
  private :
    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  p_xmlchAllocatedViaXerces
    //      This is the Unicode XMLCh format of the string.
    // -----------------------------------------------------------------------
    XMLCh * m_p_xmlchAllocatedViaXerces;
    XMLCh * m_p_xmlchAllocatedViaNew;
  public :
    enum { before = -1, strings_are_indentical = 0, after };
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    XercesString(const char * const toTranscode)
      : m_p_xmlchAllocatedViaNew( NULL)
    {
      // Call the private transcoding method
      m_p_xmlchAllocatedViaXerces = XERCES_CPP_NAMESPACE::XMLString::transcode(
        toTranscode);
    }
    XercesString(const wchar_t * const cpc_wchar_tToTranscode)
      : m_p_xmlchAllocatedViaXerces(NULL)
    {
      m_p_xmlchAllocatedViaNew = Convert_wchar_t_StringToXercesString(
        cpc_wchar_tToTranscode ) ;
    }

    ~XercesString()
    {
      if( m_p_xmlchAllocatedViaXerces)
        XERCES_CPP_NAMESPACE::XMLString::release(
          & m_p_xmlchAllocatedViaXerces );
      if( m_p_xmlchAllocatedViaNew )
        delete [] m_p_xmlchAllocatedViaNew ;
    }
    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    const XMLCh * unicodeForm() const
    {
      if( m_p_xmlchAllocatedViaXerces)
        return m_p_xmlchAllocatedViaXerces;
      if( m_p_xmlchAllocatedViaNew)
        return m_p_xmlchAllocatedViaNew ;
      return NULL ;
    }
  }; //class XercesString

  #define XERCES_STRING_FROM_ANSI_STRING(char_pointer_string) \
    Xerces::XercesString(char_pointer_string).unicodeForm()

//  class XercesString
//  {
//  public:
//    XercesString();
//    virtual
//    ~XercesString();
//  };

#ifdef _WIN32
//#if sizeof(XMLCh) == sizeof(wchar_t)
  #define XMLCH_SIZE_EQUALS_WCHAR_T_SIZE
#endif

#ifdef XMLCH_SIZE_EQUALS_WCHAR_T_SIZE
  #define GET_WCHAR_STRING_FROM_XERCES_STRING(xml_ch_pointer_string) \
    std::wstring( (wchar_t *) xml_ch_pointer_string )

  #define XERCES_STRING_FROM_WCHAR_T_STRING(wchar_t_pointer_string) \
  /*/Avoid g++ warning "no matching function for call to
  //‘xercesc_3_0::DOMElement::getAttribute(const wchar_t [17])’ " */ \
  (const XMLCh * ) wchar_t_pointer_string

#else //under Linux the size of wchar_t and XMLCh differs/ may differ
  #define GET_WCHAR_STRING_FROM_XERCES_STRING(xml_ch_pointer_string) \
    Xerces::ConvertXercesStringToStdWstring(xml_ch_pointer_string)

  #define XERCES_STRING_FROM_WCHAR_T_STRING(wchar_t_pointer_string) \
    Xerces::XercesString(wchar_t_pointer_string).unicodeForm()
#endif
//  static
  std::string ToStdString(
    const XMLCh * p_xmlch
    ) ;

  void ToStdString(
    const XMLCh * p_xmlch,
    std::string & r_std_strValue
    ) ;

  #include "compareWithANSIstring.hpp"
  /** The following because: wcscmp(...) did not work correctly when compiled
  * under Linux (with "XMLCh *", probably because "XMLCh" or wchar_t has 4 bytes
  * under Linux). */
  #ifdef __linux__
    #define ANSI_OR_WCHAR(string) string
  #else //Under Windows XMLCh is wchar_t
//    #define ANSI_OR_WCHAR(string) L ## EXPAND_AND_STRINGIFY(string)
    #define ANSI_OR_WCHAR(string) L ## string
    #include "compareWithWideString.hpp"
  #endif
} //namespace Xerces

#endif /* XERCESSTRING_HPP_ */
