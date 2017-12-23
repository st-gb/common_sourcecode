#pragma once

#include "FileException.hpp"

class EndOfFileException
  : public FileException
{
public:
  //std::tstring str;
  //TCHAR * m_filePath;
  
  EndOfFileException(const char * const chFilePath)
    : FileException(chFilePath)
  {
  }
  EndOfFileException(const wchar_t * const chFilePath)
    : FileException(chFilePath)
  {
  }
  
  ~EndOfFileException()
  {
  }  
};