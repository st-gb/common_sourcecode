/*
 * HTMLformatLogFileWriter.hpp
 *
 *  Created on: 26.04.2012
 *      Author: Stefan
 */

#ifndef HTMLFORMATLOGFILEWRITER_HPP_
#define HTMLFORMATLOGFILEWRITER_HPP_

//#include "Logger.hpp" //base class "Logger"
#include "ILogFormatter.hpp" //base class
// inline void outputDateAndTimeInHTMLFormat(std::ostream & r_ostream)
#include "log_file_prefix.hpp"

//typedef unsigned long WORD;
class Logger;

class HTMLformatLogFileWriter
  : public I_LogFormatter
//      Logger
{
public:
  HTMLformatLogFileWriter(//std::ofstream * p_std_ofstream
    const Logger * p_logger)
    : I_LogFormatter(//p_std_ofstream
      p_logger)
  {
  }
  virtual
  ~HTMLformatLogFileWriter();
//  {
//  }

  virtual void WriteHeader();

  virtual void WriteTrailer()
  {
    * m_p_std_ofstream << "</table></body></html>";
  }

  //inline
  void OutputCSSclass(enum MessageType messageType);

  //inline
  void WriteLogFileEntry(
    const LogFileEntry & logfileentry,
    enum MessageType messageType = log_message_typeINFO
    );

  void WriteMessage(const std::string & r_std_strMessage,
    enum MessageType messageType = log_message_typeINFO);
  void WriteTimeStamp(const std::stringstream & std_str_stream)
  {
    * m_p_std_ofstream << "<tr><td>" << std_str_stream.str() << "</td>";
  }
};

#endif /* HTMLFORMATLOGFILEWRITER_HPP_ */
