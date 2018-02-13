#include "FileChooserDialog.hpp"
#include "../UIcontrols/FileChooser.hpp"
#include "libraries/curses/LayoutManager/BorderLayout.hpp"
#include "../UIcontrols/ListBox.hpp"
#include <OperatingSystem/multithread/nativeThreadType.hpp>

namespace curses {
  
using namespace curses;

DWORD waitForDialogEnd(void * p_v)
{
  curses::FileChooserDialog * p_fileChooserDialog = (curses::FileChooserDialog *) p_v;
  if(p_fileChooserDialog)
  {
//    p_fileChooserDialog->m_closeEvent.Wait();
  }
}

std::string FileChooserDialog::ChooseFile(
  const char * const initialDir, 
  WINDOW * pWindowToShowFileChooserIn,
  enum FileChooserDialog::mode mode)
{
//  create();
  if( mode == FileChooserDialog::save)
  {
    curses::BorderLayout * p_borderLayout = new curses::BorderLayout();
    curses::ListBox * p_listBox = new curses::ListBox();
    p_borderLayout->add(p_listBox, curses::BorderLayout::center);
    setLayout(p_borderLayout);
  }
//  return ::ChooseFile(initialDir, pWindowToShowFileChooserIn, 
//    m_backGroundColorPair, m_currentSelectionColorPair);
  doLayout();
  SetAsKeyListener();
  Curses::EventLoop();
//  nativeThread_type thread;
//  thread.start(waitForDialogEnd, this);
  //TODO create new thread and wait for end?!
  return "";
}

int FileChooserDialog::HandleAction(const int ch)
{
  int ret = curses::TopLevelWindow::HandleAction(ch);
  if( ret == Curses::Window::inputNotHandled )
  {
    switch(ch)
    {
      case 27 :
//        m_closeEvent.Broadcast();
        break;
    }
  }
}

}

