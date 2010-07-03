/*
 * XercesAttributesHelper.hpp
 *
 *  Created on: Jun 11, 2010
 *      Author: Stefan
 */

#ifndef XERCESATTRIBUTESHELPER_HPP_
#define XERCESATTRIBUTESHELPER_HPP_

#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/util/xmlstring.hpp> //for XMLString::transcode(...)
#include <string>
#include <sstream> //std::istringstream

class XercesAttributesHelper
: public  XERCES_CPP_NAMESPACE::Attributes
{
public:
  XercesAttributesHelper();

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
     //,std::ios_base& (*f)(std::ios_base&)
    ) ;
  static bool XercesAttributesHelper::getValue(
     const XERCES_CPP_NAMESPACE::Attributes & cr_xerces_attributes ,
     std::string & r_stdstrAttributeValue ,
      const   XMLCh * const    cpc_xmlchAttributeName
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
//   //,std::ios_base& (*f)(std::ios_base&)
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
template <class T>
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
template <class T>
 bool ConvertXercesAttributesValue(
  const XERCES_CPP_NAMESPACE::Attributes & cr_xerces_attributes ,
   T & r_templateType,
   const XMLCh * const cpc_xmlchAttributeName
  )
{
  const XMLCh * cp_xmlchAttributeValue = cr_xerces_attributes.getValue(// const XMLCh *const qName
    cpc_xmlchAttributeName
    //"number"
    ) ;
  //If the attribute exists.
  if(cp_xmlchAttributeValue)
  {
    char * pchAttributeValue = XERCES_CPP_NAMESPACE::XMLString::transcode(
      cp_xmlchAttributeValue) ;
    if( pchAttributeValue )
    {
        std::string strAttributeValue = std::string(pchAttributeValue);
        std::istringstream iss(strAttributeValue);
        //Release memory of dyn. alloc. buffer (else memory leaks).
        XERCES_CPP_NAMESPACE::XMLString::release(&pchAttributeValue);
        return !(iss //>> f
          >> r_templateType
          ).fail();
    }
    //      else
    //        byReturn = XERCES_ATTRIBUTE_VALUE_DOES_NOT_EXIST ;
//        else
//          byReturn = XERCES_ERROR_CONVERTING_ATTRIBUTE_VALUE_TO_C_STRING ;
  }
  return false ;
}

#endif /* XERCESATTRIBUTESHELPER_HPP_ */
