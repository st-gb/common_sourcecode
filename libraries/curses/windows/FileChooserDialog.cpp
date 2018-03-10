#include "FileChooserDialog.hpp"
#include "../UIcontrols/FileChooser.hpp"
#include "../UIcontrols/Button.hpp"
#include "../UIcontrols/TextBox.hpp"
#include "libraries/curses/LayoutManager/BorderLayout.hpp"
#include "ncurses/MainWindow.hpp"
#include <OperatingSystem/multithread/nativeThreadType.hpp>
#include <FileSystem/GetDirContents.hpp>

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
  const char * const initialFileOrDir, 
  WINDOW * pWindowToShowFileChooserIn,
  enum FileChooserDialog::mode mode)
{
  std::string dirToGetContentsFrom = GetDirToGetContentsFrom(initialFileOrDir);
  std::vector<std::string> dirEntries;
  unsigned result = FileSystem::GetDirContents(dirToGetContentsFrom.c_str(), 
    dirEntries);
  const char * pchDirEntries[dirEntries.size() + 1];
  pchDirEntries[dirEntries.size()] = NULL;
  std::vector<std::string>::const_iterator citer = dirEntries.begin();
  for( unsigned arrayIndex = 0; 
    citer != dirEntries.end(); arrayIndex++, citer++)
  {
    pchDirEntries[arrayIndex] = citer->c_str();
  }
  m_p_listBox = new curses::ListBox(m_backGroundColorPair, m_currentSelectionColorPair);
  m_p_listBox->create(pchDirEntries, dirEntries.size());
//  create();
  curses::Button * p_button;
  if( mode == FileChooserDialog::save)
  {
    
//    curses::BorderLayout * p_buttonAndTextFieldPanel = new curses::BorderLayout();
    p_button = new curses::Button("save");
//    p_buttonAndTextFieldPanel->add(p_button, curses::BorderLayout::left);
//    ncurses::TextBox * p_textField = new ncurses::TextBox(BODY_WINDOW_COLOR);
//    p_textField->create(p_buttonAndTextFieldPanel->getWindowHandle())
//    p_buttonAndTextFieldPanel->add(p_textField, curses::BorderLayout::center);
  }
  if( mode == FileChooserDialog::open)
  {
    curses::Button * p_button = new curses::Button("open");    
  }
  curses::BorderLayout * p_borderLayout = new curses::BorderLayout();
  p_borderLayout->add(m_p_listBox, curses::BorderLayout::center);
  p_borderLayout->add(/*p_buttonAndTextFieldPanel*/p_button, 
    curses::BorderLayout::bottom);
  p_button->create();
  setLayout(p_borderLayout);

//  return ::ChooseFile(initialDir, pWindowToShowFileChooserIn, 
//    m_backGroundColorPair, m_currentSelectionColorPair);
  doLayout();
  m_p_listBox->show();
  p_button->show();
  SetAsKeyListener();
//  Curses::EventLoop();
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
      default:
        m_p_listBox->HandleAction(ch);
    }
  }
}

}

