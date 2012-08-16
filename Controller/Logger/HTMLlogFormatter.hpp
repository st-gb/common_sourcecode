/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany
 * ("Trilobyte SE") 2010-at least 2012.
 * You are allowed to modify and use the source code from Trilobyte SE for free
 * if you are not making profit directly or indirectly with it or its adaption.
 * Else you may contact Trilobyte SE. */
/*
 * HTMLlogFormatter.hpp
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

/** Name should not contain a log destination like a file (because formatting
 * ought to be independent of the log destination), so name it like
 * "log formatter". */
class HTMLlogFormatter
  : public I_LogFormatter
//      Logger
{
public:
  HTMLlogFormatter(//std::ofstream * p_std_ofstream
    const Logger * p_logger)
    : I_LogFormatter(//p_std_ofstream
      p_logger)
  {
  }
  virtual
  ~HTMLlogFormatter();
//  {
//  }

  virtual void WriteHeader();

  virtual void WriteTrailer();

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
    * m_p_std_ostream << "<tr><td>" << std_str_stream.str() << "</td>";
  }
};

#endif /* HTMLFORMATLOGFILEWRITER_HPP_ */
