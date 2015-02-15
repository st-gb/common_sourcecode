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
//#include <exception> //class std::exception
#include <IO/FileAccessException.hpp> //base class

class LogFileAccessException
  : public /*std::exception*/ FileAccessException
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
    const DWORD operatinSystemErrorCode,
    const char * const logFilePath)
  {
    m_action = action;
    m_operatingSystemErrorCode = operatinSystemErrorCode;
    m_filePath = logFilePath;
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
    const std::string std_strAbsoluteLogFilePath = GetAbsoluteFilePathA();

    std_strErrorMessage += " log file \"" + std_strAbsoluteLogFilePath + "\" failed:";
    const std::string std_strErrorMessageFromErrorCode =
      ::GetErrorMessageFromErrorCodeA(m_operatingSystemErrorCode);
    std_strErrorMessage += std_strErrorMessageFromErrorCode;
    return std_strErrorMessage;
  }
};

#endif /* LOGFILEACCESSEXCEPTION_HPP_ */
