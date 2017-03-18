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
#include <wx/menu.h> //class wxMenu

#include "Controller/TranslationControllerBase.hpp"

//https://wiki.wxwidgets.org/Custom_Events_in_wx2.8_and_earlier#Creating_a_Custom_Event_-_Method_4
const wxEventType LogCommandEvent = wxNewEventType();

unsigned wxWidgets::LogEntriesListCtrl::s_GUIthreadID = 0;

namespace wxWidgets
{
  BEGIN_EVENT_TABLE(LogEntriesListCtrl, wxListCtrl)
    EVT_LIST_ITEM_SELECTED(LogEntriesDialog::logEntriesListCtrl, 
      LogEntriesListCtrl::OnListItemSelected)
//    EVT_LIST_ITEM_DESELECTED(LogEntriesDialog::logEntriesListCtrl, LogEntriesListCtrl::OnListItemDeselected)
//    EVT_SCROLLWIN_THUMBRELEASE()
    //http://forums.wxwidgets.org/viewtopic.php?f=1&t=3157
    EVT_SCROLLWIN(LogEntriesListCtrl::OnScroll)
    /** Non-scrollbar scrolling via mouse, touchpad  etc. */
    EVT_MOUSEWHEEL(LogEntriesListCtrl::OnMouseWheel)
    //from https://wiki.wxwidgets.org/Custom_Events_in_wx2.8_and_earlier#Creating_a_Custom_Event_-_Method_4
    EVT_LOG( wxID_ANY, LogEntriesListCtrl::OnLogEntry )
    EVT_CLOSE(LogEntriesListCtrl::OnClose)
    // or EVT_MYFOO_RANGE( Foo_DoFirstThing, Foo_DoThirdThing, MyDestination::DoSomething )
    // or EVT_MYFOO( Foo_DoFirstThing, MyDestination::DoFirstThing)
    // or EVT_MYFOO( Foo_DoSecondThing, MyDestination::DoSecondThing)
    // or EVT_MYFOO( Foo_DoThirdThing, MyDestination::DoThirdThing)
    /**http://stackoverflow.com/questions/14487102/wxwidgets-contextmenu-popup */
    EVT_LIST_ITEM_RIGHT_CLICK(
      /** Needs to be the ID of _this_ list ctrl?! */
      LogEntriesDialog::logEntriesListCtrl, 
      LogEntriesListCtrl::OnRightClick)
    EVT_CONTEXT_MENU(LogEntriesListCtrl::OnContextMenu)
    EVT_MENU(ID_MakeFontLarger, LogEntriesListCtrl::OnMakeFontLarger )
    EVT_MENU(ID_MakeFontSmaller, LogEntriesListCtrl::OnMakeFontSmaller )
  END_EVENT_TABLE()

