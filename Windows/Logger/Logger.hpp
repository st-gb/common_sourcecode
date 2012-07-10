/*
 * Logger.hpp
 *
 *  Created on: 05.07.2012
 *      Author: Stefan
 */

#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <sstream> //class std::ostringstream
#include <windows.h> //HANDLE
#include <Controller/Logger/Logger.hpp> //base class "Logger"

#ifdef _WIN32
namespace Windows_API
{

  class Logger
    : public ::Logger
  {
  private:
    HANDLE m_hFile;
    std::ostringstream m_std_stringstream;
  public:
    Logger();
    virtual
    ~Logger();

    std::ostream & GetStdOstream() const {
      return (std::ostream &) m_std_stringstream; }

    DWORD Log(//ostream & ostr
      const std::string & r_stdstrMessage,
      enum I_LogFormatter::MessageType messageType =
        I_LogFormatter::log_message_typeINFO
      )
    {
//      EnterCritSec();
#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
      if(
        IsNotFiltered(r_stdstrMessage)
        )
#endif //#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
      {
        return OutputTimeStampEtc_Inline(r_stdstrMessage, messageType);
//        POSSIBLY_LEAVE_CRIT_SEC
//        Ideas();
      }
//#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
//      else
//        m_critical_section_typeLogging.Leave() ;
//#endif
//      POSSIBLY_LEAVE_CRIT_SEC
    }
    bool IsOpen()    {     return m_hFile != INVALID_HANDLE_VALUE; }

    bool OpenFile2( const std::string & c_r_stdstrFilePath );
    bool OpenFlushingFile(const std::string & c_r_stdstrFilePath);
    DWORD WriteToFile();
  };

} /* namespace Windows_API */
#endif
#endif /* LOGGER_HPP_ */
