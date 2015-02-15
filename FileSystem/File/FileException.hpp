#pragma once

#include <tchar.h>

class FileException
{
public:
  //std::tstring str;
  TCHAR * m_filePath;
  
  FileException(const TCHAR * const chFilePath)
  {
    const int stringLength = _tcslen(chFilePath);
    m_filePath = new TCHAR[stringLength + 1];
    _tcscpy(m_filePath, chFilePath);
    m_filePath[stringLength] = _T('\0');
    //str = ch;
  }
  ~FileException()
  {
    delete [] m_filePath;
  }
  
  TCHAR * GetFilePath() const
  {
    return m_filePath;
  }
};