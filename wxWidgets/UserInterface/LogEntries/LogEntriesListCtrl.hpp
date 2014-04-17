/*
 * LogEntriesListCtrl.hpp
 *
 *  Created on: 12.04.2014
 *      Author: mr.sys
 */

#ifndef LOGENTRIESLISTCTRL_HPP_
#define LOGENTRIESLISTCTRL_HPP_

#include <deque> //class std::deque (double-ended queue)
#include <wx/listctrl.h> //class wxListCtrl
#include <Controller/Logger/Appender/FormattedLogEntryProcessor.hpp>

class Logger;
//class I_LogEntryOutputter;
//class I_LogFormatter;

/** = no pointers to strings ->whose content is changed */
class PersistentLogEntry
  : public LogFileEntry
{
//  uint16_t m_threadID; //0-2^16 numbers -> needs at least 2 bytes
//  uint16_t year; //data type need to have at least 2 bytes.
//  datatype_for_1_byte_numbers month;
//  datatype_for_1_byte_numbers day;
//  datatype_for_1_byte_numbers hour;
//  datatype_for_1_byte_numbers minute;
//  datatype_for_1_byte_numbers second;
//  uint16_t millisecond;
//  uint16_t microsecond;
//  uint16_t nanosecond;

public:
  std::string m_std_strMessage;
  std::string m_std_strThreadName;

  PersistentLogEntry(const LogFileEntry & logfileEntry)
  {
//    threadID = logfileEntry.
//    * this = logfileEntry; //obtain a full copy
    m_std_strMessage = * logfileEntry.p_std_strMessage;
    millisecond = logfileEntry.millisecond;
    second = logfileEntry.second;
    hour = logfileEntry.hour;
    minute = logfileEntry.minute;
  }
};

namespace wxWidgets
{

  class LogEntriesListCtrl
    : public wxListCtrl,
    public FormattedLogEntryProcessor
  {
    enum columnIndices { colID_timeStamp, colID_message };
    typedef std::deque<PersistentLogEntry> container_type;
    container_type m_logentries;
    Logger & m_logger;
  public:
    LogEntriesListCtrl(
      /*const*/ wxWindow * /*const*/ parent,
      const wxWindowID ID,
      Logger & logger//,
//      I_LogEntryOutputter * p_outputhandler,
//      I_LogFormatter * p_log_formatter,
//      enum LogLevel::MessageType logLevel
      );
    virtual
    ~LogEntriesListCtrl();

    unsigned Log(//ostream & ostr
  //    const std::string & r_stdstrMessage,
      const LogFileEntry & logfileentry,
      enum LogLevel::MessageType messageType =
        LogLevel::info,
      const char * const prettyFunctionFormattedFunctionName = NULL
      ) const;
    wxString OnGetItemText(long item, long column) const;
    /** For callback of OnGetItemText(...). */
    DECLARE_EVENT_TABLE()
  };

} /* namespace wxWidgets */

#endif /* LOGENTRIESLISTCTRL_HPP_ */
