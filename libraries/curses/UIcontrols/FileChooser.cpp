/** Should should with ncurses, PDcurses */
#include <libraries/curses/listbox.h>

#include <FileSystem/GetCurrentWorkingDir.hpp>
#include <FileSystem/GetDirContents.hpp>
#include <FileSystem/isDirectory.hpp>
#include <limits.h> //UINT_MAX
#include <string.h> //class std::string
#include <vector> //strcmp(...)
#include <curses.h> //WINDOW
#include <FileSystem/path_seperator.h>

std::string ChooseFile(const char * const initialDir, WINDOW * pBodyWindow)
{
  //TODO show all files from from /proc/fs/ntfs ?

//#ifdef __linux__
  unsigned numFilesOrDirs;
//  char * dir = "//";
//  std::string std_strCurrentWorkingDir;
  std::string dirToGetContentsFrom /*= "/" */;
  std::string selectedFile;
  OperatingSystem::GetCurrentWorkingDirA_inl(dirToGetContentsFrom);
  const char pathSeperator = PATH_SEPERATOR_CHAR;
//  dirToGetContentsFrom += pathSeperator;
  unsigned selectedIndex;
  do
  {
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
    selectedIndex = ::listBox(pchDirEntries, dirToGetContentsFrom.c_str(), pBodyWindow );
    if( selectedIndex != UINT_MAX )
    {
      if( strcmp(pchDirEntries[selectedIndex], "..") == 0 )
      {
        const unsigned indexOfPathSeperatorChar = dirToGetContentsFrom.rfind(pathSeperator,
          dirToGetContentsFrom.size() - 2);
        if( indexOfPathSeperatorChar != std::string::npos )
          if( indexOfPathSeperatorChar == 0)
            dirToGetContentsFrom = pathSeperator;
          else
            dirToGetContentsFrom = dirToGetContentsFrom.substr(0, indexOfPathSeperatorChar);
      }
      else if( /** Prevent <PATH = PATH + ".">  */
          strcmp(pchDirEntries[selectedIndex], ".") != 0 )
      {
        selectedFile = dirToGetContentsFrom + pathSeperator;
        selectedFile += pchDirEntries[selectedIndex];
        if( FileSystem::IsDirectory(selectedFile.c_str() ) )
          //dirToGetContentsFrom += pathSeperator;
          ;
        else
          selectedIndex = UINT_MAX;
      }
    }
  }while(selectedIndex != UINT_MAX);
//#endif
  return selectedFile;
}
