#pragma once

#include <tchar.h>
#include <string.h> //strlen

class FileException
{
public:
  //std::tstring str;
//  TCHAR * m_filePath;
  wchar_t * m_filePath;
//  std::wstring m_filePath;
  DWORD m_operatingSystemErrorCode;
  
  FileException() : m_operatingSystemErrorCode(0) { }
  
  FileException(const wchar_t * const chFilePath)
    : m_operatingSystemErrorCode(0)
//    , m_filePath(chFilePath)
  {
    const int stringLength = wcslen(chFilePath);
    m_filePath = new wchar_t[stringLength + 1];
    wcscpy(m_filePath, chFilePath);
  }
  
  FileException(const char * const chFilePath)
    : m_operatingSystemErrorCode(0)
  {
    const int stringLength = strlen(chFilePath);
    m_filePath = new TCHAR[stringLength + 1];
//    _tcscpy(m_filePath, chFilePath);
    for( unsigned int index = 0; index < stringLength; index ++ )
    {
      m_filePath[index] = chFilePath[index];
    }
    m_filePath[stringLength] = L'\0';
    //str = ch;
  }
  
  ~FileException()
  {
    delete [] m_filePath;
  }
  
  inline const std::string GetErrorMessageA() const
  {
    
  }
  
  TCHAR * GetFilePath() const
  {
    return m_filePath;
  }
};
