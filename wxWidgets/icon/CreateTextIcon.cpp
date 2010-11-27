/*
 * CreateTextIcon.cpp
 *
 *  Created on: Nov 22, 2010
 *      Author: Stefan
 */
#include <wx/bitmap.h> //for class wxBitmap
#include <wx/dcmemory.h> //for class wxMemoryDC
#include <wx/icon.h> //class wxIcon

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
  //  BYTE ar_by [byW*byW] ;
  //  wxBitmap wxbitmapMask(
  ////    ar_by ,
  ////    wxBITMAP_TYPE_BMP ,
  //    byW //int width
  //    , byH //int height
  //    , 1 //int depth = -1
  //    ) ;
  //  wxbitmapMask.S
  //  wxMask wxmask(wxbitmapMask) ;
  //  wxbitmap.SetMask( & wxmask) ;
  //  BYTE * ar_by = CreateNumberAsPixelArray(35.5,32,32) ;
  //  if( ar_by )
  {
  //    wxDC wxDC
    wxMemoryDC wxmemorydc ;
    //http://docs.wxwidgets.org/2.6/wx_wxmemorydc.html:
    //"A bitmap must be selected into the new memory DC before it may be used
    //for anything."
    wxmemorydc.SelectObject(wxbitmap);

    //http://www.informit.com/articles/article.aspx?p=405047:
    // Shifts the device origin so we don't have to worry
    // about the current scroll position ourselves
  //    PrepareDC(wxmemorydc);

    //http://docs.wxwidgets.org/stable/wx_wxmemorydc.html#wxmemorydc:
    //"Use the IsOk member to test whether the constructor was
    //successful in creating a usable device context."
    if( wxmemorydc.IsOk() )
    {
//      std::cout
//        << "width:" << wxbitmap.GetWidth()
//        << "height:" << wxbitmap.GetHeight()
//        << "depth:" << wxbitmap.GetDepth()
//        << "\n"
//        ;
  //      wxColor col() ;
  //      wxPen pen(wxBLUE, 3); // pen of width 3
      wxmemorydc.SetPen(//pen
          //*wxBLACK_PEN
          //Must explicitely select a white pen to draw:
        //http://docs.wxwidgets.org/2.6/wx_wxmemorydc.html#wxmemorydc:
        //"When drawing in to a mono-bitmap, using wxWHITE, wxWHITE_PEN  and
        //wxWHITE_BRUSH will draw the background colour (i.e. 0) whereas all
        //other colours will draw the foreground colour (i.e. 1).
        * wxWHITE_PEN );
  //        * wxBLACK_PEN );
      //Fill white (initially it is black).
      wxmemorydc.FloodFill( 0,0, //* wxWHITE
        * wxBLACK
        //"    * wxFLOOD_SURFACE: The flooding occurs until a colour other
        // than the given colour is encountered.
        // * wxFLOOD_BORDER: The area to be flooded is bounded by the given
        // colour."
        ) ;
  //      wxmemorydc.SetTextBackground( * wxBLACK ) ;
  //      wxmemorydc.SetTextForeground( * wxWHITE ) ;
  //      wxmemorydc.SetTextBackground( * wxWHITE ) ;
      wxmemorydc.SetTextForeground( * wxBLACK ) ;
      wxmemorydc.SetBrush( * wxWHITE_BRUSH) ;
      wxmemorydc.DrawText( //wxT("38")
        r_wxstr
  //        , 5,5) ;
        , 0,0) ;
  //      wxmemorydc.DrawLine(0,0, byWidth-1, 0) ;
  //      wxmemorydc.DrawLine(0,0,0,byHeight-1) ;
  //      wxmemorydc.DrawLine(byWidth-1, 0, byWidth-1, byHeight-1) ;
  //      wxmemorydc.DrawLine(0, byHeight-1, byWidth-1, byHeight-1) ;
  //      wxmemorydc.F
//      OutputMemoryDCsValues(wxmemorydc) ;
    }
  }
//  OutputImageData(wxbitmap,byWidth,byHeight) ;
  //  wxIcon icon(archANDmaskIcon,byWidth,byHeight) ;
  icon.CopyFromBitmap(wxbitmap) ;
}

void CreateNumberIcon( wxIcon & r_wxicon, BYTE byNumber)
{
  CreateTextIcon(r_wxicon, wxString::Format( wxT("%u"), byNumber ) ) ;
}
