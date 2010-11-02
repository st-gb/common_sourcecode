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
  //The following function because one can not always cast "XMLCh *" to
  //"wchar_t *" because "wchar_t" has 2 bytes and "XMLCh" has 4 bytes under
  //Linux.
  inline std::wstring ConvertXercesStringToStdWstring(
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
    arwch[ xmlssize_tStringLength ] = 0 ;
    std::wstring stdwstr( arwch) ;
    return stdwstr ;
  }
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
    Xerces::ConvertXercesStringToStdWstring(xml_ch_pointer_string) ;
  #define XERCES_STRING_FROM_WCHAR_T_STRING(wchar_t_pointer_string) \
    Xerces::XercesString(wchar_t_pointer_string).unicodeForm()
#endif
//  static
  std::string ToStdString(
    const XMLCh * p_xmlch
    ) ;

  //The following because: wcscmp(...) did not work correctly when compiled
  //under Linux (with "XMLCh *", probably because "XMLCh" has 4 bytes under
  //Linux).
  #ifdef __linux__
    #define ANSI_OR_WCHAR(string) string
  #else
    #define ANSI_OR_WCHAR(string) L ## string
  #endif

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
      //If strings equal.
    return wcscmp(
      //Explicitly cast to "wchar_t *" to avoid Linux g++ warning.
      (wchar_t *) cpc_xmlch, cpc_wch ) ;
    #endif //#ifdef __linux__
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
    #ifdef __linux__//wcscmp(...) does not work correctly under Linux->strcmp(...)
//      char * p_ch = XERCES_CPP_NAMESPACE::XMLString::transcode(cpc_xmlch) ;
//      int n = strcmp(p_ch, cpc_ch ) ;
//      XERCES_CPP_NAMESPACE::XMLString::release( & p_ch ) ;
//      int n ;
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
    //  #else //#ifdef __linux__
    //    /If strings equal.
    //  return wcscmp(
    //    //Explicitly cast to "wchar_t *" to avoid Linux g++ warning.
    //    (wchar_t *) cpc_xmlch, cpc_wch ) ;
    #else
      return 1 ;
    #endif //#ifdef __linux__
  } //inline int ansi_or_wchar_string_compare(...)
} //namespace Xerces

#endif /* XERCESSTRING_HPP_ */
