/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */
/*
 * XercesHelper.hpp
 *
 *  Created on: Nov 12, 2010
 *      Author: Stefan
 */

#ifndef XERCESHELPER_HPP_
#define XERCESHELPER_HPP_

#include <preprocessor_macros/logging_preprocessor_macros.h> //LOGN(...)
//XERCES_CPP_NAMESPACE::XMLPlatformUtils::Initialize()
#include <xercesc/util/PlatformUtils.hpp>
//XERCES_CPP_NAMESPACE::XMLString::transcode(XMLCh *), release(char **)
#include <xercesc/util/XMLString.hpp>

//Code is equal on many code places.
inline bool InitializeXerces()
{
  try
  {
    LOGN_DEBUG("BEFORE initializing Xerces") ;
    //http://xerces.apache.org/xerces-c/program-3.html:
    //"Independent of the API you want to use, DOM, SAX, or SAX2, your
    //application must initialize the Xerces system before using the API[...]"
    //Initialize() must be called _before_ any Xerces function call, else
    // SIGSEV / program crash.
    XERCES_CPP_NAMESPACE::XMLPlatformUtils::Initialize();
    LOGN_DEBUG("Xerces successfully initialized") ;
  }
  catch(const XERCES_CPP_NAMESPACE::XMLException & cr_xercesc_xml_exception )
  {
    char * pMsg = XERCES_CPP_NAMESPACE::XMLString::transcode(
      cr_xercesc_xml_exception.getMessage() );
    LOGN_ERROR( "Error during Xerces-c Initialization.\n"
      << "  Exception message:"
      << pMsg )
    XERCES_CPP_NAMESPACE::XMLString::release( & pMsg);
  //      return 1;
    return false ;
  }
  return true ;
}

inline void TerminateXerces()
{
  //http://xerces.apache.org/xerces-c/program-3.html:
  //"Independent of the API you want to use, DOM, SAX, or SAX2, your
  //application must [...] and terminate it after you are done.
  //When Terminate() was called in another block (even if in a function that
  //is called in the same block) than program crash.
  XERCES_CPP_NAMESPACE::XMLPlatformUtils::Terminate();
  LOGN("Xerces access terminated")
}

#endif /* XERCESHELPER_HPP_ */
