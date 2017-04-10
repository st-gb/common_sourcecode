/*
 * LogEntriesDialog.cpp
 *
 *  Created on: 02.04.2014
 *      Author: mr.sys
 */

#include "LogEntriesDialog.hpp"
#include "LogEntriesListCtrl.hpp"

#include <wx/defs.h> //wxID_ANY
#include <wx/sizer.h> //class wxSizer
#include <wx/button.h> //class wxButton
#include <wx/menu.h> //class wxMenu
#include <preprocessor_macros/logging_preprocessor_macros.h> //LOGN

namespace wxWidgets
{

  BEGIN_EVENT_TABLE(LogEntriesDialog, wxDialog)
    EVT_BUTTON( ClearLogEntriesButton, LogEntriesDialog::OnClearLogEntriesButton)
    EVT_BUTTON( goToNextMatchButton, LogEntriesDialog::OnGoToNextMatchButton)
    EVT_BUTTON( goToPreviousMatchButton, LogEntriesDialog::OnGoToPreviousMatchButton)
    EVT_CLOSE(LogEntriesDialog::OnClose)
  END_EVENT_TABLE()

  enum eventIDs { searchInMessage, searchInFunctionName };

  /** Adapted from http://wiki.wxwidgets.org/WxMenu#PopUp-menus */
  void LogEntriesDialog::OnContextMenuMouseButtonDown(wxMouseEvent & evt)
  {
    //LOGN_DEBUG("begin--m_searchInFunctionName:" << m_searchInFunctionName)
    //void *data = reinterpret_cast<void *>(evt.GetItem().GetData());
    wxMenu mnu;
//      mnu.SetClientData( data );
    wxMenuItem * item;
    item = mnu.AppendCheckItem(searchInMessage /*ID_SOMETHING*/,
      wxT("search in Message") );
    item->Check(m_searchParams.IsSearchedInMessage() );
    item = mnu.AppendCheckItem(searchInFunctionName,
        wxT("search in function name") );
    item->Check(m_searchParams.IsSearchedInFunctionName() );
    mnu.Connect(wxEVT_COMMAND_MENU_SELECTED,
      (wxObjectEventFunction) & LogEntriesDialog::OnPopupClick, NULL, this);
    PopupMenu(&mnu);
//    int i = 0;
//    m_p_messageToSearch->SetLabel(wxT("fdfd") );
  }

  /** Adapted from http://wiki.wxwidgets.org/WxMenu#PopUp-menus */
  void LogEntriesDialog::OnPopupClick(wxCommandEvent & evt)
  {
  //      void * data = static_cast<wxMenu *>(evt.GetEventObject())->GetClientData();
    switch( evt.GetId() ) {
      case searchInMessage:
        m_searchParams.SetSearchInMessage(evt.IsChecked() );
        break;
      case searchInFunctionName:
        m_searchParams.SetSearchInFunctionName(evt.IsChecked() );
         break;
     default:
      break;
    }
    //LOGN_DEBUG("end--m_searchInFunctionName:" << m_searchInFunctionName)
  }

