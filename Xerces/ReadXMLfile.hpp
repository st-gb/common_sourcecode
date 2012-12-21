/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */
/*
 * ReadXMLfile.hpp
 *
 *  Created on: Nov 29, 2010
 *      Author: Stefan
 */

#ifndef READXMLFILE_HPP_
#define READXMLFILE_HPP_

#include "ReadXMLdocument.hpp" //ReadXMLdocument(...)
#include <preprocessor_macros/logging_preprocessor_macros.h> //LOGN(...)
//InitializeXerces(), TerminateXerces()
#include <Xerces/XercesHelperFunctions.hpp>
//class XERCES_CPP_NAMESPACE::LocalFileInputSource
#include <xercesc/framework/LocalFileInputSource.hpp>

inline BYTE ReadXMLfile_Inline(
  const char * const cpc_chXMLfilePath ,
  //Base class of implementing Xerces XML handlers.
  //This is useful because there may be more than one XML file to read.
  //So one calls this functions with different handlers passed.
   XERCES_CPP_NAMESPACE::DefaultHandler * const pc_defaulthandler ,
   std::wstring & r_stdwstrErrorMessage
  )
{
  BYTE by = 1 ;
  LOGN_DEBUG(//"ReadXMLfile_Inline(" <<
    cpc_chXMLfilePath
    << "," << pc_defaulthandler << ",...) begin")
  XMLCh * p_xmlchXMLfilePath = XERCES_CPP_NAMESPACE::XMLString::transcode(
    cpc_chXMLfilePath);
  LOGN_DEBUG(//"ReadXMLfile_Inline--"
    "file path as Xerces string: " <<
    p_xmlchXMLfilePath )
  if( p_xmlchXMLfilePath )
  {
    XERCES_CPP_NAMESPACE::LocalFileInputSource xerces_localfileinputsource(
      p_xmlchXMLfilePath ) ;
    LOGN_TYPE(//"ReadXMLfile_Inline--"
      "LocalFileInputSource obj: "
      << & xerces_localfileinputsource, LogLevel::debug )
    by = ReadXMLdocument(
      xerces_localfileinputsource ,
      pc_defaulthandler ,
      r_stdwstrErrorMessage
      ) ;
    XERCES_CPP_NAMESPACE::XMLString::release( & p_xmlchXMLfilePath );
  }
  LOGN_DEBUG(//"ReadXMLfile_Inline "
    "before return")
  return by ;
}

//@return 0=success
inline BYTE ReadXMLfileInitAndTermXerces_Inline(
  const char * const cpc_chXMLfilePath ,
  //Base class of implementing Xerces XML handlers.
  //This is useful because there may be more than one XML file to read.
  //So one calls this functions with different handlers passed.
   XERCES_CPP_NAMESPACE::DefaultHandler * const pc_defaulthandler ,
   std::wstring & r_stdwstrErrorMessage
  )
{
  if( InitializeXerces() )
  {
    return ReadXMLfile_Inline(
      cpc_chXMLfilePath ,
      pc_defaulthandler ,
      r_stdwstrErrorMessage
      ) ;
    TerminateXerces() ;
  }
  return 1 ;
}

#endif /* READXMLFILE_HPP_ */
