/*
 * include_bitmap_toggle_button.hpp
 *
 *  Created on: 23.06.2013
 *      Author: Stefan
 */

#ifndef INCLUDE_BITMAP_TOGGLE_BUTTON_HPP_
#define INCLUDE_BITMAP_TOGGLE_BUTTON_HPP_

// >= wxWidgets version 2.9
#if (wxMAJOR_VERSION > 1 && wxMINOR_VERSION > 8)
  #define USE_WX_BITMAPTOGGLEBUTTON
#endif
#ifdef wxHAS_BITMAPTOGGLEBUTTON
  #define USE_WX_BITMAPTOGGLEBUTTON
#endif

//#ifdef USE_BITMAP_TOGGLE_BTN
  #ifdef USE_WX_BITMAPTOGGLEBUTTON
    //wxWidgets 2.9.1 has wxBitmapToggleButton but does not have
    // wxHAS_BITMAPTOGGLEBUTTON defined.
    #include <wx/tglbtn.h> //class wxBitmapToggleButton
    #define WX_BITMAP_TOGGLE_BUTTON_EVENT_MACRO EVT_TOGGLEBUTTON
    #define TOGGLE_BUTTON_OR_BUTTON_EVENT_MACRO EVT_TOGGLEBUTTON
  #else
    //class wxBitmapToggleButton
    #include <wxWidgets/UserInterface/wx2.9compatibility/wxBitmapToggleButton.hpp>
    #define WX_BITMAP_TOGGLE_BUTTON_EVENT_MACRO EVT_CHECKBOX
    #define TOGGLE_BUTTON_OR_BUTTON_EVENT_MACRO EVT_BUTTON
  #endif
//#endif

#endif /* INCLUDE_BITMAP_TOGGLE_BUTTON_HPP_ */
