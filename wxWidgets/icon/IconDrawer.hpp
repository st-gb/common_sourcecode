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
#include <wx/msw/winundef.h> //to not replace DrawText with DrawTextW

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
  void ReleaseRessources()
  {
    LOGN("wxIconDrawer::ReleaseRessources begin--m_p_wxbitmapMask:"
      << m_p_wxbitmapMask)
    if( m_p_wxbitmapMask )
    {
      m_p_wxbitmapMask->FreeResource();
      delete m_p_wxbitmapMask;
      delete m_p_wxbitmapToDrawOn;
      //Is allocated when m_p_wxbitmapMask is <> NULL.
      delete [] m_ar_chBits;
      //Prevent another deletion of the memory at this address
      m_p_wxbitmapMask = NULL;
      m_wxmemorydc.UnRef();
//      m_wxbitmap.FreeResource();
//      m_wxmask.FreeResource();
//      m_wxbitmapMask.FreeResource();

      //else wxBitmapRefData::Free():
      // " wxT("deleting bitmap still selected into wxMemoryDC") );"
//      m_wxmemorydc.UnRef();
    }
    LOGN("wxIconDrawer::ReleaseRessources end")
  }
  ~wxIconDrawer()
  {
    LOGN("~wxIconDrawer begin")
    ReleaseRessources();
    LOGN("~wxIconDrawer end")
  }
  wxIconDrawer(WORD wWidth = 16, WORD wHeight = 16, int nColorDepth = //1
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
           //0 means: can be drawn onto.
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
          //http://www.informit.com/articles/article.aspx?p=405047:
          // Shifts the device origin so we don't have to worry
          // about the current scroll position ourselves
        //    PrepareDC(wxmemorydc);
          m_bOk = true;
        }
      }
    }
  }
  bool Create(
    int   width,
    int   height,
    int   depth = //wxBITMAP_SCREEN_DEPTH
      -1
    )
  {
    return m_wxbitmap.Create(width,height,depth);
  }
  void DrawText(
    wxIcon & r_wxicon,
    const wxString & cr_wxstrText,
    const wxColour * p_wxcolourText,
    const wxColour * p_wxcolourBackground = wxWHITE
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
    if( m_p_wxbitmapToDrawOn &&m_wxmemorydc.IsOk() )
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
