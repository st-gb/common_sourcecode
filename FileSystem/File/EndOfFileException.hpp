#pragma once

#include "FileException.hpp"

class EndOfFileException
  : public FileException
{
public:
  //std::tstring str;
  TCHAR * m_filePath;
  
  EndOfFileException(const TCHAR * const chFilePath)
	: FileException(chFilePath)
  {
  }
  ~EndOfFileException()
  {
  }  
};