/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany
 * ("Trilobyte SE") 2010-at least 2012.
 * You are allowed to modify and use the source code from Trilobyte SE for free
 * if you are not making profit directly or indirectly with it or its adaption.
 * Else you may contact Trilobyte SE. */
/*
 * wxBitmapToggleButton.cpp
 *
 *  Created on: 13.06.2012
 *      Author: Stefan
 */

//#include "wxWidgets/UserInterface/wxBitmapToggleButton.hpp"
#include "wxBitmapToggleButton.hpp"
#include <wx/window.h> //class wxWindow
#include <wx/checkbox.h> //class wxCheckBoxNameStr
#include <wx/statbmp.h> //class wxStaticBitmap
#ifdef _WIN32
  //for "GetClassInfo" not be expanded to "GetClassInfoA"
  #include <wx/msw/winundef.h>
#endif //#ifdef _WIN32

namespace wx2_9compatibility
{
  IMPLEMENT_DYNAMIC_CLASS(wx2_9compatibility::wxBitmapToggleButton, wxWindow)

  wxBitmapToggleButton::wxBitmapToggleButton()
  {
    // TODO Auto-generated constructor stub

  }

  wxBitmapToggleButton::wxBitmapToggleButton(
    wxWindow *    parent,
    wxWindowID    id,
    const wxBitmap &    label,
    const wxPoint &   pos,
    const wxSize &    size ,
    long    style ,
    const wxValidator &   val ,
    const wxString &    name
    )
  {
    Create(parent, id, label, pos, size, style, val, name);
  }

  wxBitmapToggleButton::~wxBitmapToggleButton()
  {
    // TODO Auto-generated destructor stub
  }

  // Create the control
  bool wxBitmapToggleButton::Create(
    wxWindow * parent,
    wxWindowID id,
    const wxBitmap & label,
    const wxPoint & pos , //= wxDefaultPosition
    const wxSize& size, // = wxDefaultSize
    long style,// = 0
    const wxValidator & validator,// = wxDefaultValidator
    const wxString & name// = wxCheckBoxNameStr
    )
  {
    m_p_wxcheckbox = new wxCheckBox(
//      this,
      parent,
      id,
      wxT("")
      ) ;
    m_p_wxstaticbitmap = new wxStaticBitmap(
//      this ,
      parent,
      wxID_ANY ,
      label
      ) ;
    return m_p_wxcheckbox && m_p_wxstaticbitmap;
  }
  bool wxBitmapToggleButton::Create(
    wxWindow * parent,
    wxWindowID id,
    const char * const * bitmapData,
    const wxPoint & pos,// = wxDefaultPosition
    const wxSize& size, // = wxDefaultSize
    long style,// = 0
    const wxValidator & validator,// = wxDefaultValidator
    const wxString & name// = wxCheckBoxNameStr
    )
  {
    m_p_wxcheckbox = new wxCheckBox(
//      this,
      parent,
      id,
      wxT("")
      ) ;
    m_p_wxstaticbitmap = new wxStaticBitmap(
//      this ,
      parent,
      wxID_ANY ,
      wxBitmap( bitmapData )
      ) ;
    return m_p_wxcheckbox && m_p_wxstaticbitmap;
  }
//  GetClassInfo()
//  {
//
//  }
  void wxBitmapToggleButton::SetToolTip(const wxString & wxstrToolTip) {
    m_p_wxcheckbox->SetToolTip(wxstrToolTip);
    m_p_wxstaticbitmap->SetToolTip(wxstrToolTip);
  }
//  void wxBitmapToggleButton::SetText(const wxString & wxstrText) {
//    m_p_wxcheckbox->SetLabel(wxstrText);
//  }
  wxSizerItem * wxFlexGridSizer::Add(
    wxWindow * window,
    int proportion,// = 0
    int flag,// = 0
    int border,// = 0
    wxObject * userData// = NULL
    )
  {
    LOGN( FULL_FUNC_NAME << "--begin")
    //from http://en.wikipedia.org/wiki/RTTI#C.2B.2B_Example:
    // to find whether abc_pointer is pointing to xyz type of object
    wx2_9compatibility::wxBitmapToggleButton *
      p_wx2_9compatibility_wxbitmaptogglebutton = dynamic_cast<
      wx2_9compatibility::wxBitmapToggleButton *> (window);
//    LOGN( FULL_FUNC_NAME << __FILE__ << "--" << pointer)
    LOGN( FULL_FUNC_NAME << "--class name: \"" << GetStdString(
      std::tstring(window->GetClassInfo()->GetClassName() )) << "\"")
    if (p_wx2_9compatibility_wxbitmaptogglebutton != NULL)
      return Add(
        p_wx2_9compatibility_wxbitmaptogglebutton,
        proportion,
        flag,
        border,
        userData
        );
    else
      return wxSizer::Add(
        window,
        proportion,
        flag,
        border,
        userData
        );
  }

} /* namespace wx2_9compatibility */
