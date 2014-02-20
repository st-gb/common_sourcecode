/* Do not remove this header/ copyright information.
 *
 * Copyright � Trilobyte Software Engineering GmbH, Berlin, Germany
 * ("Trilobyte SE") 2010-at least 2012.
 * You are allowed to modify and use the source code from Trilobyte SE for free
 * if you are not making profit directly or indirectly with it or its adaption.
 * Else you may contact Trilobyte SE. */
/*
 * wxTextControlDialog.hpp
 *
 *  Created on: 11.08.2011
 *      Author: Stefan
 */

#ifndef WXTEXTCONTROLDIALOG_HPP_
#define WXTEXTCONTROLDIALOG_HPP_

#include <wx/sizer.h> //class wxSizer
#include <wx/dialog.h> //Base class wxDialog
#include <wx/textctrl.h> //class wxTextCtrl
//SUPPRESS_UNUSED_VARIABLE_WARNING
#include <compiler/GCC/suppress_unused_variable.h>
#include <wx/button.h> //class wxButton

class wxTextControlDialog
  : public wxDialog
{
public:
  enum flags
  {
    OK_Button = 1,
    Retry_Button = 2
  };
    wxTextControlDialog(
      const wxString & c_r_wxstrMessage,
      const wxString & c_r_wxstrTitle = wxT(""),
      unsigned flags = OK_Button,
      long dialog_style = wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER
      )
      : wxDialog(
          NULL,
          wxID_ANY,
          c_r_wxstrTitle, //const wxString& title
          wxDefaultPosition, //const wxPoint& pos = wxDefaultPosition,
          wxDefaultSize, //const wxSize& size = wxDefaultSize,
//          wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER
          dialog_style
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

      wxBoxSizer * p_buttonsSizer = new wxBoxSizer(wxHORIZONTAL);

      if( flags & OK_Button)
      {
        wxButton * p_wxButtonOK = new wxButton(this, wxID_OK);
        p_buttonsSizer->Add(
          p_wxButtonOK,
          //"in the main orientation of the wxBoxSizer - where 0 stands for not changeable"
          0,//proportion;
          //flag
          wxEXPAND //"The item will be expanded to fill the space assigned to the item"
          );
      }
      if( flags & Retry_Button)
      {
        wxButton * p_wxButtonRetry = new wxButton(this, wxID_RETRY);
        p_buttonsSizer->Add(
          p_wxButtonRetry,
          //"in the main orientation of the wxBoxSizer - where 0 stands for not changeable"
          0,//proportion;
          //flag
          wxEXPAND //"The item will be expanded to fill the space assigned to the item"
          );
      }
      p_sizer->Add(p_buttonsSizer);
      SetSizer(p_sizer);
      //  wxd.AddChild( p_wxtextctrl);
      Layout(); //stretch to the whole client window.
      //See http://docs.wxwidgets.org/stable/wx_wxwindow.html#wxwindowfit:
//      SetClientSize(p_wxtextctrl->GetSize() );
    }
};

#endif /* WXTEXTCONTROLDIALOG_HPP_ */
