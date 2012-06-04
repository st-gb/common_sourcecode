/*
 * HTMLformatLogFileWriter.cpp
 *
 *  Created on: 26.04.2012
 *      Author: Stefan
 */

#include "Controller/Logger/HTMLformatLogFileWriter.hpp"

//  HTMLformatLogFileWriter::HTMLformatLogFileWriter()
//  {
//    // TODO Auto-generated constructor stub
//  }

HTMLformatLogFileWriter::~HTMLformatLogFileWriter()
{
  // TODO Auto-generated destructor stub
}

inline void HTMLformatLogFileWriter::OutputCSSclass(enum MessageType messageType)
{
  switch(messageType)
  {
    case log_message_typeINFO:
      * m_p_std_ofstream << "class=\"info\"";
      break;
    case log_message_typeERROR:
      * m_p_std_ofstream << "class=\"error\"";
      break;
    case log_message_typeWARNING:
      * m_p_std_ofstream << "class=\"warning\"";
      break;
    case log_message_typeSUCCESS:
      * m_p_std_ofstream << "class=\"success\"";
      break;
    //avoid g++ "warning: enumeration value 'beyondLastLogMessageType'
    //not handled in switch.
    case beyondLastLogMessageType:
      break;
  }
}

void HTMLformatLogFileWriter::WriteHeader()
{
  * m_p_std_ofstream
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
    "    <th>thread ID</th>"
    "    <th>message</th>"
    "   </tr>\n";
}

void HTMLformatLogFileWriter::WriteLogFileEntry(
  const LogFileEntry & logfileentry,
  enum MessageType messageType /*= log_message_typeINFO*/
  )
{
//  static std::string std_strTime;
  GetTimeAsString(logfileentry//, std_strTime
    );
  * m_p_std_ofstream
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
    << "</td><td>" << logfileentry.threadID << "</td>\n    "
        "<td ";
  OutputCSSclass(messageType);
  * m_p_std_ofstream << ">"
    << * logfileentry.p_std_strMessage << "</td>"
    << "   </tr>\n";
}

void HTMLformatLogFileWriter::WriteMessage(
  const std::string & r_std_strMessage,
  enum MessageType messageType //= log_message_typeINFO
  )
{
  if( messageType < beyondLastLogMessageType )
  {
    * m_p_std_ofstream
      << "<td ";
    OutputCSSclass(messageType);
    * m_p_std_ofstream << ">" << r_std_strMessage
      << "</td></tr>\n";
  }
  else
  {
    * m_p_std_ofstream << "<td>" << r_std_strMessage << "</td></tr>\n";
  }
}

