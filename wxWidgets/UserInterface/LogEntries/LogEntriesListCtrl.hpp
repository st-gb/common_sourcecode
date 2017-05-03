/* LogEntriesListCtrl.hpp
 *  Created on: 12.04.2014
 *      Author: mr.sys */

#ifndef LOGENTRIESLISTCTRL_HPP_
#define LOGENTRIESLISTCTRL_HPP_

#include <deque> //class std::deque (double-ended queue)
#include <wx/listctrl.h> //class wxListCtrl
#include <Controller/Logger/Appender/FormattedLogEntryProcessor.hpp>

class Logger;
//class I_LogEntryOutputter;
//class I_LogFormatter;
namespace wxWidgets
{
  class LogEntriesDialog;
}

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
  std::string m_std_strNamespaceAndOrClassName;
  std::string m_std_strFunctionName;
  std::string m_std_strMessage;
  std::string m_std_strThreadName;

  PersistentLogEntry() { }
  PersistentLogEntry(const LogFileEntry & logfileEntry)
  {
//    threadID = logfileEntry.
//    * this = logfileEntry; //obtain a full copy
    m_std_strMessage = * logfileEntry.p_std_strMessage;
    if(logfileEntry.p_std_strThreadName)
      m_std_strThreadName = * logfileEntry.p_std_strThreadName;
    threadID = logfileEntry.threadID;
    millisecond = logfileEntry.millisecond;
    second = logfileEntry.second;
    hour = logfileEntry.hour;
    minute = logfileEntry.minute;
  }
};

/**https://wiki.wxwidgets.org/Custom_Events_in_wx2.8_and_earlier#Creating_a_Custom_Event_-_Method_4 */

// Could have been DECLARE_EVENT_TYPE( MyFooCommandEvent, -1 )
// Not needed if you only use the event-type in one .cpp file
extern /*expdecl*/ const wxEventType LogCommandEvent;
 
// A custom event that transports a whole wxString.
class LogEvent: public wxCommandEvent
{
public:
	LogEvent( wxEventType commandType = LogCommandEvent, int id = 0 )
	:  wxCommandEvent(commandType, id) { }
 
	// You *must* copy here the data to be transported
	LogEvent( const LogEvent &event )
	:  wxCommandEvent(event) { this->Set( event.GetPersistentLogEntry() ); }
 
	// Required for sending with wxPostEvent()
	wxEvent* Clone() const { return new LogEvent(*this); }
 
	PersistentLogEntry GetPersistentLogEntry() const { return m_persistentLogEntry; }
	void Set( const PersistentLogEntry & persistentLogEntry ) { 
    m_persistentLogEntry = persistentLogEntry; }
 
private:
	PersistentLogEntry m_persistentLogEntry;
};
 
typedef void (wxEvtHandler::*LogEventFunction)(LogEvent &);
 
// This #define simplifies the one below, and makes the syntax less
// ugly if you want to use Connect() instead of an event table.
#define LogEventHandler(func)                                         \
	(wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)\\
	wxStaticCastEvent(LogEventFunction, &func)                    
 
// Define the event table entry. Yes, it really *does* end in a comma.
#define EVT_LOG(id, fn)                                            \
	DECLARE_EVENT_TABLE_ENTRY( LogCommandEvent, id, wxID_ANY,  \
	(wxObjectEventFunction)(wxEventFunction)                     \
	(wxCommandEventFunction) wxStaticCastEvent(                  \
	LogEventFunction, &fn ), (wxObject*) NULL ),
 
// Optionally, you can do a similar #define for EVT_MYFOO_RANGE.
#define EVT_MYFOO_RANGE(id1,id2, fn)                                 \
	DECLARE_EVENT_TABLE_ENTRY( MyFooCommandEvent, id1, id2,      \\
	MyFooEventHandler(fn), (wxObject*) NULL ),
 
// If you want to use the custom event to send more than one sort
// of data, or to more than one place, make it easier by providing
// named IDs in an enumeration.
enum { Foo_DoFirstThing = 1, Foo_DoSecondThing, Foo_DoThirdThing };

namespace wxWidgets
{

  class LogEntriesListCtrl
    : public wxListCtrl,
    public FormattedLogEntryProcessor
  {
    bool m_rightClickProcessed;
    static unsigned s_GUIthreadID;
    enum columnIndices { colID_timeStamp, colID_threadName, colID_namespaceAndClass,
      colID_functionName, colID_message };
      enum windowIDs { ID_MakeFontLarger, ID_MakeFontSmaller, RightClick };
    //TODO is this a performant data structure for OnGetItemText(...)?
    typedef std::deque<PersistentLogEntry> container_type;
    container_type m_logentries;
    Logger & m_logger;
    int m_currentScrollPos;
    int m_lastSeletedItemIndex;
    wxWidgets::LogEntriesDialog & m_logEntriesDialog;
  public:
    LogEntriesListCtrl(
      /*const*/ wxWindow * /*const*/ parent,
      const wxWindowID ID,
      Logger & logger,
      wxWidgets::LogEntriesDialog & logEntriesDialog,
      const unsigned GUIthreadID
//      I_LogEntryOutputter * p_outputhandler,
//      I_LogFormatter * p_log_formatter,
//      enum LogLevel::MessageType logLevel
      );
    virtual
    ~LogEntriesListCtrl();

    inline void AddPersistentLogEntry(const PersistentLogEntry & persistentLogEntry)
    {
      //TODO insert entry based on timestamp
      ( (container_type &) m_logentries).push_back(
        persistentLogEntry );
      const unsigned numLogEntries = m_logentries.size();
      ( (LogEntriesListCtrl *)this)->SetItemCount( numLogEntries );
    }
    inline void AddAccelerators();
    inline void BuildGUI();
    void ClearLogEntries();
    void HighlightMatchingLineAndMoveThere(const SearchParams & searchParams );
    void HighlightPreviousMatchingLineAndMoveThere(const SearchParams & searchParams );
    unsigned Log(//ostream & ostr
  //    const std::string & r_stdstrMessage,
      const LogFileEntry & logfileentry,
      enum LogLevel::MessageType messageType =
        LogLevel::info,
      const char * const prettyFunctionFormattedFunctionName = NULL
      ) const;
    inline void UpdateTitleBar();
    wxString OnGetItemText(long item, long column) const;
    void OnClose( wxCloseEvent & wxcmd );
    void OnListItemSelected(wxListEvent& event);
    void OnMouseWheel(wxMouseEvent & mouseEvent);
    void OnScroll(wxScrollWinEvent & event);
    void OnLogEntry( LogEvent & event);
    void OnRightClick(wxListEvent & evt);
    void OnContextMenu(wxContextMenuEvent & event);
    void OnMakeFontLarger(wxCommandEvent &);
    void OnMakeFontSmaller(wxCommandEvent &);
    void ShowPopupMenu(const wxPoint & point);

    /** For receiving messages/ for callback of OnGetItemText(...). */
    DECLARE_EVENT_TABLE()
  };

} /* namespace wxWidgets */

#endif /* LOGENTRIESLISTCTRL_HPP_ */
