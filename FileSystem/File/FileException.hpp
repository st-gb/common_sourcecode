#pragma once

#include <tchar.h>
#include <string.h> //strlen(...)
#include <preprocessor_macros/Windows_compatible_typedefs.h> //DWORD

class FileException
{
protected:
	//std::tstring str;
	//  TCHAR * m_filePath;
	//TODO why not use a std::wstring here?->deleting the array in the destructor
	// would be unneccessary
	wchar_t * m_filePath;
	//  std::wstring m_filePath;
	DWORD m_operatingSystemErrorCode;
public:
  void cpyWchars(const wchar_t chFilePath []){
    const int stringLength = wcslen(chFilePath);
    m_filePath = new wchar_t[stringLength 
      /** Plus 1 character for string terminating '0' char.*/ + 1];
    wcscpy(m_filePath, chFilePath);
  }
  
  FileException() : m_filePath(0), m_operatingSystemErrorCode(0) { }
  
  FileException(const wchar_t * const chFilePath)
    : m_operatingSystemErrorCode(0)
//    , m_filePath(chFilePath)
  {
    cpyWchars(chFilePath);
  }
  
  FileException(const char * const chFilePath)
    : m_operatingSystemErrorCode(0)
  {
    const unsigned int stringLength = strlen(chFilePath);
    m_filePath = new wchar_t[stringLength + 1];
//    _tcscpy(m_filePath, chFilePath);
    for( unsigned int index = 0; index < stringLength; index ++ )
    {
      m_filePath[index] = chFilePath[index];
    }
    m_filePath[stringLength] = L'\0';
    //str = ch;
  }

  ///Also called when doing a "throw" with an object of this class.
  FileException(const FileException & fe)
  {
    cpyWchars(fe.m_filePath);
    m_operatingSystemErrorCode = fe.m_operatingSystemErrorCode;
  }

  /** Called when created on stack a´when leaving block or at end of catch(...)
   *  with a FileException-based class.*/
  ~FileException()
  {
    if( m_filePath){
      delete [] m_filePath;
      m_filePath = NULL;
    }
  }

  //TODO?
//  inline const std::string GetErrorMessageA() const
//  {
//
//  }
  
  wchar_t * GetFilePath() const
  {
    return m_filePath;
  }
};
