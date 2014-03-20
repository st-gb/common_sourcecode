/*
 * LogFileAccessException.hpp
 *
 *  Created on: 19.02.2014
 *      Author: mr.sys
 */

#ifndef LOGFILEACCESSEXCEPTION_HPP_
#define LOGFILEACCESSEXCEPTION_HPP_

//::GetErrorMessageFromLastErrorCode()
#include <Controller/GetErrorMessageFromLastErrorCode.hpp>
#include <FileSystem/IsRelativePath.hpp> //bool FileSystem::IsRelativePath(...)
#include <FileSystem/GetCurrentWorkingDir.hpp> //GetCurrentWorkingDir(...)
//#include <exception> //class std::exception

class LogFileAccessException
//  : public std::exception
{
  std::string m_errorMessage;
public:
  enum action { deleteLogFile, openLogFile, writeToFile};
  enum action m_action;
  DWORD m_operatingSystemErrorCode;
  std::string m_logFilePath;

  /** Copy constructor */
  LogFileAccessException(
    const LogFileAccessException & originalToCopyFrom)
    : m_action (originalToCopyFrom.m_action)
    , m_operatingSystemErrorCode (originalToCopyFrom.m_operatingSystemErrorCode)
    , m_logFilePath( originalToCopyFrom.m_logFilePath) { }

//  LogFileAccessException(const char * const pch)
//  {
//    m_errorMessage = pch;
//  }
  LogFileAccessException(
    const enum action action,
    const DWORD operatinSystemErrorCode,
    const char * const logFilePath)
  {
    m_action = action;
    m_operatingSystemErrorCode = operatinSystemErrorCode;
    m_logFilePath = logFilePath;
  }

  const std::string GetAbsoluteLogFilePath() const
  {
    std::string std_strAbsoluteLogFilePath;
    if( FileSystem::IsRelativePathA(m_logFilePath.c_str() ) )
    {
      std::string std_strCurrentDirectory;
//      OperatingSystem::GetCurrentWorkingDirA_inl(std_strCurrentDirectory);
#ifdef _WIN32
      Windows::GetCurrentWorkingDirA_inl(std_strCurrentDirectory);
#else
      /*OperatingSystem*/Linux::GetCurrentWorkingDirA_inl(std_strCurrentDirectory);
#endif
      std_strAbsoluteLogFilePath += std_strCurrentDirectory += m_logFilePath;
      return std_strAbsoluteLogFilePath;
    }
    return m_logFilePath;
  }

  inline const std::string GetErrorMessage() const
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
    const std::string std_strAbsoluteLogFilePath = GetAbsoluteLogFilePath();

    std_strErrorMessage += " log file \"" + std_strAbsoluteLogFilePath + "\" failed:";
    const std::string std_strErrorMessageFromErrorCode =
      ::GetErrorMessageFromErrorCodeA(m_operatingSystemErrorCode);
    std_strErrorMessage += std_strErrorMessageFromErrorCode;
    return std_strErrorMessage;
  }
};

#endif /* LOGFILEACCESSEXCEPTION_HPP_ */