  LogEntriesDialog::LogEntriesDialog(const Logger & logger, const unsigned GUIthreadID)
    : wxDialog(
      NULL //wxWindow * parent
       ,wxID_ANY //wxWindowID id
       , wxT("log entries") //const wxString & title//,
       , wxDefaultPosition //const wxPoint& pos = wxDefaultPosition,
       , wxDefaultSize //const wxSize& size = wxDefaultSize,
//       long style = wxDEFAULT_DIALOG_STYLE,
       , wxRESIZE_BORDER | wxDEFAULT_DIALOG_STYLE
//       const wxString& name = wxDialogNameStr
      )
  {
    // TODO add a virtual list control
    m_p_logEntriesListCtrl = new
      wxWidgets::LogEntriesListCtrl(
        this,
        /*wxID_ANY*/ logEntriesListCtrl,
        (Logger &) logger,
        (wxWidgets::LogEntriesDialog &) * this, 
        GUIthreadID);

    wxBoxSizer * p_wxsizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer * p_wxsizerActions = new wxBoxSizer(wxHORIZONTAL);

    wxButton * p_clearLogEntriesButton = new wxButton(
      this,
      ClearLogEntriesButton,
      wxT("clear log entries") );

    wxButton * p_goToPreviousMatch = new wxButton(
        this,
        goToPreviousMatchButton,
        wxT("<") );
    p_goToPreviousMatch->SetToolTip( wxT("go to previous match") );
    wxButton * p_goToNextMatch = new wxButton(
      this,
      goToNextMatchButton,
      wxT(">") );
    p_goToNextMatch->SetToolTip( wxT("go to NEXT match") );

    m_p_messageToSearch = new wxTextCtrl(
        this,
        wxID_ANY
        );
    m_p_messageToSearch->Connect(
      wxEVT_RIGHT_DOWN /*int eventType*/,
      //wxObjectEventFunction func,
      (wxObjectEventFunction) & wxWidgets::LogEntriesDialog::OnContextMenuMouseButtonDown,
      /*wxObject *userData = (wxObject *)*/ NULL,
      /*wxEvtHandler *eventSink = (wxEvtHandler* */ this
      );
    m_p_messageToSearch->SetToolTip(
        wxT("text to search in field/ column \"message\" (will be highlighted)") );
    p_wxsizerActions->Add(
      p_clearLogEntriesButton
      /** http://docs.wxwidgets.org/2.6/wx_wxsizer.html#wxsizeradd:
      * [...]can change its size in the main orientation of the wxBoxSizer -
      * where 0 stands for not changeable[...] */
      , 0
      , wxSTRETCH_NOT
      , 0
      );
    p_wxsizerActions->Add(
      m_p_messageToSearch
      /** http://docs.wxwidgets.org/2.6/wx_wxsizer.html#wxsizeradd:
      * [...]can change its size in the main orientation of the wxBoxSizer -
      * where 0 stands for not changeable[...] */
      , 1
      , wxEXPAND | wxALL
      , 0
      );

    p_wxsizerActions->Add(
      p_goToPreviousMatch
      /** http://docs.wxwidgets.org/2.6/wx_wxsizer.html#wxsizeradd:
      * [...]can change its size in the main orientation of the wxBoxSizer -
      * where 0 stands for not changeable[...] */
      , 0
      , wxSTRETCH_NOT
      , 0
      );
    p_wxsizerActions->Add(
      p_goToNextMatch
      /** http://docs.wxwidgets.org/2.6/wx_wxsizer.html#wxsizeradd:
      * [...]can change its size in the main orientation of the wxBoxSizer -
      * where 0 stands for not changeable[...] */
      , 0
      , wxSTRETCH_NOT
      , 0
      );

    p_wxsizer->Add(
      p_wxsizerActions
      /** http://docs.wxwidgets.org/2.6/wx_wxsizer.html#wxsizeradd:
      * [...]can change its size in the main orientation of the wxBoxSizer -
      * where 0 stands for not changeable[...] */
      , 0
      ,
      wxEXPAND |
      wxALL
      , 0
      );

    m_p_functionNameToSearch = new wxTextCtrl(
        this,
        wxID_ANY
        );

    p_wxsizer->Add(
      m_p_functionNameToSearch
      /** http://docs.wxwidgets.org/2.6/wx_wxsizer.html#wxsizeradd:
      * [...]can change its size in the main orientation of the wxBoxSizer -
      * where 0 stands for not changeable[...] */
      , 0
      ,
      wxEXPAND |
      wxALL
      , 0
      );

    p_wxsizer->Add(
      //p_wxlistctrl
      m_p_logEntriesListCtrl
      /** http://docs.wxwidgets.org/2.6/wx_wxsizer.html#wxsizeradd:
      * [...]can change its size in the main orientation of the wxBoxSizer -
      * where 0 stands for not changeable[...] */
      , 1
      , wxEXPAND |
      //wxFIXED_MINSIZE |
      wxALL
      , 0
      );
    SetSizer(p_wxsizer);
    Layout();
    SetAutoLayout(true /*bool autoLayout*/);
  }

  LogEntriesDialog::~LogEntriesDialog()
  {
    // TODO Auto-generated destructor stub
  }

  void LogEntriesDialog::OnClearLogEntriesButton(wxCommandEvent & evt)
  {
    m_p_logEntriesListCtrl->ClearLogEntries();
  }

  void LogEntriesDialog::OnGoToNextMatchButton(wxCommandEvent & evt)
  {
    //LOGN_DEBUG("begin--m_searchInFunctionName:" << m_searchInFunctionName)
    const wxString & value = m_p_messageToSearch->GetValue();
    /** Content is L"m\303\266gen" for "moegen" */
    m_searchParams.SetSearchString(value);
    //LOGN_DEBUG("m_searchInFunctionName:" << m_searchInFunctionName)
    m_p_logEntriesListCtrl->HighlightMatchingLineAndMoveThere(m_searchParams);
  }

  void LogEntriesDialog::OnGoToPreviousMatchButton(wxCommandEvent & evt)
  {
    const wxString & value = m_p_messageToSearch->GetValue();
    m_searchParams.SetSearchString(value);
    m_p_logEntriesListCtrl->HighlightPreviousMatchingLineAndMoveThere(m_searchParams);
  }

  void LogEntriesDialog::OnClose( wxCloseEvent & wxcmd )
  {
    Destroy();
  }
} /* namespace wxWidgets */
