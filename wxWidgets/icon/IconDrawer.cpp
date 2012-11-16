/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */
/*
 * IconDrawer.cpp
 *
 *  Created on: Jan 14, 2011
 *      Author: Stefan
 */

#include <wxWidgets/icon/IconDrawer.hpp>
#ifdef _WIN32 //pre-defined macro under Windows, also 64t
  #include <wx/msw/winundef.h> //to not replace DrawText with DrawTextW
#endif

namespace wxWidgets
{

  IconDrawer::IconDrawer()
  {
    // TODO Auto-generated constructor stub

  }

  IconDrawer::~IconDrawer()
  {
    // TODO Auto-generated destructor stub
  }

}

void wxIconDrawer::DrawColouredBarsIcon(
  wxIcon & r_wxicon,
//  const wxColour ar_wxcolour [],
  const float heightsInPercent[],
  BYTE numberOfBars
  )
{
  LOGN( FULL_FUNC_NAME << "--numberOfBars: " << (WORD) numberOfBars)
  //    wxMemoryDC m_wxmemorydc ;
    //http://docs.wxwidgets.org/2.6/wx_wxmemorydc.html:
    //"A bitmap must be selected into the new memory DC before it may be used
    //for anything."
  //    m_wxmemorydc.SelectObject(m_wxbitmap);

  //http://docs.wxwidgets.org/stable/wx_wxmemorydc.html#wxmemorydc:
  //"Use the IsOk member to test whether the constructor was
  //successful in creating a usable device context."
  if( m_p_wxbitmapToDrawOn && m_wxmemorydc.IsOk() )
  {
//    FillWhiteIfNonMonochromeBitmap_Inline(m_wxmemorydc);
    m_wxmemorydc.Clear();
//      Fill_Inline(m_wxmemorydc, //wxWHITE
//        //wxBLACK
//        p_wxcolourBackground
//        );

    int colouredBarWidth = m_wxbitmap.GetWidth() / numberOfBars;
    int colouredBarHeight;
    const int iconHeight = m_wxbitmap.GetHeight();
    wxRect rectColouredBar(0, 0, colouredBarWidth, iconHeight );
//    wxBrush brush;
    wxBrush wxbrush = * wxBLACK_BRUSH;
//    wxbrush.SetStyle(//wxSOLID
//      wxTRANSPARENT);
    for( BYTE barIndex = 0; barIndex < numberOfBars; ++ barIndex )
    {
      colouredBarHeight =
        //Cast to avoid g++ warning "converting to `int' from `float'"
        (int)
        ( heightsInPercent[barIndex] * iconHeight);
      rectColouredBar.height = colouredBarHeight;
      //Start from bottom pixel.
      rectColouredBar.y = iconHeight - colouredBarHeight;
      rectColouredBar.x = barIndex * colouredBarWidth;

//      brush.SetColour( ar_wxcolour[barIndex] );
//    //wxWHITE_BRUSH is black for monochrome bitmaps?
//      m_wxmemorydc.SetBrush( //* wxRED_BRUSH
////        brush
//        wxbrush
//        );
      //Alternate brush colours.
      if( wxbrush //== wxBLACK_BRUSH
          .GetColour() == * wxBLACK )
      {
//        c_p_wxbrush = wxGREY_BRUSH;
//        wxbrush.SetColour( * wxLIGHT_GREY);
        m_wxmemorydc.SetPen( * wxBLACK_PEN);
        m_wxmemorydc.SetBrush( * wxBLACK_BRUSH);
      }
      else
      {
        //c_p_wxbrush = wxBLACK_BRUSH;
//        wxbrush.SetColour( * wxBLACK);
        m_wxmemorydc.SetBrush( * wxGREY_BRUSH);
        m_wxmemorydc.SetPen( //* wxLIGHT_GREY_PEN
          * wxGREY_PEN);
      }
      //http://docs.wxwidgets.org/2.8/wx_wxdc.html#wxdcdrawrectangle:
      //"The current pen is used for the outline and the current brush for
      //filling the shape."
      m_wxmemorydc.DrawRectangle( //wxT("38")
        rectColouredBar);
    }
    r_wxicon.CopyFromBitmap(//m_wxbitmap
      * m_p_wxbitmapToDrawOn) ;
  }
}

void wxIconDrawer::DrawText(
  wxIcon & r_wxicon,
  const wxString & cr_wxstrText,
  const wxColour * p_wxcolourText,
  const wxColour * p_wxcolourBackground /* = wxWHITE */
//    const wxBrush & brush
  )
{
//    wxMemoryDC m_wxmemorydc ;
  //http://docs.wxwidgets.org/2.6/wx_wxmemorydc.html:
  //"A bitmap must be selected into the new memory DC before it may be used
  //for anything."
//    m_wxmemorydc.SelectObject(m_wxbitmap);

  //http://docs.wxwidgets.org/stable/wx_wxmemorydc.html#wxmemorydc:
  //"Use the IsOk member to test whether the constructor was
  //successful in creating a usable device context."
  if( m_p_wxbitmapToDrawOn && m_wxmemorydc.IsOk() )
  {
//    FillWhiteIfNonMonochromeBitmap_Inline(m_wxmemorydc);
    m_wxmemorydc.Clear();
//      Fill_Inline(m_wxmemorydc, //wxWHITE
//        //wxBLACK
//        p_wxcolourBackground
//        );
//      wxmemorydc.SetTextBackground( * wxBLACK ) ;
    m_wxmemorydc.SetTextForeground( //* wxWHITE
      * p_wxcolourText) ;
//      wxmemorydc.SetTextBackground( * wxWHITE ) ;

//    m_wxmemorydc.SetTextForeground( //* wxBLACK
//      * wxRED ) ;

//    //wxWHITE_BRUSH is black for monochrome bitmaps?
//    m_wxmemorydc.SetBrush( //* wxRED_BRUSH
////      * wxBLACK_BRUSH
////      * wxWHITE_BRUSH
//      //* p_wxcolour
//      brush
//      ) ;
  m_wxmemorydc.DrawText( //wxT("38")
    cr_wxstrText
//        , 5,5) ;
    , 0,0) ;
  r_wxicon.CopyFromBitmap(//m_wxbitmap
    * m_p_wxbitmapToDrawOn) ;
  }
}

void wxIconDrawer::ReleaseRessources()
{
  LOGN("wxIconDrawer::ReleaseRessources begin--m_p_wxbitmapMask:"
    << m_p_wxbitmapMask)
  if( m_p_wxbitmapMask )
  {
    LOGN("wxIconDrawer::ReleaseRessources freeing resources for the mask "
      "bitmap")
//      m_p_wxbitmapMask->FreeResource();
    delete m_p_wxbitmapMask;
    //http://docs.wxwidgets.org/2.8/wx_wxbitmap.html#wxbitmapdtor:
    //"Do not delete a bitmap that is selected into a memory device context."
//      delete m_p_wxbitmapToDrawOn;

    //Is allocated when m_p_wxbitmapMask is <> NULL.
    delete [] m_ar_chBits;
    //Prevent another deletion of the memory at this address
    m_p_wxbitmapMask = NULL;

//      m_wxmemorydc.UnRef();
//      m_wxbitmap.FreeResource();
//      m_wxmask.FreeResource();
//      m_wxbitmapMask.FreeResource();

    //else wxBitmapRefData::Free():
    // " wxT("deleting bitmap still selected into wxMemoryDC") );"
//      m_wxmemorydc.UnRef();
  }
  LOGN("wxIconDrawer::ReleaseRessources end")
}
