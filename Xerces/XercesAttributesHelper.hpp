/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */
/*
 * XercesAttributesHelper.hpp
 *
 *  Created on: Jun 11, 2010
 *      Author: Stefan
 */

#ifndef XERCESATTRIBUTESHELPER_HPP_
#define XERCESATTRIBUTESHELPER_HPP_

//for XERCES_CPP_NAMESPACE::Attributes for function defined in _this_ file
#include <xercesc/sax2/Attributes.hpp>
//for XERCES_CPP_NAMESPACE::XMLString::transcode(...)
#include <xercesc/util/XMLString.hpp>
#include <string> //std::string
#include <sstream> //std::istringstream
#include <windef.h> //for BYTE

#define XERCES_ATTRIBUTE_VALUE_INVALID_DATA_FORMAT 2
#define XERCES_ERROR_GETTING_ATTRIBUTE_NAME 3
#define XERCES_ERROR_CONVERTING_ATTRIBUTE_VALUE_TO_C_STRING 4
#define XERCES_ATTRIBUTE_VALUE_DOES_NOT_EXIST 5
#define XERCES_ERROR_CONVERTING_ATTRIBUTE_NAME_TO_XERCES_STRING 6

//#define SUCCESS 1
//#define FAILURE 0

class XercesAttributesHelper
//  : public XERCES_CPP_NAMESPACE::Attributes
{
public:
  XercesAttributesHelper();
  enum return_codes
  {
    getting_attribute_value_failed = 0 ,
    getting_attribute_value_succeeded = 1
  };
  //_Must_ be _defined_ here because of the template type: the templates type gets
  // replaced by the actual data type. When the declaration is separated from
  // the definition (what it usual) the template type is replaced by the actual
  //parameter, but the definition's template type is _not_ being replaced.
  //So it gets an error message like
  //"undefined reference to `bool XercesAttributesHelper::getValue<std::string>
  //(std::string&, char*) const'"
  //Also see here: http://www.codeproject.com/KB/cpp/templatesourceorg.aspx
//  template <class T>
//  bool getValue(
//     T & r_templateType,
////     const std::string & r_stdstr
//     char * const lpctstrAttrName
//     ) const
//  {
//    //DEBUG("from_string:%s\n",s);
//  //  LOG("from_string:" << s << "\n" );
//  //  char * message = XMLString::transcode(localname);
//    XMLCh * p_xmlchAttributeName = XERCES_CPP_NAMESPACE::XMLString::transcode(
//      lpctstrAttrName) ;
//    if( p_xmlchAttributeName )
//    {
//        const XMLCh * cp_xmlchAttributeValue =
//            XERCES_CPP_NAMESPACE::Attributes::getValue(// const XMLCh *const qName
//          p_xmlchAttributeName
//          //"number"
//          ) ;
//        //If the attribute exists.
//        if(cp_xmlchAttributeValue)
//        {
//          char * pchAttributeValue = XERCES_CPP_NAMESPACE::XMLString::transcode(
//            cp_xmlchAttributeValue) ;
//          if( pchAttributeValue )
//          {
//              std::string strAttributeValue = std::string(pchAttributeValue);
//
//              std::istringstream iss(strAttributeValue);
//              return !(iss //>> f
//                >> r_templateType
//                ).fail();
//
//              //Release memory of dyn. alloc. buffer (else memory leaks).
//              XERCES_CPP_NAMESPACE::XMLString::release(&pchAttributeValue);
//          }
//  //        else
//  //          byReturn = XERCES_ERROR_CONVERTING_ATTRIBUTE_VALUE_TO_C_STRING ;
//        }
//  //      else
//  //        byReturn = XERCES_ATTRIBUTE_VALUE_DOES_NOT_EXIST ;
//        //Release memory of dyn. alloc. buffer (else memory leaks).
//        XERCES_CPP_NAMESPACE::XMLString::release(&p_xmlchAttributeName);
//    }
//    return false ;
//  }
  static BYTE GetAttributeValue(
    const XERCES_CPP_NAMESPACE::Attributes & attrs,
    const char * pc_chAttributeName,
    bool & rbValue
    ) ;
  static //inline
    BYTE GetAttributeValue
    (
    const XERCES_CPP_NAMESPACE::Attributes & xercesc_attributes,
    const std::string & cr_stdstrAttributeName,
    std::string & r_strValue
    ) ;
  static BYTE GetAttributeValue(
    const XERCES_CPP_NAMESPACE::Attributes & attrs,
    char * lpctstrAttrName,
    BYTE & rbyValue
    ) ;
  BYTE GetAttributeValue(
    const XERCES_CPP_NAMESPACE::Attributes & attrs,
    const char * lpctstrAttrName,
    //DWORD & r_dwValue
    //StdStringToDestFormat & r_stdstringtodestformat ,
    BYTE ( * pfn)(
      std::string & strAttributeValue ,
      void * pv_AttributeValue ) ,
    //PVOID
    void * pv_AttributeValue
    ) ;
  //Decrease code redundancy:
  //This function has the code to get the Xerces attribute value
  //that should be identical for all data types and calls the
  //converter functions (member functions of this class).
  //For possibility to interact with the user interface in case of convert errors
  //the converter functions are member functions and so they have
  //the user interface member variable.
  BYTE GetAttributeValue(
    const XERCES_CPP_NAMESPACE::Attributes & attrs,
    const char * lpctstrAttrName,
    //DWORD & r_dwValue
    //StdStringToDestFormat & r_stdstringtodestformat ,
    BYTE ( XercesAttributesHelper::*pfn )(
      //const XercesHelper * cp_xerceshelper ,
      std::string & strAttributeValue ,
      void * pv_AttributeValue ) ,
    //const XercesHelper * cp_xerceshelper ,
    //PVOID
    void * pv_AttributeValue
    ) ;
  static BYTE GetAttributeValue(
    const XERCES_CPP_NAMESPACE::Attributes & attrs,
    const char * lpctstrAttrName,
    WORD & rwValue
    ) ;
  //static
  BYTE GetAttributeValue(
    const XERCES_CPP_NAMESPACE::Attributes & attrs,
    const char * lpctstrAttrName,
    DWORD & r_dwValue) ;
  static BYTE GetAttributeValue(
    const XERCES_CPP_NAMESPACE::Attributes & attrs,
    const char * lpctstrAttrName,
    float & rfValue
    ) ;
  static BYTE GetAttributeValue(
    const XERCES_CPP_NAMESPACE::Attributes & attrs,
    const char * lpcstrAttrName,
//    std::string & r_stdstrAttributeName ,
    std::string & r_strValue
    ) ;
  static BYTE GetAttributeValue
    (
    const XERCES_CPP_NAMESPACE::Attributes & attrs,
    const char * lpctstrAttrName,
    std::wstring & r_stdwstrValue
    ) ;
  //template idea for converting string to other data type
  //from http://www.codeguru.com/forum/showthread.php?t=231056:
//  template <class T>
  static bool getValue(
    const XERCES_CPP_NAMESPACE::Attributes & cr_xerces_attributes ,
//     T & r_templateType,
    std::string & r_stdstrAttributeValue ,
  //   const std::string & r_stdstr
    const char * const lpctstrAttrName
//     const   XMLCh * const    cpc_xmlchLocalName
    ) ;
//  static bool getValue(
//     const XERCES_CPP_NAMESPACE::Attributes & cr_xerces_attributes ,
//     std::string & r_stdstrAttributeValue ,
//     //   Under Linux XMLCh may be defined as "uint16_t".
////     const   XMLCh * const    cpc_xmlchAttributeName
//     const wchar_t * const cpc_xmlchAttributeName
//    ) ;
  BYTE ToDWORD(
    std::string & strAttributeValue ,
    void * pv_AttributeValue
    ) ;
  virtual
  ~XercesAttributesHelper();
};

