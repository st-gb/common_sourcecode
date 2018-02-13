/** GetDirContents.cpp
 *  Created on: 17.01.2018
 *      Author: s.gebauer */
#include <string.h> //strcat(...)
#include <vector> //class std::vector
#include <string> //class std::string
#include <windows.h> //::FindFirstFile(...)

namespace FileSystem {
/** @param p_ch : NULL to get # of needed chars */
/*char * */ unsigned GetDirContents(
  const char * const dirToRetrieveContentsFrom,
  std::vector<std::string> & dirEntries
  )
{
  //TODO ensure array is big enough for device file name (use MAX_PATH constant,
  // create array on heap etc.
  WIN32_FIND_DATAA wIN32_FIND_DATA;
  HANDLE hFind = INVALID_HANDLE_VALUE;
  /** adapted from 
    https://msdn.microsoft.com/de-de/library/windows/desktop/aa365200(v=vs.85).aspx */
  hFind = ::FindFirstFileA(dirToRetrieveContentsFrom, &wIN32_FIND_DATA);
  if(hFind == INVALID_HANDLE_VALUE) 
    return 1;
  do
  {
    dirEntries.push_back(wIN32_FIND_DATA.cFileName);
  }
  while(FindNextFileA(hFind, &wIN32_FIND_DATA) != 0);
  FindClose(hFind);
  return 0;
}
}