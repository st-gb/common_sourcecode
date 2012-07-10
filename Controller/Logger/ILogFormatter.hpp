/*
 * ILogFileWriter.hpp
 *
 *  Created on: 26.04.2012
 *      Author: Stefan
 */

#ifndef ILOGFILEWRITER_HPP_
#define ILOGFILEWRITER_HPP_

#include <fstream> //for class std::ofstream ;
#include <sstream> //for class std::basic_stringstream ;
#include <vector> //class std::vector

#include "LogFileEntry.hpp" //class LogFileEntry
#include <data_structures/Trie/NodeTrie/NodeTrie.hpp> //class NodeTrie

//typedef uint16_t WORD;
//typedef
class Logger;

class uint16_tPointerAndBYTE
{
public:
  const uint16_t * m_p_uint16_t;
  BYTE m_numCharsToSkip;
//  BYTE m_charIndexOfLeftPercentSign;
  uint16_t m_charIndexOfLeftPercentSign;
  uint16_tPointerAndBYTE(
    const uint16_t * p_uint16_t,
    BYTE byte, //# bytes to skip on replacement of place holder on left "%"
    uint16_t charIndexOfLeftPercentSign
    )
    : m_p_uint16_t(p_uint16_t),
      m_numCharsToSkip (byte),
      m_charIndexOfLeftPercentSign(charIndexOfLeftPercentSign)
  {
  }
};

/** Base class for log stream formatting. May e.g. format as HTML.*/
class I_LogFormatter
{
private:
protected:
  const Logger * m_p_logger;
  char * m_p_chTimeString;
//  std::ofstream * m_p_std_ofstream;
  std::basic_ostream<char> * m_p_std_ofstream;
  std::string m_TimeFormatString;
  const LogFileEntry * m_p_logfileentry;
  NodeTrie<const uint16_t *> m_nodetrieTimePlaceHolderToLogFileEntryMember;
  std::vector<uint16_tPointerAndBYTE> m_vecPointerToTimeElementFromLogFileEntry;
public:

  enum MessageType{
    log_message_typeINFO,
    log_message_typeWARNING,
    log_message_typeERROR,
    log_message_typeSUCCESS,
    beyondLastLogMessageType
  };

  I_LogFormatter(//std::ofstream * p_std_ofstream
    const Logger * p_logger);
  virtual
  ~I_LogFormatter();

  void CreateTimePlaceHolderToLogFileEntryMemberMapping();
  uint16_t GetNeededArraySizeForTimeString(std::string timeFormatString);
  //inline
  void GetTimeAsString(const LogFileEntry & logfileentry//,
//    std::string & std_strTime
    );
  inline void Replace(
    const std::string & std_strToReplace,
    const std::string & std_strFromLogFileEntry
    );
  BYTE Replace(uint16_t IndexOf1stChar, uint16_t IndexOfLastChar,
//    std::string & std_strTime
    char * & ar_ch);
  void SetStdOstream(std::ostream * p_std_ostream)
    { m_p_std_ofstream = p_std_ostream; }
  void SetTimeFormat(const std::string & TimeFormatString);
  virtual void WriteHeader() {}
  virtual void WriteTrailer() {}

  virtual void WriteLogFileEntry(
    const LogFileEntry & logfileentry,
    enum MessageType messageType = log_message_typeINFO
    )
  {
//    static std::string std_strTime;
    GetTimeAsString(logfileentry//, std_strTime
      );
    * m_p_std_ofstream
//      << logfileentry.year << "-"
//      << (WORD) logfileentry.month << "-"
//      << (WORD) logfileentry.day << " "
//      << (WORD) logfileentry.hour << ":"
//      << (WORD) logfileentry.minute << ":"
//      << (WORD) logfileentry.second << ":"
//      << logfileentry.millisecond << ":"
//      << logfileentry.nanosecond << " "
//      << std_strTime
      << m_p_chTimeString
      << " "
      << * logfileentry.p_std_strMessage
//      << "\n"
      ;
  }

  virtual void WriteMessage(const std::string & r_std_strMessage,
    enum MessageType messageType = log_message_typeINFO)
  {
    * m_p_std_ofstream << r_std_strMessage << "\n";
  }
  virtual void WriteTimeStamp(const std::stringstream & std_str_stream)
  {
    * m_p_std_ofstream << std_str_stream.str() << ":";
  }
};

#endif /* ILOGFILEWRITER_HPP_ */
