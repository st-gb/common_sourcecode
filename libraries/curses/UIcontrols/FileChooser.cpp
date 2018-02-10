/** Should should with ncurses, PDcurses */
#include <libraries/curses/listbox.h>

#include <FileSystem/GetCurrentWorkingDir.hpp>
#include <FileSystem/GetDirContents.hpp>
#include <FileSystem/isDirectory.hpp>
#include <FileSystem/isRegularFile.hpp>
#include <limits.h> //UINT_MAX
#include <string.h> //class std::string
#include <vector> //strcmp(...)
#include <curses.h> //WINDOW
#include <FileSystem/path_seperator.h>

//void HandleSelection()
//{
//}

std::string ChooseFile(const char * const initialFileOrDir, WINDOW * pBodyWindow)
{
  //TODO show all files from from /proc/fs/ntfs ?

//#ifdef __linux__
//  unsigned numFilesOrDirs;
//  char * dir = "//";
//  std::string std_strCurrentWorkingDir;
  std::string dirToGetContentsFrom;
  const char pathSeperator = PATH_SEPERATOR_CHAR;
  if( FileSystem::IsDirectory(initialFileOrDir ) )
    dirToGetContentsFrom = initialFileOrDir;
  else if(FileSystem::IsRegularFile(initialFileOrDir) )
  {
//    std::string std_str
    const char * p_posOfPathSeperatorChar = strrchr(initialFileOrDir, PATH_SEPERATOR_CHAR);
    if(p_posOfPathSeperatorChar != NULL)
    {
      int numChars = p_posOfPathSeperatorChar - initialFileOrDir;
      dirToGetContentsFrom = std::string(initialFileOrDir, numChars);
    }
  }
  if( dirToGetContentsFrom == "")
    OperatingSystem::GetCurrentWorkingDirA_inl(dirToGetContentsFrom);
  std::string selectedFileOrDir;
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
        const unsigned indexOfPathSeperatorChar = dirToGetContentsFrom.rfind(
          pathSeperator,dirToGetContentsFrom.size() - 2);
        if( indexOfPathSeperatorChar != std::string::npos )
          if( indexOfPathSeperatorChar == 0)
            dirToGetContentsFrom = pathSeperator;
          else
            dirToGetContentsFrom = dirToGetContentsFrom.substr(0, indexOfPathSeperatorChar);
      }
      else if( /** Prevent <PATH = PATH + ".">  */
          strcmp(pchDirEntries[selectedIndex], ".") != 0 )
      {
        selectedFileOrDir = dirToGetContentsFrom + pathSeperator;
        selectedFileOrDir += pchDirEntries[selectedIndex];
        if( FileSystem::IsDirectory(selectedFileOrDir.c_str() ) )
          /** Go 1 level down (=loger path) in the file system hierarchy. */
          dirToGetContentsFrom = selectedFileOrDir;
        else
          selectedIndex = UINT_MAX; /** Force a break of the "while" loop. */
      }
    }
  }while(selectedIndex != UINT_MAX);
//#endif
  return selectedFileOrDir;
}
