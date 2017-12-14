/* 
 * File:   DictionaryFileRessAccessException.h
 * Author: mr.sys
 *
 * Created on 14. Februar 2015, 15:20
 */

#ifndef DICTIONARYFILERESSACCESSEXCEPTION_HPP
#define	DICTIONARYFILERESSACCESSEXCEPTION_HPP

#include <FileSystem/File/File.hpp>
#include "FileException.hpp"
#include <string> //class std::string

class FileReadException
  : public FileException
{
  enum I_File::ReadResult m_res;
  unsigned m_operatingSystemErrorCode;
  std::string m_filePath;
public:
  FileReadException(
    const enum I_File::ReadResult res,
    const DWORD operatinSystemErrorCode,
    const char * const filePath )
  {
    m_res = res;
    m_operatingSystemErrorCode = operatinSystemErrorCode;
    m_filePath = filePath;
  }
  //DictionaryFileRessAccessException(const DictionaryFileRessAccessException& orig);
  virtual ~FileReadException() { };
  
  enum I_File::ReadResult GetResult() const { return m_res; } 
  unsigned GetOSerrorCode() const { return m_operatingSystemErrorCode; }
private:

};

#endif	/* DICTIONARYFILERESSACCESSEXCEPTION_HPP */

