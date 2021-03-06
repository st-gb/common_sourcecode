/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */
/*
 * ReadXMLdocument.hpp
 *
 *  Created on: Jul 31, 2010
 *      Author: Stefan
 */

#ifndef READXMLDOCUMENT_HPP_
#define READXMLDOCUMENT_HPP_

//Xerces header files.
#include <xercesc/sax/InputSource.hpp> //class XERCES_CPP_NAMESPACE::InputSource
//XERCES_CPP_NAMESPACE::DefaultHandler
#include <xercesc/sax2/DefaultHandler.hpp>
//class XERCES_CPP_NAMESPACE::SAX2XMLReader
#include <xercesc/sax2/SAX2XMLReader.hpp>
//Class XERCES_CPP_NAMESPACE::XMLReaderFactory
#include <xercesc/sax2/XMLReaderFactory.hpp>

#include <string> //for class std::wstring
#include <Xerces/XercesString.hpp> //GET_WCHAR_STRING_FROM_XERCES_STRING(...)

//Own header files.
//for convertToStdString(...)
#include <Controller/character_string/convertFromAndToStdString.hpp>
#include <Controller/character_string/stdtstr.hpp> //for GetStdString(...)
#include <preprocessor_macros/logging_preprocessor_macros.h> //LOGN(...)

typedef unsigned char BYTE ;

//I do not do "using namespace XERCES_CPP_NAMESPACE" because so the class
// names are eindeutig.