  LogEntriesListCtrl::LogEntriesListCtrl(
    /*const*/ wxWindow * /*const*/ parent,
    const wxWindowID ID,
    Logger & logger,
    wxWidgets::LogEntriesDialog & logEntriesDialog,
    const unsigned GUIthreadID
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
    , m_lastSeletedItemIndex(-1)
  {
    s_GUIthreadID = GUIthreadID;
    // Add first column
    wxListItem column;

    column.SetId(colID_timeStamp);
    column.SetText( wxT("time stamp") );
    column.SetWidth(50);
    InsertColumn(colID_timeStamp, column);

    column.SetId(colID_threadName);
    column.SetText( wxT("thread name or ID") );
    column.SetWidth(70);
    InsertColumn(colID_threadName, column);
    
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
      const SearchParams & searchParams )
  {
    //http://wiki.wxwidgets.org/WxListCtrl#Getting_the_selected_item_indexes
//    long itemIndex = -1;
    long lastSeletedItemIndex = -1;
    long firstLineToSearchIn = 0;
//    for (;;) {
//      itemIndex = GetNextItem(
//        itemIndex,
//        wxLIST_NEXT_ALL,
//        wxLIST_STATE_SELECTED);
//      if (itemIndex == -1)
//        break;
//      else
//        lastSeletedItemIndex = itemIndex;
//    }
    lastSeletedItemIndex = m_lastSeletedItemIndex;
    if( lastSeletedItemIndex != -1 )
      firstLineToSearchIn = lastSeletedItemIndex + 1;
    const int numLogEntries = m_logentries.size();
    if( numLogEntries > firstLineToSearchIn)
    {
      const std::string std_strSearchFor = wxWidgets::GetStdString(
        searchParams.GetSearchString() );
      container_type::const_iterator c_iter = //m_logentries.begin();
        m_logentries.begin() + firstLineToSearchIn;
      long currentItemIndex = firstLineToSearchIn;
      const bool searchInMessage = searchParams.IsSearchedInMessage();
      const bool searchInFunctionName = searchParams.IsSearchedInFunctionName();
      bool noMatchingMessageFound = false;
      bool matchingLineFound = false;
      while( c_iter != m_logentries.end() )
      {
//        noMatchingMessageFound = true;
        //matchingLineFound = false;
        if( searchInMessage )
        {
          const std::string & std_strMessage = c_iter->m_std_strMessage;
          if( std_strMessage.find(std_strSearchFor) != std::string::npos )
          {
            matchingLineFound = true;
          }
        }
        if( ! matchingLineFound && searchInFunctionName )
        {
          const std::string & std_strFunctionName = c_iter->m_std_strFunctionName;
          if( std_strFunctionName.find(std_strSearchFor) != std::string::npos )
          {
            matchingLineFound = true;
          }
        }
        if(matchingLineFound)
        {
          //http://wiki.wxwidgets.org/WxListCtrl#Select_or_Deselect_an_Item
          SetItemState(currentItemIndex, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
          const int numLinesToScroll = currentItemIndex - m_currentScrollPos;
          //e.g. current item index: 100, current scroll pos: 101
          //TODO scrolling is not done correctly
          ScrollLines( numLinesToScroll);
          m_currentScrollPos = /*m_currentScrollPos + numLinesToScroll*/
            currentItemIndex;
          m_lastSeletedItemIndex = currentItemIndex;
//          SetScrollPos(wxVERTICAL, m_currentScrollPos);
          Refresh();
          break;
        }
        ++ c_iter;
        ++ currentItemIndex;
      }
    }
  }

  void LogEntriesListCtrl::HighlightPreviousMatchingLineAndMoveThere(
    const SearchParams & searchParams )
  {
    long lastSeletedItemIndex = -1;
    long firstLineToSearchIn = 0;
    lastSeletedItemIndex = m_lastSeletedItemIndex;

    const int numLogEntries = m_logentries.size();

    if( lastSeletedItemIndex == -1 )
      firstLineToSearchIn = numLogEntries - 1;
    else
      firstLineToSearchIn = m_lastSeletedItemIndex - 1;

    if( numLogEntries > firstLineToSearchIn)
    {
      const std::string std_strSearchFor = wxWidgets::GetStdString(
        searchParams.GetSearchString() );
      const bool searchInMessage = searchParams.IsSearchedInMessage();
      const bool searchInFunctionName = searchParams.IsSearchedInFunctionName();

      container_type::const_reverse_iterator c_iter = //m_logentries.begin();
        m_logentries.rbegin() +
        //e.g. 10 - last line (9) - 1 = move by 0 positions after rbegin
        (numLogEntries - firstLineToSearchIn - 1);

      long currentItemIndex = firstLineToSearchIn;
      bool matchingLineFound = false;
      while( c_iter != m_logentries.rend() )
      {
        //matchingLineFound = false;
        if( searchInMessage )
        {
          const std::string & std_strMessage = c_iter->m_std_strMessage;
          if( std_strMessage.find(std_strSearchFor) != std::string::npos )
          {
            matchingLineFound = true;
          }
        }
        if( ! matchingLineFound && searchInFunctionName )
        {
          const std::string & std_strFunctionName = c_iter->m_std_strFunctionName;
          if( std_strFunctionName.find(std_strSearchFor) != std::string::npos )
          {
            matchingLineFound = true;
          }
        }
        if(matchingLineFound)
        {
          //http://wiki.wxwidgets.org/WxListCtrl#Select_or_Deselect_an_Item
          SetItemState(currentItemIndex, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
          const int numLinesToScroll = currentItemIndex - m_currentScrollPos;
          ScrollLines( numLinesToScroll);
          m_currentScrollPos = currentItemIndex;
          m_lastSeletedItemIndex = currentItemIndex;
//          SetScrollPos(wxVERTICAL, m_currentScrollPos);
          Refresh();
          break;
        }
        ++ c_iter;
        -- currentItemIndex;
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
    if(logfileentry.p_std_strThreadName)
      persistentLogEntry.m_std_strThreadName = * logfileentry.p_std_strThreadName;

    persistentLogEntry.m_std_strNamespaceAndOrClassName =
      PrettyFunctionFormattedFunctionSignature::GetClassName(
      prettyFunctionFormattedFunctionName);

    persistentLogEntry.m_std_strFunctionName =
      PrettyFunctionFormattedFunctionSignature::GetFunctionName(
      prettyFunctionFormattedFunctionName);

    const DWORD dwCurrentThreadNumer = OperatingSystem::GetCurrentThreadNumber();
    if( dwCurrentThreadNumer == s_GUIthreadID )
    {
      ( (LogEntriesListCtrl *) this)->AddPersistentLogEntry(persistentLogEntry);
    }
    else
    {
      /** Don't access GUI controls from another than the UI thread (else hangup/ crash) */
//      int i = 0;
      //https://wiki.wxwidgets.org/Custom_Events_in_wx2.8_and_earlier#Creating_a_Custom_Event_-_Method_4
      LogEvent event( LogCommandEvent /*, Foo_DoFirstThing*/ );
      // Add the exciting data. You can put anything you like
      // into the class: ints, structs, binary data...
      event.Set( persistentLogEntry );
      wxPostEvent( (LogEntriesListCtrl *) this, event );
    }
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
      case colID_threadName :
        return wxWidgets::getwxString(
          logentry.m_std_strThreadName) + 
          wxString::Format(wxT(" (%u)"), logentry.threadID);
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

  void LogEntriesListCtrl::OnLogEntry( LogEvent & event)
  {
//   int i = 0;
    AddPersistentLogEntry(event.GetPersistentLogEntry() );
  }
  
  void LogEntriesListCtrl::OnClose( wxCloseEvent & wxcmd )
  {
    m_logger.Remove(this);
  }
    
  void LogEntriesListCtrl::OnListItemSelected(wxListEvent & event)
  {
    m_lastSeletedItemIndex = event.GetIndex();
  }
  
  void LogEntriesListCtrl::OnMakeFontLarger(wxCommandEvent & cmdevt)
  {
    wxFont font = GetFont();
    int fontPointSize = font.GetPointSize();
    font.SetPointSize(++fontPointSize);
    SetFont(font);
    //TODO update list ctrl?
//    Layout();
  }
  
  void LogEntriesListCtrl::OnMakeFontSmaller(wxCommandEvent & cmdevt)
  {
    wxFont font = GetFont();
    int fontPointSize = font.GetPointSize();
    if( fontPointSize > 1)
    {
      font.SetPointSize(--fontPointSize);
      SetFont(font);
      //TODO update list ctrl?
//      Layout();
    }
  }
  
  void LogEntriesListCtrl::ShowPopupMenu(const wxPoint & point)
  {
    /**from http://stackoverflow.com/questions/14487102/wxwidgets-contextmenu-popup
    *  Show popupmenu at position */
    wxMenu menu(wxT(""));
//    const int col = event.GetColumn();
//    const int index = event.GetIndex();
    menu.Append(ID_MakeFontLarger, wxT("make font &larger\tCTRL++"));
    menu.Append(ID_MakeFontSmaller, wxT("make font &smaller\tCTRL+-"));
    PopupMenu(& menu, point );
  }
  
  void LogEntriesListCtrl::OnContextMenu(wxContextMenuEvent & event)
  {
    ShowPopupMenu(event.GetPosition());
  }

  void LogEntriesListCtrl::OnRightClick(wxListEvent & event)
  {
    ShowPopupMenu(event.GetPoint() );
  }

  void LogEntriesListCtrl::OnMouseWheel(wxMouseEvent & mouseEvent)
  {
    if( mouseEvent.GetWheelAxis() == wxMOUSE_WHEEL_VERTICAL)
    {
      int numLinesToScroll = mouseEvent.GetLinesPerAction();
      if( mouseEvent.GetWheelRotation() > 0 )
        numLinesToScroll *= -1;
//      m_currentScrollPos += numLinesToScroll;
      ScrollLines(numLinesToScroll);
    }
  }
  
  void LogEntriesListCtrl::OnScroll(wxScrollWinEvent & event)
  {
    /** see http://docs.wxwidgets.org/3.1.0/classwx_scroll_win_event.html#af6652b2f8110049e9c7208237a641960
    * int wxScrollWinEvent:GetPosition():"Returns the position of the scrollbar 
    * for the thumb track and release events. " */
//    int pos = event.GetPosition();
//    int id = event.GetId();
    /** The position of scroll pos BEFORE the scroll event. */
    m_currentScrollPos = GetScrollPos(wxVERTICAL);
    m_logEntriesDialog.SetTitle( wxString::Format(
      wxT("log entries--first line:%u/%ulines"),
      m_currentScrollPos, GetItemCount() )
      );

    //TODO send custom event and call GetScrollPos() in event handler
    // instead of code this below.

    wxEventType evtType = event.GetEventType();
    //from wx/event.h
//    int nnn = wxEVT_SCROLLWIN_LINEUP;
    //TODO is this "switch" construct used at all??
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
//    i++;
//    Refresh();
  }

} /* namespace wxWidgets */
