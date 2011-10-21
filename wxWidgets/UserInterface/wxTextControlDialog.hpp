/*
 * wxTextControlDialog.hpp
 *
 *  Created on: 11.08.2011
 *      Author: Stefan
 */

#ifndef WXTEXTCONTROLDIALOG_HPP_
#define WXTEXTCONTROLDIALOG_HPP_

#include <wx/dialog.h> //Base class wxDialog
//SUPPRESS_UNUSED_VARIABLE_WARNING
#include <preprocessor_macros/suppress_unused_variable.h>

class wxTextControlDialog
  : public wxDialog
{
public:
    wxTextControlDialog(const wxString & c_r_wxstrMessage,
        const wxString & c_r_wxstrTitle)
      : wxDialog(
          NULL,
          wxID_ANY,
          c_r_wxstrTitle, //const wxString& title
          wxDefaultPosition, //const wxPoint& pos = wxDefaultPosition,
          wxDefaultSize, //const wxSize& size = wxDefaultSize,
          wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER
          )
    {
      wxTextCtrl * p_wxtextctrl = new wxTextCtrl(
        this //wxWindow* parent
        , wxID_ANY //wxWindowID id
        , c_r_wxstrMessage //const wxString& value = ""
        , wxDefaultPosition //const wxPoint& pos = wxDefaultPosition,
        , wxDefaultSize //const wxSize& size = wxDefaultSize
        , wxTE_READONLY | wxTE_MULTILINE //long style = 0
        );
      SUPPRESS_UNUSED_VARIABLE_WARNING(p_wxtextctrl)

      wxBoxSizer * p_sizer = new wxBoxSizer(wxVERTICAL);
      p_sizer->Add(
        p_wxtextctrl,
        1,//proportion
        wxEXPAND);

//      if( flags == OK_BUTTON)
//      {
//        wxButtonOK = new wxButton
//        p_sizer->Add(
//          wxButtonOK,
//          1,//proportion
//          wxEXPAND);
//      }
      SetSizer(p_sizer);
      //  wxd.AddChild( p_wxtextctrl);
      Layout(); //stretch to the whole client window.
      //See http://docs.wxwidgets.org/stable/wx_wxwindow.html#wxwindowfit:
//      SetClientSize(p_wxtextctrl->GetSize() );
    }
};

#endif /* WXTEXTCONTROLDIALOG_HPP_ */
