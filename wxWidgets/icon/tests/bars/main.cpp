#include <iostream>///std::cout
#include <wxWidgets/icon/IconDrawer.hpp>///class wxIconDrawer

void saveFile(const wxBitmap & wxbmp)
{
//#ifdef _DEBUG
  const bool succSaved =
    ///https://docs.wxwidgets.org/stable/classwx_bitmap.html#a48617712dd0f5a6a51bb1897a49ae273:
	///"true if the operation succeeded, false otherwise."	
	wxbmp./*ConvertToImage().*/SaveFile(
	  wxT("barTest.bmp")///const wxString& name
	  ///wxBitmapType type
	  , //wxBITMAP_TYPE_XPM///did work on Windows
	  wxBITMAP_TYPE_BMP
	  );
  //https://forums.wxwidgets.org/viewtopic.php?t=42547
  if(succSaved)
    std::cout << "saving file succeeded" << std::endl;
  else
    std::cerr << "saving file failed" << std::endl;  
//#endif
}

void generateIcon(wxIconDrawer & wxiconDrawer)
{	
  const int numBars = 3;
  float heightsInPercent[numBars] = {0.5f,0.0f,1.0f};
  //wxImage::AddHandler(wxJPEGHandler);///Must add handler?
  //wxInitAllImageHandlers();
  wxIcon wxicon;
  wxiconDrawer.DrawColouredBarsIcon(wxicon, heightsInPercent, numBars);
}

///Adapted from https://forums.wxwidgets.org/viewtopic.php?t=21065, 
/// by "rupinder", Thu Sep 25, 2008 1:58 am
#include <wx/wx.h>///includes many wxWidgets header files

///Without a wxApp object saving the wxBitmap to a file failed with:
/// "Warning: No image handler for type 1 defined."
class MyApp:public wxApp
{
 public:
  virtual bool OnInit();
};

class MyFrame: public wxFrame
{
 public:
  MyFrame();
};

MyFrame::MyFrame():wxFrame(NULL,wxID_ANY,"")
{
  wxIconDrawer wxiconDrawer;
  generateIcon(wxiconDrawer);
  saveFile(*wxiconDrawer.m_p_wxbitmapToDrawOn);
}

bool MyApp::OnInit()
{
  MyFrame * p_wxframe = new MyFrame();
  p_wxframe->Show(true);
  return true;
}

DECLARE_APP(MyApp)
IMPLEMENT_APP(MyApp)

//int main()
//{
  //wxIconDrawer wxIconDrawer;
  //return -1;
//}
