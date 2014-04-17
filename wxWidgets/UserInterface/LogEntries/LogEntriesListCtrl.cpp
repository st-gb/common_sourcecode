/*
 * LogEntriesListCtrl.cpp
 *
 *  Created on: 12.04.2014
 *      Author: mr.sys
 */

#include <wxWidgets/UserInterface/LogEntries/LogEntriesListCtrl.hpp>
#include <wxWidgets/Controller/character_string/wxStringHelper.hpp>
#include <Controller/Logger/Logger.hpp>

namespace wxWidgets
{
  BEGIN_EVENT_TABLE(LogEntriesListCtrl, wxListCtrl)
  END_EVENT_TABLE()

  LogEntriesListCtrl::LogEntriesListCtrl(
    /*const*/ wxWindow * /*const*/ parent,
    const wxWindowID ID,
    Logger & logger//,
//      I_LogEntryOutputter * p_outputhandler,
//      I_LogFormatter * p_log_formatter,
//      enum LogLevel::MessageType logLevel
    )
    : wxListCtrl(
      (wxWindow *) parent, //wxID_ANY
      ID, wxDefaultPosition, wxDefaultSize,
      wxLC_REPORT | wxLC_VIRTUAL | wxLC_EDIT_LABELS)
    , FormattedLogEntryProcessor(logger, NULL, NULL, LogLevel::info)
    , m_logger(logger)
  {
    // Add first column
    wxListItem col0;
    col0.SetId(colID_timeStamp);
    col0.SetText( wxT("time stamp") );
    col0.SetWidth(500);
    InsertColumn(colID_timeStamp, col0);
    wxListItem col1;
    col1.SetId(colID_message);
    col1.SetText( wxT("message") );
    col1.SetWidth(200);
    InsertColumn(colID_message, col1);

    SetItemCount( m_logentries.size() );
    logger.AddFormattedLogEntryProcessor(this);
  }

  LogEntriesListCtrl::~LogEntriesListCtrl()
  {
    m_logger.Remove(this);
  }

  unsigned LogEntriesListCtrl::Log(//ostream & ostr
//    const std::string & r_stdstrMessage,
    const LogFileEntry & logfileentry,
    enum LogLevel::MessageType messageType,
    const char * const prettyFunctionFormattedFunctionName
    ) const
  {
    PersistentLogEntry persistentLogEntry = logfileentry;
    persistentLogEntry.m_std_strMessage = * logfileentry.p_std_strMessage;

    ( (container_type &) m_logentries).push_back(
      persistentLogEntry );
    const unsigned numLogEntries = m_logentries.size();
    ( (LogEntriesListCtrl *)this)->SetItemCount( numLogEntries );
    return 0;
  }

  /** Override virtual method of wxListCtrl to provide text data for virtual list*/
  wxString LogEntriesListCtrl::OnGetItemText(long item, long column) const
  {
    if( m_logentries.size() > item)
    {
      const PersistentLogEntry & logentry = m_logentries[item];
      switch(column )
      {
      case colID_timeStamp:
//        return wxWidgets::getwxString(* logentry.p_std_strMessage);
        {
        const wxString timeStamp = wxString::Format(wxT("%uh:%umin:%us.%ums"),
          logentry.hour,
          logentry.minute,
          logentry.second,
          logentry.millisecond
          );
        return //wxT("timeStamp")
          timeStamp;
        }
        break;
      case colID_message:
        return wxWidgets::getwxString(//* logentry.p_std_strMessage
          logentry.m_std_strMessage);
//        return wxT("message");
//        break;
      }
    }
    return wxT("xx");
  }
} /* namespace wxWidgets */
