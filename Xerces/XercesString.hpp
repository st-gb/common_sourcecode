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

namespace Xerces
{
  //from Xerces sourcecode (CreateDOMDocument sample, CreateDOMDocument.cpp) :
  // ---------------------------------------------------------------------------
  //  This is a simple class that lets us do easy (though not terribly efficient)
  //  trancoding of char* data to XMLCh data.
  // ---------------------------------------------------------------------------
  class XercesString
  {
  public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    XercesString(const char * const toTranscode)
    {
      // Call the private transcoding method
      fUnicodeForm = XERCES_CPP_NAMESPACE::XMLString::transcode(toTranscode);
    }

    ~XercesString()
    {
      XERCES_CPP_NAMESPACE::XMLString::release(&fUnicodeForm);
    }
    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    const XMLCh * unicodeForm() const
    {
      return fUnicodeForm;
    }
  private :
    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fUnicodeForm
    //      This is the Unicode XMLCh format of the string.
    // -----------------------------------------------------------------------
    XMLCh * fUnicodeForm;
  };
  #define XERCES_STRING_FROM_ANSI_STRING(str) \
Xerces::XercesString(str).unicodeForm()
//  class XercesString
//  {
//  public:
//    XercesString();
//    virtual
//    ~XercesString();
//  };
//  static
  std::string ToStdString(
    const XMLCh * p_xmlch
    ) ;
}

#endif /* XERCESSTRING_HPP_ */
