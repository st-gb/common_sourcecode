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
  LOGN("ReadXMLfile_Inline(" << cpc_chXMLfilePath
    << "," << pc_defaulthandler << ",...) begin")
  XMLCh * p_xmlchXMLfilePath = XERCES_CPP_NAMESPACE::XMLString::transcode(
    cpc_chXMLfilePath);
  LOGN("ReadXMLfile_Inline--file path as Xerces string: " <<
    p_xmlchXMLfilePath )
  if( p_xmlchXMLfilePath )
  {
    XERCES_CPP_NAMESPACE::LocalFileInputSource xerces_localfileinputsource(
      p_xmlchXMLfilePath ) ;
    LOGN("ReadXMLfile_Inline--LocalFileInputSource obj: "
      << & xerces_localfileinputsource )
    by = ReadXMLdocument(
      xerces_localfileinputsource ,
      pc_defaulthandler ,
      r_stdwstrErrorMessage
      ) ;
    XERCES_CPP_NAMESPACE::XMLString::release( & p_xmlchXMLfilePath );
  }
  LOGN("ReadXMLfile_Inline before return")
  return by ;
}

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
    ReadXMLfile_Inline(
      cpc_chXMLfilePath ,
      pc_defaulthandler ,
      r_stdwstrErrorMessage
      ) ;
    TerminateXerces() ;
  }
}

#endif /* READXMLFILE_HPP_ */
