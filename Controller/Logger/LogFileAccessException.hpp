/**(c)from 2014 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
*Created 19.2.2014 by Stefan Gebauer(TU Berlin matriculation number 361095)*/

///Include guard,see http://en.wikipedia.org/wiki/Include_guard :

/**Bln=BerLiN:http://www.acronymfinder.com/Berlin-(Bln).html
 * Prgm=PRaGMa
 * Incl=INCLude:http://www.abbreviations.com/abbreviation/include
 * Grd=GuaRD:http://www.abbreviations.com/abbreviation/guard */
#ifdef TU_Bln361095usePrgmInclGrd
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
  #pragma once
#endif
#if defined TU_Bln361095usePrgmInclGrd ||\
/**Include guard supported by (nearly) all industry compilers:*/\
/**Bln=BerLiN: http://www.acronymfinder.com/Berlin-(Bln).html
 * cmn=CoMmoN: http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe: http://www.abbreviations.com/abbreviation/Source */\
 ! defined TU_Bln361095cmnSrc_Logger_LogFileAccessException_hpp
   #define TU_Bln361095cmnSrc_Logger_LogFileAccessException_hpp

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
#include <dataType/charStr/stdtstr.hpp>///GetStdString_Inline(...)
#include <FileSystem/File/FileException.hpp>///base class
#include <FileSystem/GetAbsolutePath.hpp>///TU_Bln361095::FileSys::GetAbsPathA
 //::GetErrorMessageFromLastErrorCode()
#include <OperatingSystem/GetErrorMessageFromErrorCode.h>

//#include <exception> //class std::exception
//#include <InputOutput/FileAccessException.hpp> //base class

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
    std::string std_strAbsoluteLogFilePath;
    const DWORD getAbsPathRslt = TU_Bln361095::FileSys::
    /**Taking the absolute file path is neccessary because the current working
     * directory may change later.*/
      GetAbsPathA(logFilePath, std_strAbsoluteLogFilePath);
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
    std::string std_strAbsoluteLogFilePath;
    const DWORD getAbsPathRslt = TU_Bln361095::FileSys::
      GetAbsPathA(std_strFilePath.c_str(), std_strAbsoluteLogFilePath);

    std_strErrorMessage += " log file \"" + std_strAbsoluteLogFilePath + "\" failed:";
    const std::string std_strErrorMessageFromErrorCode =
      OperatingSystem::GetErrorMessageFromErrorCodeA(m_operatingSystemErrorCode);
    std_strErrorMessage += std_strErrorMessageFromErrorCode;
    return std_strErrorMessage;
  }
};

#endif///include guard
