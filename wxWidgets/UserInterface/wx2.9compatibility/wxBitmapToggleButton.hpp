/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany
 * ("Trilobyte SE") 2010-at least 2012.
 * You are allowed to modify and use the source code from Trilobyte SE for free
 * if you are not making profit directly or indirectly with it or its adaption.
 * Else you may contact Trilobyte SE. */
/*
 * wxBitmapToggleButton.hpp
 *
 *  Created on: 13.06.2012
 *      Author: Stefan
 */

#ifndef WXBITMAPTOGGLEBUTTON_HPP_
#define WXBITMAPTOGGLEBUTTON_HPP_

//#include <wx/gdicmn.h> //wxDefaultSize
#include <wx/bitmap.h>
#include <wx/validate.h> //wxDefaultValidator
#include <wx/checkbox.h> //wxCheckBoxNameStr
#include <wx/sizer.h> //class wxFlexGridSizer
#include <preprocessor_macros/logging_preprocessor_macros.h> //LOGN()
#include <wx/version.h> //wxMAJOR_VERSION
#ifdef _WIN32
  #include <wx/msw/winundef.h> //avoid "GetClassInfo" -> "GetClassInfoA"
#endif //#ifdef _WIN32
//see wxWidgets-2.8.10/include/wx/msw/tglbtn.h
// extern WXDLLIMPEXP_DATA_CORE(const wxChar) wxCheckBoxNameStr[];
//see wxWidgets-2.9.1/include/wx/msw/tglbtn.h :
// extern WXDLLIMPEXP_DATA_CORE(const char) wxCheckBoxNameStr[];

#if wxMAJOR_VERSION > 1 
  #if wxMAJOR_VERSION == 2
    #if wxMINOR_VERSION > 8 // wxWidgets version >= 2.9
      typedef char wxCheckBoxNameStr_Type;
    #else // wxWidgets version element of [2.0 ... 2.8]
      typedef wxChar wxCheckBoxNameStr_Type;
    #endif
  #else // wxWidgets version >= 3.0
    typedef char wxCheckBoxNameStr_Type;
  #endif
#else //wxWidgets version = 1.x
  typedef wxChar wxCheckBoxNameStr_Type;
#endif
extern WXDLLIMPEXP_DATA_CORE(const wxCheckBoxNameStr_Type) wxCheckBoxNameStr[];

//forward decl.
class wxWindow;
//class wxWindowID;
class wxBitmap;
class wxPoint;
class wxSize;
class wxValidator;
class wxString;
class wxStaticBitmap;

namespace wx2_9compatibility
{
  //emulates a wxWidgets bitmap toggle starting from wx2.9.1?
  class wxBitmapToggleButton
    : public wxWindow
  {
  public:
    wxCheckBox * m_p_wxcheckbox;
    wxStaticBitmap * m_p_wxstaticbitmap;

    wxBitmapToggleButton();
    wxBitmapToggleButton(
      wxWindow *    parent,
      wxWindowID    id,
      const wxBitmap &    label,
//      const wxString & text,
      const wxPoint &   pos = wxDefaultPosition,
      const wxSize &    size = wxDefaultSize,
      long    style = 0,
      const wxValidator &   val = wxDefaultValidator,
      const wxString &    name = wxCheckBoxNameStr
      );
    virtual
    ~wxBitmapToggleButton();
    // Create the control
    bool Create(
      wxWindow * parent,
      wxWindowID id,
      const wxBitmap& label,
      const wxPoint& pos = wxDefaultPosition,
      const wxSize& size = wxDefaultSize, long style = 0,
      const wxValidator& validator = wxDefaultValidator,
      const wxString& name = wxCheckBoxNameStr);
    bool Create(
      wxWindow *parent,
      wxWindowID id,
      const char* const* bitmapData,
      const wxPoint& pos = wxDefaultPosition,
      const wxSize& size = wxDefaultSize, long style = 0,
      const wxValidator& validator = wxDefaultValidator,
      const wxString& name = wxCheckBoxNameStr);
//    void Create()
//    {
//    }
    bool GetValue(){
      return m_p_wxcheckbox->IsChecked();
    }
//    void SetText(const wxString & wxstrText);
    void SetToolTip(const wxString & wxstrToolTip);
    void SetValue(bool b)
    {
      m_p_wxcheckbox->SetValue(b);
    }
    //For getting the class name at runtime.
    DECLARE_DYNAMIC_CLASS(wx2_9compatibility::wxBitmapToggleButton)
  };

    //class to enable "Add(wx2_9compatibility::wxBitmapToggleButton"
  class wxFlexGridSizer
    : public ::wxFlexGridSizer
  {
  public:
    //Copied from "wxSizer::Add(..." in "sizer.h".
    wxFlexGridSizer( int cols, int vgap = 0, int hgap = 0 )
      : ::wxFlexGridSizer::wxFlexGridSizer(cols, vgap, hgap )
    {
    }
    //inline
      wxSizerItem * Add(
//      wxWindow * window,
        wx2_9compatibility::wxBitmapToggleButton * p_wxbitmaptogglebutton,
        int proportion = 0,
        int flag = 0,
        int border = 0,
        wxObject* userData = NULL
        )
    {
      LOGN( FULL_FUNC_NAME )
      wxSizer::Add( new wxSizerItem( //window
        (wxWindow *) p_wxbitmaptogglebutton->m_p_wxcheckbox
        , proportion, flag, border, userData ) );
      return wxSizer::Add(
        new wxSizerItem( //window
          (wxWindow *) p_wxbitmaptogglebutton->m_p_wxstaticbitmap
          , proportion
          , flag
          , border
          , userData
          )
        );
    }
    wxSizerItem * Add(
      wxWindow * window,
      int proportion = 0,
      int flag = 0,
      int border = 0,
      wxObject* userData = NULL
      );
  };
} /* namespace wx2_9compatibility */
#endif /* WXBITMAPTOGGLEBUTTON_HPP_ */