////template idea for converting string to other data type
////from http://www.codeguru.com/forum/showthread.php?t=231056:
//template <class T>
//static bool ConvertXercesAttributesValue(
////  const XERCES_CPP_NAMESPACE::Attributes & cr_xerces_attributes ,
//   T & r_templateType,
////   const std::string & r_stdstr
////   char * const lpctstrAttrName
//   const std::string & r_stdstr
//  ) ;

//template idea for converting string to other data type
//from http://www.codeguru.com/forum/showthread.php?t=231056:
//_Must_ be _defined_ here because of the template type: the templates type gets
// replaced by the actual data type. When the declaration is separated from
// the definition (what it usual) the template type is replaced by the actual
//parameter, but the definition's template type is _not_ being replaced.
//So it gets an error message like
//"undefined reference to `bool XercesAttributesHelper::getValue<std::string>
//(std::string&, char*) const'"
//Also see here: http://www.codeproject.com/KB/cpp/templatesourceorg.aspx
template <typename T>
 bool ConvertXercesAttributesValue(
  const XERCES_CPP_NAMESPACE::Attributes & cr_xerces_attributes ,
   T & r_templateType,
   const XMLCh * const cpc_xmlchAttributeName
  )
{
  const XMLCh * cp_xmlchAttributeValue = cr_xerces_attributes.getValue(
    // const XMLCh *const qName
    cpc_xmlchAttributeName
    //"number"
    ) ;
  //If the attribute exists.
  if(cp_xmlchAttributeValue)
  {
    //Must convert to "char *" because MinGW can't use std::wistringstream.
    char * pchAttributeValue = XERCES_CPP_NAMESPACE::XMLString::transcode(
      cp_xmlchAttributeValue) ;
    if( pchAttributeValue )
    {
        std::string strAttributeValue = std::string(pchAttributeValue);
        std::istringstream iss(strAttributeValue);

        //atof returned 1 for "1.2" on Linux on German because the decimal
        //point is a "," in German.
        //http://stackoverflow.com/questions/1333451/c-locale-independent-atof:
        //"localeconv (in <locale.h>) returns a pointer to struct whose
        //decimal_point member contains that value. Note that the pointer
        //is valid until the next localeconv() or setlocale() – "
        //fAtofResult = (float) atof(pchAttributeValue ) ;

        //Ensure a "." is interpreted as decimal point no matter what the
        //current locale is.
        iss.imbue( std::locale("C") );

        //Release memory of dyn. alloc. buffer (else memory leaks).
        XERCES_CPP_NAMESPACE::XMLString::release(&pchAttributeValue);
//        return ! ( iss //>> f
//          >> r_templateType
//          ).fail();
        bool b = ! ( iss //>> f
            >> r_templateType
            ).fail();
        return b;
    }
    //      else
    //        byReturn = XERCES_ATTRIBUTE_VALUE_DOES_NOT_EXIST ;
//        else
//          byReturn = XERCES_ERROR_CONVERTING_ATTRIBUTE_VALUE_TO_C_STRING ;
  }
  return false ;
}

