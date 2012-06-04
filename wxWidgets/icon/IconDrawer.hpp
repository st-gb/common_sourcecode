/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */
/*
 * IconDrawer.hpp
 *
 *  Created on: Jan 14, 2011
 *      Author: Stefan
 */

#ifndef ICONDRAWER_HPP_
#define ICONDRAWER_HPP_

#include <wx/bitmap.h> //for class wxBitmap
#include <wx/dcmemory.h> //for class wxMemoryDC
#include <wx/icon.h> //class wxIcon
#include <windef.h> //WORD
#include <preprocessor_macros/logging_preprocessor_macros.h> //LOGN(...)
#ifdef _WIN32 //pre-defined macro under Windows, also 64t
	#include <wx/msw/winundef.h> //to not replace DrawText with DrawTextW
#endif

inline void FillWhiteIfNonMonochromeBitmap_Inline(wxMemoryDC & r_wxmemorydc)
{
  //Fill white (initially it is black).
  r_wxmemorydc.FloodFill( 0,0, //* wxWHITE
    * wxWHITE
    //"    * wxFLOOD_SURFACE: The flooding occurs until a colour other
    // than the given colour is encountered.
    // * wxFLOOD_BORDER: The area to be flooded is bounded by the given
    // colour."
    ) ;
}

inline void FillWhiteIfMonochromeBitmap_Inline(wxMemoryDC & r_wxmemorydc)
{
  //Fill white (initially it is black).
  r_wxmemorydc.FloodFill( 0,0, //* wxWHITE
    * wxBLACK
    //"    * wxFLOOD_SURFACE: The flooding occurs until a colour other
    // than the given colour is encountered.
    // * wxFLOOD_BORDER: The area to be flooded is bounded by the given
    // colour."
    ) ;
}

inline void Fill_Inline(wxMemoryDC & r_wxmemorydc, const wxColour * p_wxcolour)
{
  //Fill white (initially it is black).
  r_wxmemorydc.FloodFill( 0,0, //* wxWHITE
    * p_wxcolour
    //"    * wxFLOOD_SURFACE: The flooding occurs until a colour other
    // than the given colour is encountered.
    // * wxFLOOD_BORDER: The area to be flooded is bounded by the given
    // colour."
    ) ;
}

class wxIconDrawer
{
public:
  bool m_bOk;
private:
  char * m_ar_chBits;
  wxBitmap m_wxbitmap;
  //Must be created on the heap because it must be destroyed prior to the
  //memoryDC?! Else the exe crashed at/ after wxIconDrawer's destructor.
  wxBitmap * m_p_wxbitmapToDrawOn;
//  wxBitmap m_wxbitmapMask;
  wxBitmap * m_p_wxbitmapMask;
  wxMemoryDC m_wxmemorydc ;
  wxMask m_wxmask;

public:

  wxIconDrawer(
    WORD wWidth = 16,
    WORD wHeight = 16,
    int nColorDepth = //1
    //wxBITMAP_SCREEN_DEPTH
    //http://docs.wxwidgets.org/trunk/interface_2wx_2bitmap_8h.html#92f17e2abdf285ce14f0ef47997fdb06 :
    //"n wxBitmap and wxBitmapHandler context this value means: "use the screen depth".
    -1
    )
    :
    m_bOk(false),
    m_wxbitmap(
      wWidth //int width
      , wHeight //int height
      , //1//int depth = -1
      nColorDepth
      )//,
//    m_wxbitmapMask(
//      wWidth //int width
//      , wHeight //int height
//      , 1//int depth = -1
//      //nColorDepth
//      )
    , m_p_wxbitmapMask(NULL)
    //m_wxmask(m_wxbitmap)
  {
    m_p_wxbitmapToDrawOn = new wxBitmap(
      wWidth //int width
      , wHeight //int height
      , //1//int depth = -1
      nColorDepth
      );
    //http://docs.wxwidgets.org/stable/wx_wxmemorydc.html#wxmemorydc:
    //"Use the IsOk member to test whether the constructor was
    //successful in creating a usable device context."
    if( m_p_wxbitmapToDrawOn && m_wxmemorydc.IsOk() )
    {
      WORD wNumberOfBits = wWidth * wHeight / 8;
      m_ar_chBits = new char[wNumberOfBits];
      if( m_ar_chBits)
      {
        while( wNumberOfBits --)
          m_ar_chBits[wNumberOfBits] = //255;
           //"0" means: can be drawn onto.
           0;
        m_p_wxbitmapMask = new wxBitmap(m_ar_chBits,wWidth,wHeight);
        LOGN("wxIconDrawer()--m_p_wxbitmapMask:" << m_p_wxbitmapMask)
        if( m_p_wxbitmapMask)
        {
//          m_wxbitmapMask.Create(m_ar_chBits,)
          m_wxmask.Create(* m_p_wxbitmapMask);
//          m_wxbitmap.SetMask(& m_wxmask);
          m_p_wxbitmapToDrawOn->SetMask(& m_wxmask);
          //http://docs.wxwidgets.org/trunk/classwx_icon.html#ea0254e1fcd09977999799b5744a016c:
          //Under MS Windows the bitmap must have mask colour set.:
      //    m_wxbitmap.SetMask( )

      //    BYTE byWidth = 16 , byHeight = 16 ;
          //http://docs.wxwidgets.org/2.6/wx_wxmemorydc.html:
          //"A bitmap must be selected into the new memory DC before it may be used
          //for anything."
          m_wxmemorydc.SelectObject(//m_wxbitmap
            * m_p_wxbitmapToDrawOn);
          //"Cross-Platform GUI Programming with wxWidgets"
          // (Copyright © 2006 Pearson Education, Inc.)
          // ISBN 0-13-147381-6  "First printing, July 2005"
          //"CHAPTER 5 Drawing and Printing" ->
          //"UNDERSTANDING DEVICE CONTEXTS" -> "Drawing on Windows with wxPaintDC" :
          // "Shifts the device origin so we don’t have to worry
          // about the current scroll position ourselves"
        //    PrepareDC(wxmemorydc);
          m_bOk = true;
        }
      }
    }
  }

  ~wxIconDrawer()
  {
    LOGN("~wxIconDrawer (address:" << this << ") begin")
    ReleaseRessources();
    LOGN("~wxIconDrawer end")
  }

  bool Create(
    int width,
    int height,
    int depth = //wxBITMAP_SCREEN_DEPTH
      -1
    )
  {
    return m_wxbitmap.Create(width,height,depth);
  }

  //inline
    void DrawColouredBarsIcon(
    wxIcon & r_wxicon,
//    const wxColour ar_wxcolour [],
    const float heightsInPercent[],
    BYTE numberOfBars
    );
  //inline
    void DrawText(
    wxIcon & r_wxicon,
    const wxString & cr_wxstrText,
    const wxColour * p_wxcolourText,
    const wxColour * p_wxcolourBackground = wxWHITE
  //    const wxBrush & brush
    );
  //inline
    void ReleaseRessources();
};

namespace wxWidgets
{

  class IconDrawer
  {
  public:
    IconDrawer();
    virtual
    ~IconDrawer();
  };

}

#endif /* ICONDRAWER_HPP_ */
