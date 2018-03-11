#include "FileChooserDialog.hpp"
#include "../UIcontrols/FileChooser.hpp"
#include "../UIcontrols/Button.hpp"
#include "../UIcontrols/Label.hpp"
#include "../UIcontrols/TextBox.hpp"
#include "libraries/curses/LayoutManager/BorderLayout.hpp"
#include "ncurses/MainWindow.hpp"
#include <OperatingSystem/multithread/nativeThreadType.hpp>
#include <FileSystem/GetDirContents.hpp>
#include <FileSystem/path_seperator.h>// PATH_SEPERATOR_CHAR
#include <FileSystem/isDirectory.hpp>

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
  m_dirToGetContentsFrom = GetDirToGetContentsFrom(initialFileOrDir);
  std::vector<std::string> dirEntries;
  unsigned result = FileSystem::GetDirContents(m_dirToGetContentsFrom.c_str(), 
    dirEntries);
  
//  const char * pchDirEntries[dirEntries.size() + 1];
//  pchDirEntries[dirEntries.size()] = NULL;
//  std::vector<std::string>::const_iterator citer = dirEntries.begin();
//  for( unsigned arrayIndex = 0; 
//    citer != dirEntries.end(); arrayIndex++, citer++)
//  {
//    pchDirEntries[arrayIndex] = citer->c_str();
//  }
  
  m_p_listBox = new curses::ListBox(m_backGroundColorPair, m_currentSelectionColorPair);
  m_p_listBox->create();
  m_p_listBox->SetContent(dirEntries);
//  create();
  curses::Button * p_button = new curses::Button();
  if( mode == FileChooserDialog::save)
  {
    p_button->SetLabel("save");
    p_button->SetColor(m_currentSelectionColorPair);
  }
  if( mode == FileChooserDialog::open)
  {
    p_button->SetLabel("open");
  }
  curses::BorderLayout * p_buttonAndTextFieldPanel = new curses::BorderLayout();
  p_buttonAndTextFieldPanel->create();
  curses::Label * p_label = new curses::Label();
  p_label->SetLabel("file name:");
  p_label->create();
  p_buttonAndTextFieldPanel->add(p_label, curses::BorderLayout::left);
  p_buttonAndTextFieldPanel->add(p_button, curses::BorderLayout::right);
  
//  ncurses::TextBox * p_textField = new ncurses::TextBox(BODY_WINDOW_COLOR);
  ncurses::TextBox * p_textBox = new ncurses::TextBox(m_backGroundColorPair);
  p_textBox->SetEditable(true);
  p_textBox->SetDrawBorder(false);
  
  p_textBox->create(p_buttonAndTextFieldPanel->getWindowHandle(), 10, 10, 0, 0);
  p_buttonAndTextFieldPanel->add(p_textBox, curses::BorderLayout::center);
  
  curses::BorderLayout * p_borderLayout = new curses::BorderLayout();
  m_p_folderLabel = new curses::Label();
  m_p_folderLabel->create();
  m_p_folderLabel->SetLabel(m_dirToGetContentsFrom.c_str());
  p_borderLayout->add(m_p_folderLabel, curses::BorderLayout::top);
  p_borderLayout->add(m_p_listBox, curses::BorderLayout::center);
  p_borderLayout->add(p_buttonAndTextFieldPanel
//    p_button
    , curses::BorderLayout::bottom);
  p_button->create();
  setLayout(p_borderLayout);

//  return ::ChooseFile(initialDir, pWindowToShowFileChooserIn, 
//    m_backGroundColorPair, m_currentSelectionColorPair);
  doLayout();
  m_p_listBox->show();
  m_p_listBox->SetFocus(true);
  m_p_folderLabel->show();
  p_button->show();
  p_label->show();
  p_textBox->show();
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
        if(m_p_listBox->HandleAction(ch) == 0xA)
        {
          std::string selectedListBoxItem = m_p_listBox->GetCurrentSelectionString();
          std::string testDir;
          if( selectedListBoxItem == "..")
          {
            int lastPathSeperatorCharIndex = m_dirToGetContentsFrom.
              find_last_of(PATH_SEPERATOR_CHAR);
            if( lastPathSeperatorCharIndex != std::string::npos )
            {
              testDir = m_dirToGetContentsFrom.substr(0, lastPathSeperatorCharIndex);
            }
          }
          else if(selectedListBoxItem == ".")
            testDir = m_dirToGetContentsFrom;
          else
          {
            testDir = m_dirToGetContentsFrom + PATH_SEPERATOR_CHAR; 
            testDir += selectedListBoxItem;
          }
          if(FileSystem::IsDirectory(testDir.c_str() ) )
          {
            m_dirToGetContentsFrom = testDir;
            m_p_folderLabel->SetLabel(m_dirToGetContentsFrom.c_str());
            m_p_folderLabel->show();
            std::vector<std::string> dirEntries;
            unsigned result = FileSystem::GetDirContents(m_dirToGetContentsFrom.c_str(), 
              dirEntries);
            m_p_listBox->SetContent(dirEntries);
            m_p_listBox->SetCurrentSelection(0);
            m_p_listBox->show();
          }
        }
    }
  }
}

}