//template idea for converting string to other data type
//from http://www.codeguru.com/forum/showthread.php?t=231056:
//_Must_ be _defined_ here because of the template type: the templates type gets
// replaced by the actual data type. When the declaration is separated from
// the definition (what it usual) the template type is replaced by the actual
//parameter, but the definition's template type is _not_ being replaced.
//So it gets an error message like
//"undefined reference to `bool XercesAttributesHelper::getValue<std::string>
//(std::string&, char*) const'"
//Also see here: http://www.codeproject.com/KB/cpp/templatesourceorg.aspx
template <typename T>
 bool ConvertXercesAttributesValue(
  const XERCES_CPP_NAMESPACE::Attributes & cr_xerces_attributes ,
   T & r_templateType,
//   const std::string & r_stdstr
//   char * const lpctstrAttrName
   const std::string & r_stdstrAttributeName
   //,std::ios_base& (*f)(std::ios_base&)
  )
{

  XMLCh * p_xmlchAttributeName = XERCES_CPP_NAMESPACE::XMLString::transcode(
    //lpctstrAttrName
    r_stdstrAttributeName.c_str()
    ) ;
  if( p_xmlchAttributeName )
  {
    return ConvertXercesAttributesValue(
      cr_xerces_attributes ,
      r_templateType
      , p_xmlchAttributeName
      ) ;
    //Release memory of dyn. alloc. buffer (else memory leaks).
    XERCES_CPP_NAMESPACE::XMLString::release(&p_xmlchAttributeName);
  }
  return false ;
}

template <typename T>
  bool ConvertXercesAttributesValue(
    const XERCES_CPP_NAMESPACE::Attributes & cr_xerces_attributes ,
    //   const std::string & r_stdstr
    //   char * const lpctstrAttrName
    const std::string & r_stdstrAttributeName ,
    T & r_templateType
    //,std::ios_base& (*f)(std::ios_base&)
  )
{

  XMLCh * p_xmlchAttributeName = XERCES_CPP_NAMESPACE::XMLString::transcode(
    //lpctstrAttrName
    r_stdstrAttributeName.c_str()
    ) ;
  if( p_xmlchAttributeName )
  {
    return ConvertXercesAttributesValue(
      cr_xerces_attributes ,
      r_templateType
      , p_xmlchAttributeName
      ) ;
    //Release memory of dyn. alloc. buffer (else memory leaks).
    XERCES_CPP_NAMESPACE::XMLString::release(&p_xmlchAttributeName);
  }
  return false ;
}

#endif /* XERCESATTRIBUTESHELPER_HPP_ */
