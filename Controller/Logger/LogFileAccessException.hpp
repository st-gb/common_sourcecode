/*
 * LogFileAccessException.hpp
 *
 *  Created on: 19.02.2014
 *      Author: mr.sys
 */

#ifndef LOGFILEACCESSEXCEPTION_HPP_
#define LOGFILEACCESSEXCEPTION_HPP_

//::GetErrorMessageFromLastErrorCode()
#include <OperatingSystem/GetErrorMessageFromErrorCode.h>

//#include <exception> //class std::exception
//#include <InputOutput/FileAccessException.hpp> //base class
#include <FileSystem/File/FileException.hpp> //base class
#include <FileSystem/GetAbsolutePath.hpp> //GetAbsolutePathA
#include <Controller/character_string/stdtstr.hpp>

class LogFileAccessException
  : public /*std::exception*/ /*FileAccessException*/ FileException
{
  std::string m_errorMessage;
public:
  enum action { deleteLogFile, openLogFile, writeToFile};
  enum action m_action;

//  /** Copy constructor */
//  LogFileAccessException(
//    const LogFileAccessException & originalToCopyFrom)
//    : m_action (originalToCopyFrom.m_action)
//    , m_operatingSystemErrorCode (originalToCopyFrom.m_operatingSystemErrorCode)
//    , m_filePath( originalToCopyFrom.m_filePath) { }

//  LogFileAccessException(const char * const pch)
//  {
//    m_errorMessage = pch;
//  }
  LogFileAccessException(
    const enum action action,
    const DWORD operatingSystemErrorCode,
    //const wchar_t * const logFilePath
    const char * const logFilePath
	)
    : FileException(logFilePath)
  {
    m_action = action;
    m_operatingSystemErrorCode = operatingSystemErrorCode;
//    m_filePath = /*(wchar_t *)*/ GetStdWstring( std::string(logFilePath) );
    //TODO use variable
    const std::string std_strAbsoluteLogFilePath = FileSystem::
    ///Taking the absolute file path is neccessary because the current working
    /// directory may change later.
      GetAbsolutePathA(logFilePath );
  }

  /** Get errror message as 1-byte / ASCII string. */
  inline const std::string GetErrorMessageA() const
  {
    std::string std_strErrorMessage;
    switch(m_action)
    {
    case deleteLogFile:
      std_strErrorMessage = "deleting";
      break;
    case openLogFile:
      std_strErrorMessage = "opening";
      break;
    default:
      std_strErrorMessage = "other action regarding";
      break;
   }
    const std::string std_strFilePath = ::GetStdString_Inline(m_filePath);
    ///Taking the absolute file path is neccessary because the current working
    /// directory may change later.
    const std::string std_strAbsoluteLogFilePath = FileSystem::
      GetAbsolutePathA(std_strFilePath.c_str() );

    std_strErrorMessage += " log file \"" + std_strAbsoluteLogFilePath + "\" failed:";
    const std::string std_strErrorMessageFromErrorCode =
      OperatingSystem::GetErrorMessageFromErrorCodeA(m_operatingSystemErrorCode);
    std_strErrorMessage += std_strErrorMessageFromErrorCode;
    return std_strErrorMessage;
  }
};

#endif /* LOGFILEACCESSEXCEPTION_HPP_ */
