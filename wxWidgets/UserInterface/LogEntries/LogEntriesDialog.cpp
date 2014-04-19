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

namespace wxWidgets
{

  enum winIDs { ClearLogEntriesButton, goToPreviousMatchButton, goToNextMatchButton};

  BEGIN_EVENT_TABLE(LogEntriesDialog, wxDialog)
    EVT_BUTTON( ClearLogEntriesButton, LogEntriesDialog::OnClearLogEntriesButton)
    EVT_BUTTON( goToNextMatchButton, LogEntriesDialog::OnGoToNextMatchButton)
    EVT_CLOSE(LogEntriesDialog::OnClose)
  END_EVENT_TABLE()

  LogEntriesDialog::LogEntriesDialog(const Logger & logger)
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
      wxWidgets::LogEntriesListCtrl(this, wxID_ANY, (Logger &) logger,
      (wxWidgets::LogEntriesDialog &) * this);

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
    wxButton * p_goToNextMatch = new wxButton(
        this,
        goToNextMatchButton,
        wxT(">") );

    m_p_messageToSearch = new wxTextCtrl(
        this,
        wxID_ANY
        );
    m_p_messageToSearch->SetToolTip(
        wxT("highlight") );
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
    const wxString & value = m_p_messageToSearch->GetValue();
    m_p_logEntriesListCtrl->HighlightMatchingLineAndMoveThere(value);
  }

  void LogEntriesDialog::OnClose( wxCloseEvent & wxcmd )
  {
    Destroy();
  }
} /* namespace wxWidgets */
