/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */
/*
 * XercesAttributesHelper.cpp
 *
 *  Created on: Jun 11, 2010
 *      Author: Stefan
 */
//for template_character_type_string_compare(...)
#include <Controller/character_string/generic_string_compare.hpp>
#include <preprocessor_macros/logging_preprocessor_macros.h> //LOGN(...)
#include <Xerces/XercesAttributesHelper.hpp>
#include <Xerces/XercesString.hpp>//Xerces::ConvertXercesStringToStdWstring(...)

////for XERCES_CPP_NAMESPACE::Attributes
//#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/util/XMLString.hpp> //for XMLString::transcode(...)

#include <errno.h> //for "errno", ERANGE
#include <limits.h> //ULONG_MAX
//#include <asm-generic/errno-base.h> // ERANGE
#include <sstream> //std::istringstream

//extern int errno;
#define SUCCESS 1
#define FAILURE 0

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
  )
{
  XMLCh * p_xmlchAttributeName = XERCES_CPP_NAMESPACE::XMLString::transcode(
    lpctstrAttrName) ;
  if( p_xmlchAttributeName
      //cpc_xmlchLocalName
    )
  {
    const XMLCh * cp_xmlchAttributeValue = cr_xerces_attributes.getValue(
      // const XMLCh *const qName
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

//bool XercesAttributesHelper::getValue(
//   const XERCES_CPP_NAMESPACE::Attributes & cr_xerces_attributes ,
// //   T & r_templateType,
//   std::string & r_stdstrAttributeValue ,
////   Under Linux XMLCh may be defined as "uint16_t".
////    const XMLCh * const cpc_xmlchAttributeName
//    const wchar_t * const cpc_wchAttributeName
//   )
// {
//   if( cpc_wchAttributeName
//     )
//   {
//     const XMLCh * cp_xmlchAttributeValue = cr_xerces_attributes.getValue(
//       // const XMLCh *const qName
//       cpc_wchAttributeName
//       ) ;
//     //If the attribute exists.
//     if(cp_xmlchAttributeValue)
//     {
//       char * pchAttributeValue = XERCES_CPP_NAMESPACE::XMLString::transcode(
//         cp_xmlchAttributeValue) ;
//       if( pchAttributeValue )
//       {
////            std::string strAttributeValue = std::string(pchAttributeValue);
//         r_stdstrAttributeValue = std::string(pchAttributeValue);
//         return true ;
////
////            std::istringstream iss(strAttributeValue);
////            return !(iss //>> f
////              >> r_templateType
////              ).fail();
////
////            //Release memory of dyn. alloc. buffer (else memory leaks).
////            XERCES_CPP_NAMESPACE::XMLString::release(&pchAttributeValue);
//       }
////        else
////          byReturn = XERCES_ERROR_CONVERTING_ATTRIBUTE_VALUE_TO_C_STRING ;
//     }
////      else
////        byReturn = XERCES_ATTRIBUTE_VALUE_DOES_NOT_EXIST ;
//   }
//   return false ;
// }

BYTE XercesAttributesHelper::GetAttributeValue(
  const XERCES_CPP_NAMESPACE::Attributes & cr_xercesc_attributes,
  const char * pc_chAttributeName,
  bool & rbValue
  )
{
  BYTE byReturn = //FAILURE;
    getting_attribute_value_failed;
  //Cast to XMLCh for "Attributes::getValue(...)".
  XMLCh * p_xmlchAttributeName = XERCES_CPP_NAMESPACE::XMLString::transcode(
    pc_chAttributeName) ;
  if( p_xmlchAttributeName )
  {
    const XMLCh * cp_xmlchAttributeValue = cr_xercesc_attributes.getValue(
      // const XMLCh *const qName
      p_xmlchAttributeName
      //"number"
      ) ;
    //If the attribute exists.
    if(cp_xmlchAttributeValue)
    {
      //"wcscmp(...)" does not work with "XMLCh *" under Linux (because it 
      //has 4 bytes under Linux and wcscmp(...) needs 2 bytes per character)?
      //->I want to use a code that avoid a transcoding of "XMLCh" to "char"
      //under Linux:
      if( CharacterString::template_character_type_string_compare(
          cp_xmlchAttributeValue,
          "true" ) == CharacterString::both_strings_equal
        )
      {
        rbValue = true;
        byReturn = //SUCCESS;
          getting_attribute_value_succeeded;
      }
      else if( CharacterString::template_character_type_string_compare(
          cp_xmlchAttributeValue,
          "false" ) == CharacterString::both_strings_equal
        )
      {
        rbValue = false;
        byReturn = //SUCCESS;
          getting_attribute_value_succeeded;
      }
    }//if(cp_xmlchAttributeValue)
    //Release memory of dyn. alloc. buffer (else memory leaks).
    XERCES_CPP_NAMESPACE::XMLString::release(&p_xmlchAttributeName);
  }
  return byReturn ;
}

BYTE XercesAttributesHelper::GetAttributeValue(
  const XERCES_CPP_NAMESPACE::Attributes & attrs,
  char * lpctstrAttrName,
  BYTE & rbyValue
  )
{
  BYTE byReturn = //FAILURE;
    getting_attribute_value_failed;
  XMLCh * p_xmlchAttributeName = XERCES_CPP_NAMESPACE::XMLString::transcode(
    lpctstrAttrName) ;
  if( p_xmlchAttributeName )
  {
    const XMLCh * cp_xmlchAttributeValue = attrs.getValue(
      // const XMLCh *const qName
      p_xmlchAttributeName
      //"number"
      ) ;
    //If the attribute exists.
    if(cp_xmlchAttributeValue)
    {
      char * pchAttributeValue = XERCES_CPP_NAMESPACE::XMLString::transcode(
        cp_xmlchAttributeValue) ;
      if( pchAttributeValue )
      {
        int nAtoiResult ;
        //"casting" to a std::string is not really necessary, but I
        //want to avoid the C-function "strcmp".
        std::string strAttributeValue = std::string(pchAttributeValue);
        if(
            //atoi(pchNumber) <> 0: If pchNumber is a valid number.
            ( nAtoiResult = atoi(pchAttributeValue ) )
            //Because atoi(...) returns "0" also for errors.
          ||
            //By using "(...)": avoid Linux g++ warning
            // "suggest parentheses around ‘&&’ within ‘||’"
            (
              ! nAtoiResult // <=> nAtoiResult == 0
              && strAttributeValue == "0"
            )
          )
        {
          byReturn = //SUCCESS;
            getting_attribute_value_succeeded;
          rbyValue = nAtoiResult ;
        }
        //Release memory of dyn. alloc. buffer (else memory leaks).
        XERCES_CPP_NAMESPACE::XMLString::release(&pchAttributeValue);
          //else
          //  byReturn = FAILURE;
      }
    }
    //Release memory of dyn. alloc. buffer (else memory leaks).
    XERCES_CPP_NAMESPACE::XMLString::release(&p_xmlchAttributeName);
  }
  return byReturn ;
}

BYTE XercesAttributesHelper::GetAttributeValue(
  const XERCES_CPP_NAMESPACE::Attributes & attrs,
  const char * lpctstrAttrName,
  //DWORD & r_dwValue
  //StdStringToDestFormat & r_stdstringtodestformat ,
  BYTE (* pfn )(std::string & strAttributeValue ,
  void * pv_AttributeValue ) ,
  //PVOID
  void * pv_AttributeValue
  )
{
  BYTE byReturn = FAILURE;
    //getting_attribute_value_failed;
  XMLCh * p_xmlchAttributeName = XERCES_CPP_NAMESPACE::XMLString::transcode(
    lpctstrAttrName) ;
  if( p_xmlchAttributeName )
  {
    const XMLCh * cp_xmlchAttributeValue = attrs.getValue(
      // const XMLCh *const qName
      p_xmlchAttributeName
      //"number"
      ) ;
    //If the attribute exists.
    if(cp_xmlchAttributeValue)
    {
      char * pchAttributeValue = XERCES_CPP_NAMESPACE::XMLString::transcode(
        cp_xmlchAttributeValue) ;
      if( pchAttributeValue )
      {
        //int nAtoiResult ;
        std::string strAttributeValue = std::string(pchAttributeValue);
        //if(
          //atoi(pchNumber) <> 0: If pchNumber is a valid number.
          //( nAtoiResult = atoi(pchAttributeValue ) )
          ////Because atoi(...) returns "0" also for errors.
          //||
          //! nAtoiResult // <=> nAtoiResult == 0
          //&& strAttributeValue == "0"
          //)
          //r_stdstringtodestformat.ConvertDataFormat(
        byReturn =
          (*pfn)(
            strAttributeValue ,
            pv_AttributeValue
            ) ;
        //  )
        //{
        //  byReturn = SUCCESS;
        //  //r_dwValue = nAtoiResult ;
        //}
        //else
        //  byReturn = XERCES_ATTRIBUTE_VALUE_INVALID_DATA_FORMAT ;
        //Release memory of dyn. alloc. buffer (else memory leaks).
        XERCES_CPP_NAMESPACE::XMLString::release(&pchAttributeValue);
          //else
          //  byReturn = FAILURE;
      }
      else
        byReturn = XERCES_ERROR_CONVERTING_ATTRIBUTE_VALUE_TO_C_STRING ;
    }
    else
      byReturn = XERCES_ATTRIBUTE_VALUE_DOES_NOT_EXIST ;
    //Release memory of dyn. alloc. buffer (else memory leaks).
    XERCES_CPP_NAMESPACE::XMLString::release(&p_xmlchAttributeName);
  }
  else
    byReturn = XERCES_ERROR_CONVERTING_ATTRIBUTE_NAME_TO_XERCES_STRING ;
  return byReturn ;
}

BYTE XercesAttributesHelper::GetAttributeValue(
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
  )
{
  BYTE byReturn = //FAILURE;
    getting_attribute_value_failed;
  XMLCh * p_xmlchAttributeName = XERCES_CPP_NAMESPACE::XMLString::transcode(
    lpctstrAttrName) ;
  if( p_xmlchAttributeName )
  {
    const XMLCh * cp_xmlchAttributeValue = attrs.getValue(
      // const XMLCh *const qName
      p_xmlchAttributeName
      //"number"
      ) ;
    //If the attribute exists.
    if(cp_xmlchAttributeValue)
    {
      char * pchAttributeValue = XERCES_CPP_NAMESPACE::XMLString::transcode(
        cp_xmlchAttributeValue) ;
      if( pchAttributeValue )
      {
        //int nAtoiResult ;
        std::string strAttributeValue = std::string(pchAttributeValue);
        //if(
          //atoi(pchNumber) <> 0: If pchNumber is a valid number.
          //( nAtoiResult = atoi(pchAttributeValue ) )
          ////Because atoi(...) returns "0" also for errors.
          //||
          //! nAtoiResult // <=> nAtoiResult == 0
          //&& strAttributeValue == "0"
          //)
          //r_stdstringtodestformat.ConvertDataFormat(
        byReturn =
          (this->*pfn)(
            //cp_xerceshelper,
            //this ,
            strAttributeValue ,
            pv_AttributeValue
            ) ;
        //  )
        //{
        //  byReturn = SUCCESS;
        //  //r_dwValue = nAtoiResult ;
        //}
        //else
        //  byReturn = XERCES_ATTRIBUTE_VALUE_INVALID_DATA_FORMAT ;
        //Release memory of dyn. alloc. buffer (else memory leaks).
        XERCES_CPP_NAMESPACE::XMLString::release(&pchAttributeValue);
          //else
          //  byReturn = FAILURE;
        //if( byReturn != SUCCESS )
        //  mp_userinterface->Confirm("") ;
      }
      else
        byReturn = XERCES_ERROR_CONVERTING_ATTRIBUTE_VALUE_TO_C_STRING ;
    }
    else
      byReturn = XERCES_ATTRIBUTE_VALUE_DOES_NOT_EXIST ;
    //Release memory of dyn. alloc. buffer (else memory leaks).
    XERCES_CPP_NAMESPACE::XMLString::release(&p_xmlchAttributeName);
  }
  else
    byReturn = XERCES_ERROR_CONVERTING_ATTRIBUTE_NAME_TO_XERCES_STRING ;
  return byReturn ;
}

BYTE XercesAttributesHelper::GetAttributeValue(
  const XERCES_CPP_NAMESPACE::Attributes & attrs,
  const char * lpctstrAttrName,
  WORD & rwValue
  )
{
  BYTE byReturn = //FAILURE;
    getting_attribute_value_failed;
  XMLCh * p_xmlchAttributeName = XERCES_CPP_NAMESPACE::XMLString::transcode(
    lpctstrAttrName) ;
  if( p_xmlchAttributeName )
  {
    const XMLCh * cp_xmlchAttributeValue = attrs.getValue(
      // const XMLCh *const qName
      p_xmlchAttributeName
      //"number"
      ) ;
    //If the attribute exists.
    if(cp_xmlchAttributeValue)
    {
      char * pchAttributeValue = XERCES_CPP_NAMESPACE::XMLString::transcode(
        cp_xmlchAttributeValue) ;
      if( pchAttributeValue )
      {
        int nAtoiResult ;
        std::string strAttributeValue = std::string(pchAttributeValue);
        if(
            //atoi(pchNumber) <> 0: If pchNumber is a valid number.
            ( nAtoiResult = atoi(pchAttributeValue ) )
            //Because atoi(...) returns "0" also for errors.
          ||
          //By using "(...)": avoid Linux g++ warning
          // "suggest parentheses around ‘&&’ within ‘||’"
            (
            ! nAtoiResult // <=> nAtoiResult == 0
            && strAttributeValue == "0"
            )
          )
        {
          byReturn = //SUCCESS;
            getting_attribute_value_succeeded;
          rwValue = nAtoiResult ;
          LOGN("successfully got \"" << lpctstrAttrName <<
            "\" attribute value: " << rwValue )
        }
        //Release memory of dyn. alloc. buffer (else memory leaks).
        XERCES_CPP_NAMESPACE::XMLString::release(&pchAttributeValue);
          //else
          //  byReturn = FAILURE;
      }
    }
    //Release memory of dyn. alloc. buffer (else memory leaks).
    XERCES_CPP_NAMESPACE::XMLString::release(&p_xmlchAttributeName);
  }
  return byReturn ;
}

BYTE XercesAttributesHelper::GetAttributeValue(
  const XERCES_CPP_NAMESPACE::Attributes & r_xercesc_attributes,
  const char * archAttributeName,
  DWORD & r_dwValue
  )
{
//  BYTE byReturn = FAILURE;
//XMLCh * p_xmlchAttributeName = XMLString::transcode(lpctstrAttrName) ;
//if( p_xmlchAttributeName )
//{
//    const XMLCh * cp_xmlchAttributeValue = attrs.getValue(
//      // const XMLCh *const qName
//      p_xmlchAttributeName
//      //"number"
//      ) ;
//    //If the attribute exists.
//    if(cp_xmlchAttributeValue)
//    {
//      char * pchAttributeValue = XMLString::transcode(
//        cp_xmlchAttributeValue) ;
//      if( pchAttributeValue )
//      {
//          int nAtoiResult ;
//          std::string strAttributeValue = std::string(pchAttributeValue);
//          if(
//            //atoi(pchNumber) <> 0: If pchNumber is a valid number.
//            ( nAtoiResult = atoi(pchAttributeValue ) )
//            //Because atoi(...) returns "0" also for errors.
//            ||
//            ! nAtoiResult // <=> nAtoiResult == 0
//            && strAttributeValue == "0"
//            )
//          {
//            byReturn = SUCCESS;
//            r_dwValue = nAtoiResult ;
//          }
//          else
//            byReturn = XERCES_ATTRIBUTE_VALUE_INVALID_DATA_FORMAT ;
//          //Release memory of dyn. alloc. buffer (else memory leaks).
//          XMLString::release(&pchAttributeValue);
//            //else
//            //  byReturn = FAILURE;
//      }
//    }
//    //Release memory of dyn. alloc. buffer (else memory leaks).
//    XMLString::release(&p_xmlchAttributeName);
  return GetAttributeValue
    (
    r_xercesc_attributes,//"processor_name"
    archAttributeName ,
    //* StdStringToDWORD::Convert ,
    //* this->ToDWORD ,
    & XercesAttributesHelper::ToDWORD ,
    //strValue
    //dwIndex
    & r_dwValue
    ) ;
  //}
  //return byReturn ;
}

BYTE XercesAttributesHelper::GetAttributeValue(
  const XERCES_CPP_NAMESPACE::Attributes & attrs,
  const char * lpctstrAttrName,
  float & rfValue
  )
{
  BYTE byReturn = //FAILURE;
    getting_attribute_value_failed;
  XMLCh * p_xmlchAttributeName = XERCES_CPP_NAMESPACE::XMLString::transcode(
    lpctstrAttrName) ;
  if( p_xmlchAttributeName )
  {
    const XMLCh * cp_xmlchAttributeValue = attrs.getValue(
      // const XMLCh *const qName
      p_xmlchAttributeName
      //"number"
      ) ;
    //If the attribute exists.
    if(cp_xmlchAttributeValue)
    {
      char * pchAttributeValue = XERCES_CPP_NAMESPACE::XMLString::transcode(
        cp_xmlchAttributeValue) ;
      if( pchAttributeValue )
      {
        float fAtofResult = 0.0 ;
        std::string strAttributeValue = std::string(pchAttributeValue);
        //char * pEnd;
        //double d1, d2;

        //atof returned 1 for "1.2" on Linux on German because the decimal
        //point is a "," in German.
        //http://stackoverflow.com/questions/1333451/c-locale-independent-atof:
        //"localeconv (in <locale.h>) returns a pointer to struct whose
        //decimal_point member contains that value. Note that the pointer
        //is valid until the next localeconv() or setlocale() – "
        //fAtofResult = (float) atof(pchAttributeValue ) ;
        std::istringstream istr(pchAttributeValue);

        //Ensure a "." is interpreted as decimal point no matter what the
        //current locale is.
        istr.imbue(std::locale("C"));
        istr >> fAtofResult ;

//            fAtofResult =
//              //http://www.cplusplus.com/reference/clibrary/cstdlib/strtod/:
//              //"If no valid conversion could be performed, a zero value (0.0)
//              //is returned."
//              strtod (
//              #ifdef _DEBUG
//                "1,340"
//              #else
//                pchAttributeValue
//              #endif
//                ,&pEnd);
        if(
          //atof(pchNumber) <> 0.0: If pchNumber is a valid number.
          //Because atoi(...) returns "0" also for errors.
          fAtofResult
          ||
          //By using "(...)": avoid Linux g++ warning
          // "suggest parentheses around ‘&&’ within ‘||’"
            (
            ! fAtofResult // <=> nAtoiResult == 0
            && ( strAttributeValue == "0" || strAttributeValue == "0.0" )
            )
          )
        {
          byReturn = //SUCCESS;
            getting_attribute_value_succeeded;
          rfValue = fAtofResult ;
          LOGN("successfully got \"" << lpctstrAttrName <<
            "\" attribute value: " << rfValue )
        }
        //Release memory of dyn. alloc. buffer (else memory leaks).
        XERCES_CPP_NAMESPACE::XMLString::release(& pchAttributeValue);
          //else
          //  byReturn = FAILURE;
      }
    }
    //Release memory of dyn. alloc. buffer (else memory leaks).
    XERCES_CPP_NAMESPACE::XMLString::release(&p_xmlchAttributeName);
  }
  return byReturn ;
}

BYTE XercesAttributesHelper::GetAttributeValue
  (
  const XERCES_CPP_NAMESPACE::Attributes & xercesc_attributes,
  const std::string & cr_stdstrAttributeName,
  std::string & r_strValue
  )
{
  return GetAttributeValue(
    xercesc_attributes,
    cr_stdstrAttributeName.c_str(),
    r_strValue
    ) ;
}

BYTE XercesAttributesHelper::GetAttributeValue
  (
  const XERCES_CPP_NAMESPACE::Attributes & cr_xercesc_attributes,
  const char * lpcstrAttrName,
  std::string & r_strValue
  )
{
  BYTE byReturn = //FAILURE;
    getting_attribute_value_failed;
  XMLCh * p_xmlchAttributeName = XERCES_CPP_NAMESPACE::XMLString::transcode(
    lpcstrAttrName) ;
  if( p_xmlchAttributeName )
  {
    const XMLCh * cp_xmlchAttributeValue = cr_xercesc_attributes.getValue(
      // const XMLCh *const qName
      p_xmlchAttributeName
      //"number"
      ) ;
    //If the attribute exists.
    if(cp_xmlchAttributeValue)
    {
      char * pchAttributeValue = XERCES_CPP_NAMESPACE::XMLString::transcode(
        cp_xmlchAttributeValue) ;
      if( pchAttributeValue )
      {
        r_strValue = std::string(pchAttributeValue);
        byReturn = //SUCCESS;
          getting_attribute_value_succeeded;
        //Release memory of dyn. alloc. buffer (else memory leaks).
        XERCES_CPP_NAMESPACE::XMLString::release( & pchAttributeValue);
      }
    }
    //Release memory of dyn. alloc. buffer (else memory leaks).
    XERCES_CPP_NAMESPACE::XMLString::release( & p_xmlchAttributeName);
  }
  return byReturn ;
}

BYTE XercesAttributesHelper::GetAttributeValue
  (
  const XERCES_CPP_NAMESPACE::Attributes & cr_xercesc_attributes,
  const char * lpctstrAttrName,
//  std::string & r_stdstrAttributeName ,
  std::wstring & r_stdwstrValue
  )
{
  BYTE byReturn = //FAILURE;
    getting_attribute_value_failed;
  XMLCh * p_xmlchAttributeName = XERCES_CPP_NAMESPACE::XMLString::transcode(
    lpctstrAttrName) ;
  if( p_xmlchAttributeName )
  {
    const XMLCh * cp_xmlchAttributeValue = cr_xercesc_attributes.getValue(
      // const XMLCh *const qName
      p_xmlchAttributeName
      //"number"
      ) ;
    //If the attribute exists.
    if(cp_xmlchAttributeValue)
    {
      r_stdwstrValue = //std::wstring(
//        //Avoid g++ error "no matching function for call to
//        //‘std::basic_string<wchar_t, std::char_traits<wchar_t>,
//        //std::allocator<wchar_t> >::basic_string(const XMLCh*&)’ "
//        (wchar_t *)
//        pxmlch);
        Xerces::ConvertXercesStringToStdWstring(cp_xmlchAttributeValue) ;
      byReturn = //SUCCESS;
        getting_attribute_value_succeeded;
    }
    //Release memory of dyn. alloc. buffer (else memory leaks).
    XERCES_CPP_NAMESPACE::XMLString::release( & p_xmlchAttributeName);
  }
  return byReturn ;
}

BYTE XercesAttributesHelper::ToDWORD(
  std::string & strAttributeValue ,
  void * pv_AttributeValue
  )
{
  BYTE byReturn = //FAILURE ;
      getting_attribute_value_failed;
  //TCHAR * p_tch ;
  char * p_ch ;
  DWORD dwResult = //strtoul
    //_tcstoul( strAttributeValue.c_str(), &p_tch ,//10
    //std::string is a single byte type and so needs the "char" version.
    strtoul( strAttributeValue.c_str(), & p_ch ,
    //ms-help://MS.VSCC.v80/MS.MSDN.v80/MS.VisualStudio.v80.de/dv_vccrt/html/
    // 38f2afe8-8178-4e0b-8bbe-d5c6ad66e3ab.htm:
    //"If base is 0, the initial characters of the string pointed to by
    //nptr are used to determine the base."
    0
    ) ;
  //dwRes = atol(strAttributeValue.c_str() ;
  //Use atoi64 because atol return a long value 2^31 to -2^31 but a
  //DWORD can go to 2^32
  //__int64 i64 = _atoi64(strAttributeValue.c_str() ) ;

  if ( //The return value is 0 for _atoi64 if the input cannot be
    //converted to a value of that type.
    ( //i64
    dwResult == 0 && strAttributeValue != "0" && strAttributeValue != "0x0" )
    ||
    //In all out-of-range cases, errno is set to ERANGE
    errno == ERANGE
    ||
    //i64 > ULONG_MAX
    dwResult == ULONG_MAX
    //||
    //i64 < 0
    )
     //Overflow condition occurred.
  {
//    byReturn = XERCES_ATTRIBUTE_VALUE_INVALID_DATA_FORMAT ;
//    std::string str = "Error converting \"" + strAttributeValue +
//      "\" (should be specified as DECIMAL number ) to a number" ;
//    mp_userinterface->Confirm( str ) ;
  }
  else
  {
    //dwRes = i64 ;
    byReturn = //SUCCESS;
      getting_attribute_value_succeeded;
    *((DWORD*) pv_AttributeValue ) = //(DWORD) i64; //(void*) () ;
      dwResult ;
  }
  return byReturn ;
}
