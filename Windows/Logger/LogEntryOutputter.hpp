/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany
 * ("Trilobyte SE") 2010-at least 2012.
 * You are allowed to modify and use the source code from Trilobyte SE for free
 * if you are not making profit directly or indirectly with it or its adaption.
 * Else you may contact Trilobyte SE. */
/*
 * LogEntryOutputter.hpp
 *
 *  Created on: 05.07.2012
 *      Author: Stefan
 */

#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <sstream> //class std::ostringstream
#include <windows.h> //HANDLE
//#include <Controller/Logger/Logger.hpp> //base class "LogEntryOutputter"
#include <Controller/Logger/OutputHandler/I_LogEntryOutputter.hpp> //base class "LogEntryOutputter"

#ifdef _WIN32
namespace Windows_API
{
  class LogEntryOutputter
    : public ::I_LogEntryOutputter
  {
  private:
    HANDLE m_hFile;
    LPVOID m_buffer;
    DWORD m_dwBufferSize;
    //Formatted from LogFormatter.
    std::ostringstream m_std_stringstream;
  public:
    DWORD m_dwGetLastErrorAfterCreateFileA;
    LogEntryOutputter();
    virtual
    ~LogEntryOutputter();

    unsigned Close();
    std::ostream * GetStdOstream() const {
      return (std::ostream *) & m_std_stringstream; }

//    DWORD Log(//ostream & ostr
//      const std::string & r_stdstrMessage,
//      enum I_LogFormatter::MessageType messageType =
//        I_LogFormatter::log_message_typeINFO
//      )
//    {
////      EnterCritSec();
//#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
//      if( //Is NULL before file was opened.
//          m_p_std_ostream
//        IsNotFiltered(r_stdstrMessage)
//        )
//#endif //#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
//      {
//        return OutputTimeStampEtc_Inline(r_stdstrMessage, messageType);
////        POSSIBLY_LEAVE_CRIT_SEC
////        Ideas();
//      }
////#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
////      else
////        m_critical_section_typeLogging.Leave() ;
////#endif
////      POSSIBLY_LEAVE_CRIT_SEC
//      return 0;
//    }
    bool IsOpen()    {     return m_hFile != INVALID_HANDLE_VALUE; }
    bool OpenA(const std::string & c_r_stdstrFilePath);

    bool SetStdOstream(const std::string & c_r_stdstrFilePath);
//    bool OpenFile2( const std::string & c_r_stdstrFilePath );
    bool OpenFlushingFile(const std::string & c_r_stdstrFilePath);
    int RenameFileThreadUnsafe(const std::string & r_stdstrFilePath);
    unsigned DoOutput();
  };

} /* namespace Windows_API */
#endif
#endif /* LOGGER_HPP_ */
