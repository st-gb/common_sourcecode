/*
 * LogEntriesDialog.cpp
 *
 *  Created on: 02.04.2014
 *      Author: mr.sys
 */

#include "LogEntriesDialog.hpp"
#include <wx/sizer.h>
#include "LogEntriesListCtrl.hpp"
#include <wx/defs.h> //wxID_ANY

namespace wxWidgets
{

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
    wxWidgets::LogEntriesListCtrl * p_listCtrl = new
      wxWidgets::LogEntriesListCtrl(this, wxID_ANY, (Logger &) logger);

    wxBoxSizer * p_wxsizer = new wxBoxSizer(wxVERTICAL);
    p_wxsizer->Add(
      //p_wxlistctrl
      p_listCtrl
      //http://docs.wxwidgets.org/2.6/wx_wxsizer.html#wxsizeradd:
      //[...]can change its size in the main orientation of the wxBoxSizer -
      //where 0 stands for not changeable[...]
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
} /* namespace wxWidgets */
