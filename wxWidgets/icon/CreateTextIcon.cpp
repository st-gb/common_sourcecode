/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */
/*
 * CreateTextIcon.cpp
 *
 *  Created on: Nov 22, 2010
 *      Author: Stefan
 */
#include <wx/bitmap.h> //for class wxBitmap
#include <wx/dcmemory.h> //for class wxMemoryDC
#include <wx/icon.h> //class wxIcon
#include <wxWidgets/icon/IconDrawer.hpp> //FillWhiteIfMonochromeBitmap_Inline(...)

#include <windef.h> //BYTE

void CreateTextIcon( wxIcon & icon, const wxString & r_wxstr )
{
  //  BYTE byWidth = 32 , byHeight = 32 ;
  BYTE byWidth = 16 , byHeight = 16 ;
  wxBitmap wxbitmap(
    byWidth //int width
    , byHeight //int height
    , 1//int depth = -1
    ) ;
  //  wxMask wxmask(wxbitmapMask) ;
  //  wxbitmap.SetMask( & wxmask) ;
    wxMemoryDC wxmemorydc ;
    //http://docs.wxwidgets.org/2.6/wx_wxmemorydc.html:
    //"A bitmap must be selected into the new memory DC before it may be used
    //for anything."
    wxmemorydc.SelectObject(wxbitmap);

    //"Cross-Platform GUI Programming with wxWidgets"
    // (Copyright © 2006 Pearson Education, Inc.)
    // ISBN 0-13-147381-6  "First printing, July 2005"
    //"CHAPTER 5 Drawing and Printing" ->
    //"UNDERSTANDING DEVICE CONTEXTS" -> "Drawing on Windows with wxPaintDC" :
    // "Shifts the device origin so we don’t have to worry
    // about the current scroll position ourselves"
  //    PrepareDC(wxmemorydc);

    //http://docs.wxwidgets.org/stable/wx_wxmemorydc.html#wxmemorydc:
    //"Use the IsOk member to test whether the constructor was
    //successful in creating a usable device context."
    if( wxmemorydc.IsOk() )
    {
  //      wxColor col() ;
      FillWhiteIfMonochromeBitmap_Inline(wxmemorydc);
  //      wxmemorydc.SetTextBackground( * wxBLACK ) ;
  //      wxmemorydc.SetTextForeground( * wxWHITE ) ;
  //      wxmemorydc.SetTextBackground( * wxWHITE ) ;

      //wxWHITE_BRUSH is black for monochrome bitmaps?
      wxmemorydc.SetBrush( * wxWHITE_BRUSH) ;
      wxmemorydc.DrawText( //wxT("38")
        r_wxstr
  //        , 5,5) ;
        , 0,0) ;
      icon.CopyFromBitmap(wxbitmap) ;
    }
}