//@return 0=success
//"inline" because it may be called from with another function without
//  an additional function call overhead.
inline unsigned char ReadXMLdocument(
  const XERCES_CPP_NAMESPACE::InputSource & cr_inputsource,
 //Base class of implementing Xerces XML handlers.
 //This is useful because there may be more than one XML file to read.
 //So one calls this functions with different handlers passed.
  XERCES_CPP_NAMESPACE::DefaultHandler * const pc_defaulthandler ,
  std::wstring & r_stdwstrErrorMessage
  )
{
  LOGN_DEBUG(/*"ReadXMLdocument "*/"begin")
  unsigned char byReturn = 1 ;
    //DEBUG("ReadXMLfileInitAndTermXerces begin--filename:%s\n",xmlFile);
  //Initialize to NULL just to avoid (g++) compiler warning.
  XERCES_CPP_NAMESPACE::SAX2XMLReader * p_sax2xmlreader =
    XERCES_CPP_NAMESPACE::XMLReaderFactory::createXMLReader();
  if( p_sax2xmlreader )
  {
    p_sax2xmlreader->setFeature(
      XERCES_CPP_NAMESPACE::XMLUni::fgSAX2CoreValidation, true);
    p_sax2xmlreader->setFeature(
      XERCES_CPP_NAMESPACE::XMLUni::fgSAX2CoreNameSpaces, true);   // optional

    //DefaultHandler * p_defaultHandler = new DefaultHandler();
    XERCES_CPP_NAMESPACE::DefaultHandler defaultHandler;
    //p_sax2xmlreader->setContentHandler(defaultHandler);
    p_sax2xmlreader->setContentHandler(//&sax2
      pc_defaulthandler );
    p_sax2xmlreader->setErrorHandler(//p_defaultHandler
      & defaultHandler );
    try
    {
      LOGN_DEBUG( "before parsing XML document"
//        << GetStdStringInline(
//            ConvertXercesStringToStdWstring( cr_inputsource.getPublicId() )
//          )
        )
      p_sax2xmlreader->
      //from SAX2XMLReader::parse(const   InputSource&    source):
//        * @exception SAXException Any SAX exception, possibly
//        *            wrapping another exception.
//        * @exception XMLException An exception from the parser or client
//        *            handler code.
      parse(//xmlFile
        cr_inputsource );
//      DEBUG("-----------End of loading from XML document/ input source\n") ;
//          if( model.m_bTruncateLogFileForEveryStartup )
//              g_logger.TruncateFileToZeroAndRewrite() ;
       byReturn = 0 ;
       LOGN_DEBUG( "XML document successfully parsed." );
    }
    catch ( const XERCES_CPP_NAMESPACE::XMLException & cr_xmlexception )
    {
//      LOGN( "XMLException" );

      //Use wide string because maybe chinese file names.
      r_stdwstrErrorMessage =
        std::wstring( L"XML exception in document \"" )
//        + std::wstring( cr_inputsource.getSystemId() ) +
        + GET_WCHAR_STRING_FROM_XERCES_STRING( cr_inputsource.getSystemId() ) +
        L"\" :" + //message
//        cr_xmlexception.getMessage() ;
        GET_WCHAR_STRING_FROM_XERCES_STRING(cr_xmlexception.getMessage() );
//          return FAILURE;
    }
    catch ( const XERCES_CPP_NAMESPACE::SAXParseException & cr_saxparseexception
       )
    {
//      LOGN( "SAXParseException" );
      XMLFileLoc xmlfilelocColumnNumber = cr_saxparseexception.
          getColumnNumber() ;
      XMLFileLoc xmlfilelocLineNumber = cr_saxparseexception.
          getLineNumber() ;
      r_stdwstrErrorMessage = L"XML exception in document \""
//        + std::wstring( cr_inputsource.getSystemId() ) +
        + GET_WCHAR_STRING_FROM_XERCES_STRING( cr_inputsource.getSystemId() ) +
        L"\"\n"
//          + "\", line " + convertToStdString( cr_saxparseexception.getLineNumber() )
//          + ", column " + convertToStdString( cr_saxparseexception.getColumnNumber() )
        //+
        L"in line " + GetStdWstring( convertToStdString(
          xmlfilelocLineNumber ) )
        + L", column " + GetStdWstring( convertToStdString(
          xmlfilelocColumnNumber ) )
//          + "\", line " + convertToStdString( cr_saxexception.getLineNumber() )
//          + ", column " + convertToStdString( cr_saxexception.getColumnNumber() )
        //+ L":\n\"" + cr_saxparseexception.getMessage() ;
        + L":\n\"" + GET_WCHAR_STRING_FROM_XERCES_STRING(
          cr_saxparseexception.getMessage() ) ;
      if( ! xmlfilelocColumnNumber && ! xmlfilelocLineNumber )
      {
        r_stdwstrErrorMessage += L"\n\nThis probably means that this document/ file does"
          "not exist" ;
      }
      r_stdwstrErrorMessage +=
//          + cr_saxexception.getMessage()
        + L"\n\nSorry, no further information.\n"
          "In order to solve this problem you may look into the XML "
        "specifications for element names etc" ;
//        p_userinterface->Confirm(//pchMessage
//          //strMessage
//          stdwstrMessage );
//      LOGWN_WSPRINTF(L"%ls", stdwstrMessage.c_str() )
    }
    catch( const XERCES_CPP_NAMESPACE::SAXException & cr_saxexception )
    {
//      LOGN( "SAXException" );
//        char * pchMessage = XMLString::transcode(
//            r_saxparseexception.getMessage()
//            r_saxexception.getMessage()
//          );
//        std::string strMessage = "XML error in file: \"" +
//          std::string(xmlFile)

      //Use wide string because maybe chinese file names.
      r_stdwstrErrorMessage = L"XML exception in document \""
//        + std::wstring( cr_inputsource.getSystemId() ) +
        + GET_WCHAR_STRING_FROM_XERCES_STRING( cr_inputsource.getSystemId() ) +
        L"\" :"
//          + "\", line " + convertToStdString( r_saxparseexception.getLineNumber() )
//          + ", column " + convertToStdString( r_saxparseexception.getColumnNumber() )
//          + L"\", line " + GetStdWstring( convertToStdString(
//              r_saxparseexception.getLineNumber() ) )
//          + L", column " + GetStdWstring( convertToStdString(
//            r_saxparseexception.getColumnNumber() ) )
//          + "\", line " + convertToStdString( r_saxexception.getLineNumber() )
//          + ", column " + convertToStdString( r_saxexception.getColumnNumber() )
//          + L": " + r_saxparseexception.getMessage()
//        + cr_saxexception.getMessage()
        + GET_WCHAR_STRING_FROM_XERCES_STRING( cr_saxexception.getMessage() )
        + L"\nIn order to solve this problem you may look into the XML "
        "specifications for element names etc" ;
//      LOGWN_WSPRINTF(L"%ls", stdwstrMessage.c_str() )
//        XMLString::release( & pchMessage );
//          return FAILURE;
    }
    catch (...)
    {
//      LOGN( "Unexpected Exception at parsing XML\n" ) ;
      r_stdwstrErrorMessage = std::wstring(
        L"Unexpected Exception parsing the XML document\n");
//          return FAILURE;
    }
    //__finally
   //   {
   ////        //http://xerces.apache.org/xerces-c/apiDocs-2/classXMLReaderFactory.html#_details:
   //   //"The parser object returned by XMLReaderFactory is owned by the
   //   //calling users, and it's the responsiblity of the users to
   //   //delete that parser object, once they no longer need it."
   //   delete p_sax2xmlreader;
   //   }
    //delete p_defaultHandler;

    //http://xerces.apache.org/xerces-c/apiDocs-2/classXMLReaderFactory.html#_details:
    //"The parser object returned by XMLReaderFactory is owned by
    //the calling users, and it's the responsiblity of the users to
    //delete that parser object, once they no longer need it."
    delete p_sax2xmlreader;
  }
  else
    r_stdwstrErrorMessage = std::wstring (
      L"Xerces failed to create an XML reader" );
  LOGN_DEBUG("ReadXMLdocument end")
//    return SUCCESS;
  return byReturn ;
}

#endif /* READXMLDOCUMENT_HPP_ */
