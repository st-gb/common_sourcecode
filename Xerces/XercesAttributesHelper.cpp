/*
 * XercesAttributesHelper.cpp
 *
 *  Created on: Jun 11, 2010
 *      Author: Stefan
 */

#include <Xerces/XercesAttributesHelper.hpp>

#include <xercesc/util/xmlstring.hpp> //for XMLString::transcode(...)
#include <sstream> //std::istringstream

XercesAttributesHelper::XercesAttributesHelper()
{
  // TODO Auto-generated constructor stub

}

XercesAttributesHelper::~XercesAttributesHelper()
{
  // TODO Auto-generated destructor stub
}

////template idea for converting string to other data type
////from http://www.codeguru.com/forum/showthread.php?t=231056:
//template <class T>
//bool XercesAttributesHelper::getValue(
//   T & r_templateType,
////   const std::string & r_stdstr
//   char * const lpctstrAttrName
//   //,std::ios_base& (*f)(std::ios_base&)
//  ) const
//{
//
//}

////template idea for converting string to other data type
////from http://www.codeguru.com/forum/showthread.php?t=231056:
//template <class T>
 bool XercesAttributesHelper::getValue(
  const XERCES_CPP_NAMESPACE::Attributes & cr_xerces_attributes ,
//   T & r_templateType,
  std::string & r_stdstrAttributeValue ,
//   const std::string & r_stdstr
  const char * const lpctstrAttrName
//   const   XMLCh * const    cpc_xmlchLocalName
   //,std::ios_base& (*f)(std::ios_base&)
  )
{

  XMLCh * p_xmlchAttributeName = XERCES_CPP_NAMESPACE::XMLString::transcode(
    lpctstrAttrName) ;
  if( p_xmlchAttributeName
      //cpc_xmlchLocalName
    )
  {
      const XMLCh * cp_xmlchAttributeValue = cr_xerces_attributes.getValue(// const XMLCh *const qName
        p_xmlchAttributeName
//        cpc_xmlchLocalName
        //"number"
        ) ;
      //If the attribute exists.
      if(cp_xmlchAttributeValue)
      {
        char * pchAttributeValue = XERCES_CPP_NAMESPACE::XMLString::transcode(
          cp_xmlchAttributeValue) ;
        if( pchAttributeValue )
        {
//            std::string strAttributeValue = std::string(pchAttributeValue);
          r_stdstrAttributeValue = std::string(pchAttributeValue);
          return true ;
//
//            std::istringstream iss(strAttributeValue);
//            return !(iss //>> f
//              >> r_templateType
//              ).fail();
//
//            //Release memory of dyn. alloc. buffer (else memory leaks).
//            XERCES_CPP_NAMESPACE::XMLString::release(&pchAttributeValue);
        }
//        else
//          byReturn = XERCES_ERROR_CONVERTING_ATTRIBUTE_VALUE_TO_C_STRING ;
      }
//      else
//        byReturn = XERCES_ATTRIBUTE_VALUE_DOES_NOT_EXIST ;
      //Release memory of dyn. alloc. buffer (else memory leaks).
      XERCES_CPP_NAMESPACE::XMLString::release(&p_xmlchAttributeName);
  }
  return false ;
}

bool XercesAttributesHelper::getValue(
   const XERCES_CPP_NAMESPACE::Attributes & cr_xerces_attributes ,
 //   T & r_templateType,
   std::string & r_stdstrAttributeValue ,
    const   XMLCh * const    cpc_xmlchAttributeName
   )
 {
   if( cpc_xmlchAttributeName
     )
   {
     const XMLCh * cp_xmlchAttributeValue = cr_xerces_attributes.getValue(// const XMLCh *const qName
       cpc_xmlchAttributeName
       ) ;
     //If the attribute exists.
     if(cp_xmlchAttributeValue)
     {
       char * pchAttributeValue = XERCES_CPP_NAMESPACE::XMLString::transcode(
         cp_xmlchAttributeValue) ;
       if( pchAttributeValue )
       {
//            std::string strAttributeValue = std::string(pchAttributeValue);
         r_stdstrAttributeValue = std::string(pchAttributeValue);
         return true ;
//
//            std::istringstream iss(strAttributeValue);
//            return !(iss //>> f
//              >> r_templateType
//              ).fail();
//
//            //Release memory of dyn. alloc. buffer (else memory leaks).
//            XERCES_CPP_NAMESPACE::XMLString::release(&pchAttributeValue);
       }
//        else
//          byReturn = XERCES_ERROR_CONVERTING_ATTRIBUTE_VALUE_TO_C_STRING ;
     }
//      else
//        byReturn = XERCES_ATTRIBUTE_VALUE_DOES_NOT_EXIST ;
   }
   return false ;
 }