void CreateTextIcon( wxIcon & icon, const wxString & r_wxstr,
  const wxColour & r_wxcolor )
{
  //  BYTE byWidth = 32 , byHeight = 32 ;
  BYTE byWidth = 16 , byHeight = 16 ;
  wxBitmap wxbitmap(
    byWidth //int width
    , byHeight //int height
    //, 1//int depth = -1
    ) ;
  BYTE byNumBits = 16 * 2;
  char bits[ 16 * //16 / 8
    2 ] ;
  while( byNumBits --)
    bits[byNumBits] = //255;
     0;
  wxBitmap wxbitmapMask(
    bits, //const char bits[],
    16,//int width,
    16//int height,
    //int depth=1
    );
    //"Construct a mask from a mono bitmap (copies the bitmap)."
    wxMask wxmask(wxbitmapMask) ;
    wxbitmap.SetMask( & wxmask) ;
    wxMemoryDC wxmemorydc ;
    //http://docs.wxwidgets.org/2.6/wx_wxmemorydc.html:
    //"A bitmap must be selected into the new memory DC before it may be used
    //for anything."
    wxmemorydc.SelectObject(wxbitmap);

    //"Cross-Platform GUI Programming with wxWidgets"
    // (Copyright © 2006 Pearson Education, Inc.)
    // ISBN 0-13-147381-6  "First printing, July 2005"
    //"CHAPTER 5 Drawing and Printing" ->
    //"UNDERSTANDING DEVICE CONTEXTS" -> "Drawing on Windows with wxPaintDC" :
    // "Shifts the device origin so we don’t have to worry
    // about the current scroll position ourselves"
  //    PrepareDC(wxmemorydc);

    //http://docs.wxwidgets.org/stable/wx_wxmemorydc.html#wxmemorydc:
    //"Use the IsOk member to test whether the constructor was
    //successful in creating a usable device context."
    if( wxmemorydc.IsOk() )
    {
  //      wxColor col() ;
      FillWhiteIfMonochromeBitmap_Inline(wxmemorydc);
  //      wxmemorydc.SetTextBackground( * wxBLACK ) ;
        wxmemorydc.SetTextForeground( r_wxcolor ) ;
  //      wxmemorydc.SetTextBackground( * wxWHITE ) ;

      //wxWHITE_BRUSH is black for monochrome bitmaps?
//      wxmemorydc.SetBrush( * wxWHITE_BRUSH) ;
      wxmemorydc.DrawText( //wxT("38")
        r_wxstr
  //        , 5,5) ;
        , 0,0) ;
      icon.CopyFromBitmap(wxbitmap) ;
    }
}

void CreateWhiteTextIcon( wxIcon & icon, const wxString & r_wxstr )
{
  //Default size for Windows icons.
  BYTE byWidth = 16 , byHeight = 16 ;
  wxBitmap wxbitmap(
    byWidth //int width
    , byHeight //int height
    , 1//int depth = -1
    ) ;
  //  wxMask wxmask(wxbitmapMask) ;
  //  wxbitmap.SetMask( & wxmask) ;
  {
  //    wxDC wxDC
    wxMemoryDC wxmemorydc ;
    //http://docs.wxwidgets.org/2.6/wx_wxmemorydc.html:
    //"A bitmap must be selected into the new memory DC before it may be used
    //for anything."
    wxmemorydc.SelectObject(wxbitmap);

    //"Cross-Platform GUI Programming with wxWidgets"
    // (Copyright © 2006 Pearson Education, Inc.)
    // ISBN 0-13-147381-6  "First printing, July 2005"
    //"CHAPTER 5 Drawing and Printing" ->
    //"UNDERSTANDING DEVICE CONTEXTS" -> "Drawing on Windows with wxPaintDC" :
    // "Shifts the device origin so we don’t have to worry
    // about the current scroll position ourselves"
  //    PrepareDC(wxmemorydc);

    //http://docs.wxwidgets.org/stable/wx_wxmemorydc.html#wxmemorydc:
    //"Use the IsOk member to test whether the constructor was
    //successful in creating a usable device context."
    if( wxmemorydc.IsOk() )
    {
      FillWhiteIfNonMonochromeBitmap_Inline(wxmemorydc);
  //      wxmemorydc.SetTextBackground( * wxBLACK ) ;
      wxmemorydc.SetTextForeground( * wxWHITE ) ;
  //      wxmemorydc.SetTextBackground( * wxWHITE ) ;

//      wxmemorydc.SetTextForeground( * wxBLACK ) ;
      //wxWHITE_BRUSH is black for monochrome bitmaps?
      wxmemorydc.SetBrush( * wxBLACK_BRUSH) ;
      wxmemorydc.DrawText( //wxT("38")
        r_wxstr
  //        , 5,5) ;
        , 0,0) ;
    }
  }
  icon.CopyFromBitmap(wxbitmap) ;
}


void CreateNumberIcon( wxIcon & r_wxicon, BYTE byNumber)
{
  CreateTextIcon(r_wxicon, wxString::Format( wxT("%u"), byNumber ) ) ;
}
