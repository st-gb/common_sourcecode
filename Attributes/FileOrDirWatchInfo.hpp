/*
 * FileOrDirWatchInfo.hpp
 *
 *  Created on: Nov 20, 2010
 *      Author: Stefan
 */

#ifndef FILEORDIRWATCHINFO_HPP_
#define FILEORDIRWATCHINFO_HPP_

#include <string> //std::wstring

//Named "watch" and not "change" because not only changes are being tracked.
class FileOrDirWatchInfo
//class FileOrDirWatchAttributes
{
public:
  BYTE m_byAction ;
  DWORD m_dwFileNameLength;
  wchar_t * m_p_wchFileName ;
  wchar_t * m_p_wchRootPath ;
  std::wstring m_stdwstrOldFileOrDirPath ;
  std::wstring m_stdwstrCurrentFileOrDirPath ;
} ;

#endif /* FILEORDIRWATCHINFO_HPP_ */
