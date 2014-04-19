/*
 * LogEntriesListCtrl.cpp
 *
 *  Created on: 12.04.2014
 *      Author: mr.sys
 */

#include <wxWidgets/UserInterface/LogEntries/LogEntriesDialog.hpp>
#include <wxWidgets/UserInterface/LogEntries/LogEntriesListCtrl.hpp>

#include <wxWidgets/Controller/character_string/wxStringHelper.hpp>
#include <Controller/Logger/Logger.hpp>
/** PrettyFuntionFormattedFunctionSignature::GetClassName(...),
* PrettyFuntionFormattedFunctionSignature::GetFunctionName(...) */
#include <compiler/current_function.hpp>

namespace wxWidgets
{
  BEGIN_EVENT_TABLE(LogEntriesListCtrl, wxListCtrl)
    //http://forums.wxwidgets.org/viewtopic.php?f=1&t=3157
    EVT_SCROLLWIN(LogEntriesListCtrl::OnScroll)
  END_EVENT_TABLE()

  LogEntriesListCtrl::LogEntriesListCtrl(
    /*const*/ wxWindow * /*const*/ parent,
    const wxWindowID ID,
    Logger & logger,
    wxWidgets::LogEntriesDialog & logEntriesDialog
//      I_LogEntryOutputter * p_outputhandler,
//      I_LogFormatter * p_log_formatter,
//      enum LogLevel::MessageType logLevel
    )
    : wxListCtrl(
      (wxWindow *) parent, //wxID_ANY
      ID, wxDefaultPosition, wxDefaultSize,
      wxLC_REPORT | wxLC_VIRTUAL | wxLC_EDIT_LABELS)
    , FormattedLogEntryProcessor(logger, NULL, NULL, LogLevel::debug)
    , m_logger(logger)
    , m_logEntriesDialog(logEntriesDialog)
    , m_currentScrollPos(0)
  {
    // Add first column
    wxListItem column;

    column.SetId(colID_timeStamp);
    column.SetText( wxT("time stamp") );
    column.SetWidth(50);
    InsertColumn(colID_timeStamp, column);

    column.SetId(colID_namespaceAndClass);
    column.SetText( wxT("namespace and/or class") );
    column.SetWidth(100);
    InsertColumn(colID_namespaceAndClass, column);

    column.SetId(colID_functionName);
    column.SetText( wxT("function name") );
    column.SetWidth(50);
    InsertColumn(colID_functionName, column);

    column.SetId(colID_message);
    column.SetText( wxT("message") );
    column.SetWidth(500);
    InsertColumn(colID_message, column);

    SetItemCount( m_logentries.size() );
    logger.AddFormattedLogEntryProcessor(this);
  }

  LogEntriesListCtrl::~LogEntriesListCtrl()
  {
    m_logger.Remove(this);
  }

  void LogEntriesListCtrl::HighlightMatchingLineAndMoveThere(
      const wxString & searchFor)
  {
    //http://wiki.wxwidgets.org/WxListCtrl#Getting_the_selected_item_indexes
    long itemIndex = -1;
    long lastSeletedItemIndex = -1;
    long firstLineToSearchIn = 0;
    for (;;) {
      itemIndex = GetNextItem(
        itemIndex,
        wxLIST_NEXT_ALL,
        wxLIST_STATE_SELECTED);
      if (itemIndex == -1)
        break;
      else
        lastSeletedItemIndex = itemIndex;
    }
    if( lastSeletedItemIndex != -1 )
      firstLineToSearchIn = lastSeletedItemIndex + 1;
    if( m_logentries.size() > firstLineToSearchIn)
    {
      const std::string std_strSearchFor = wxWidgets::GetStdString(searchFor);
      container_type::const_iterator c_iter = //m_logentries.begin();
        m_logentries.begin() + firstLineToSearchIn;
      long currentItemIndex = firstLineToSearchIn;
      while( c_iter != m_logentries.end() )
      {
        if( c_iter->m_std_strMessage.find(std_strSearchFor) != std::string::npos )
        {
          //http://wiki.wxwidgets.org/WxListCtrl#Select_or_Deselect_an_Item
          SetItemState(currentItemIndex, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
          ScrollLines( currentItemIndex - m_currentScrollPos);
//          SetScrollPos(wxVERTICAL, currentItemIndex - m_currentScrollPos);
          break;
        }
        ++ c_iter;
        ++ currentItemIndex;
      }
    }
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

    persistentLogEntry.m_std_strNamespaceAndOrClassName =
      PrettyFunctionFormattedFunctionSignature::GetClassName(
      prettyFunctionFormattedFunctionName);

    persistentLogEntry.m_std_strFunctionName =
      PrettyFunctionFormattedFunctionSignature::GetFunctionName(
      prettyFunctionFormattedFunctionName);

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
      case colID_namespaceAndClass:
        return wxWidgets::getwxString(
          logentry.m_std_strNamespaceAndOrClassName);
      case colID_functionName:
        return wxWidgets::getwxString(
          logentry.m_std_strFunctionName);
      case colID_message:
        return wxWidgets::getwxString(//* logentry.p_std_strMessage
          logentry.m_std_strMessage);
//        return wxT("message");
//        break;
      }
    }
    return wxT("xx");
  }

  void LogEntriesListCtrl::OnScroll(wxScrollWinEvent & event)
  {
    int i = event.GetPosition();
    i = event.GetId();
    /** The position of scroll pos BEFORE the scroll event. */
    m_currentScrollPos = GetScrollPos(wxVERTICAL);
    m_logEntriesDialog.SetTitle( wxString::Format(
      wxT("log entries--first line:%u"),
      m_currentScrollPos)
      );

    //TODO send custom event and call GetScrollPos() in event handler
    // instead of code this below.

    wxEventType evtType= event.GetEventType();
    switch(evtType)
    {
    case 10147: //1 line up
      if(m_currentScrollPos > -1)
        m_currentScrollPos -= 1;
      break;
    case 10148: //1 line down
      m_currentScrollPos += 1;
      break;
    case 10149: //1 page up
      m_currentScrollPos += 10;
      break;
    case 10150: //1 page down
      m_currentScrollPos += 10;
      break;
    }
    /** Needed, else it immediately scrolls to top. */
    event.Skip();
    i++;
//    Refresh();
  }

} /* namespace wxWidgets */
