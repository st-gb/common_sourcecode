/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany
 * ("Trilobyte SE") 2010-at least 2012.
 * You are allowed to modify and use the source code from Trilobyte SE for free
 * if you are not making profit directly or indirectly with it or its adaption.
 * Else you may contact Trilobyte SE. */
/*
 * HTMLformatLogFileWriter.cpp
 *
 *  Created on: 26.04.2012
 *      Author: Stefan
 */

#include "HTMLlogFormatter.hpp"

//  HTMLformatLogFileWriter::HTMLformatLogFileWriter()
//  {
//    // TODO Auto-generated constructor stub
//  }

HTMLlogFormatter::~HTMLlogFormatter()
{
  // TODO Auto-generated destructor stub
}

inline void HTMLlogFormatter::OutputCSSclass(enum MessageType messageType)
{
  switch(messageType)
  {
    case LogLevel::info:
      * m_p_std_ostream << "class=\"info\"";
      break;
    case LogLevel::debug:
      * m_p_std_ostream << "class=\"debug\"";
      break;
    case LogLevel::error:
      * m_p_std_ostream << "class=\"error\"";
      break;
    case LogLevel::warning:
      * m_p_std_ostream << "class=\"warning\"";
      break;
    case LogLevel::success:
      * m_p_std_ostream << "class=\"success\"";
      break;
    //avoid g++ "warning: enumeration value 'beyondLastLogMessageType'
    //not handled in switch.
    case beyondLastLogMessageType:
    //case debug:
      break;
  }
}

void HTMLlogFormatter::WriteHeader()
{
  * m_p_std_ostream
    << "<html>\n"
      " <link rel=\"stylesheet\" type=\"text/css\" href=\""
      "format.css"
      //<< m_p_logger->m_std_strLogFilePath + ".css"
      "\" />\n"
      " <body>"
      "  <table>\n"
  //"Table head" element names from
  // http://www.w3schools.com/html/html_tables.asp:
  <<   "<tr>"
    "    <th>time</th>"
    "    <th>thread name</th>"
    "    <th>thread ID</th>"
    "    <th>code pos.</th>"
    "    <th>message</th>"
    "   </tr>\n";
}

void HTMLlogFormatter::WriteTrailer()
{
//    if( m_p_std_ostream )
  * m_p_std_ostream << "</table></body></html>";
//  m_p_logger->WriteToFile();
}

/** exchange '\n' with "<br>" */
inline std::string & MakeHTMLFormat(std::string * p_std_strMessage)
{
//  std::string::iterator iter = p_std_strMessage->begin();
//  char * p_ch = p_std_strMessage->c_str();
//  std::string std = p_std_strMessage->replace(0, );
//  while( * p_ch )
//  {
//
//  }
  return *p_std_strMessage;
}

void HTMLlogFormatter::WriteLogFileEntry(
  const LogFileEntry & logfileentry,
  enum MessageType messageType /*= LogLevel::info*/,
  const char * const prettyFunctionFormattedFunctionName /*= NULL*/
  )
{
//  static std::string std_strTime;
  GetTimeAsString(logfileentry//, std_strTime
    );
//  static std::string std_strHTMLformattedMessage;
//  std_strHTMLformattedMessage = MakeHTMLFormat(logfileentry.p_std_strMessage);
  * m_p_std_ostream
    << "   <tr><td>"
//    << logfileentry.year << "-"
//    << (uint16_t) logfileentry.month << "-"
//    << (uint16_t) logfileentry.day << " "
//    << (uint16_t) logfileentry.hour << "h:"
//    << (uint16_t) logfileentry.minute << "min:"
//    << (uint16_t) logfileentry.second << "s "
//    << logfileentry.millisecond << "ms"
//    << logfileentry.nanosecond << "ns"
//    << std_strTime
    << m_p_chTimeString
    << "</td><td>";
  if( logfileentry.p_std_strThreadName )
    * m_p_std_ostream << * logfileentry.p_std_strThreadName << "</td>\n<td>";
  else
    * m_p_std_ostream << "</td>\n<td>";
  * m_p_std_ostream << logfileentry.threadID;
  * m_p_std_ostream << "</td>\n<td>" << prettyFunctionFormattedFunctionName;
  * m_p_std_ostream << "</td>\n    "
        "<td ";
  OutputCSSclass(messageType);
  * m_p_std_ostream << ">"
    << * logfileentry.p_std_strMessage << "</td>"
    << "   </tr>\n";
}

void HTMLlogFormatter::WriteMessage(
  const std::string & r_std_strMessage,
  enum MessageType messageType //= LogLevel::info
  )
{
  if( messageType < beyondLastLogMessageType )
  {
    * m_p_std_ostream
      << "<td ";
    OutputCSSclass(messageType);
    * m_p_std_ostream << ">" << r_std_strMessage
      << "</td></tr>\n";
  }
  else
  {
    * m_p_std_ostream << "<td>" << r_std_strMessage << "</td></tr>\n";
  }
}

