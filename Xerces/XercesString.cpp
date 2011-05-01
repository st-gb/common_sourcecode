/*
 * XercesString.cpp
 *
 *  Created on: 30.09.2010
 *      Author: sgebauer
 */

#include <Xerces/XercesString.hpp>

namespace Xerces
{

//  XercesString::XercesString()
//  {
//    // TODO Auto-generated constructor stub
//
//  }
//
//  XercesString::~XercesString()
//  {
//    // TODO Auto-generated destructor stub
//  }
  std::string ToStdString(
    const XMLCh * p_xmlch
    )
  {
    std::string strValue ;
    //If the attribute exists.
    if(p_xmlch)
    {
      char * pchAttributeValue = XERCES_CPP_NAMESPACE::XMLString::transcode(
        (const XMLCh * const) p_xmlch) ;
      if( pchAttributeValue )
      {
        strValue = std::string(pchAttributeValue);
        //Release memory of dyn. alloc. buffer (else memory leaks).
        XERCES_CPP_NAMESPACE::XMLString::release(&pchAttributeValue);
      }
    }
    return strValue ;
  }
}
