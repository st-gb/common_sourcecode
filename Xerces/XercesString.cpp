/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */
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
    std::string std_strValue;
    ToStdString(p_xmlch, std_strValue);
    return std_strValue ;
  }

  void ToStdString(
    const XMLCh * p_xmlch,
    std::string & r_std_strValue
    )
  {
    //If the attribute exists.
    if(p_xmlch)
    {
      char * pchAttributeValue = XERCES_CPP_NAMESPACE::XMLString::transcode(
        (const XMLCh * const) p_xmlch) ;
      if( pchAttributeValue )
      {
        r_std_strValue = std::string(pchAttributeValue);
        //Release memory of dyn. alloc. buffer (else memory leaks).
        XERCES_CPP_NAMESPACE::XMLString::release(&pchAttributeValue);
      }
    }
  }
}
