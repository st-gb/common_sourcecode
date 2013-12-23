/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany
 * ("Trilobyte SE") 2010-at least 2012.
 * You are allowed to modify and use the source code from Trilobyte SE for free
 * if you are not making profit directly or indirectly with it or its adaption.
 * Else you may contact Trilobyte SE. */
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

#include "../LogFileEntry.hpp" //class LogFileEntry
#include <data_structures/Trie/NodeTrie/NodeTrie.hpp> //class NodeTrie

#include "../LogLevel.hpp" //namespace LogLevel::MessageType
using namespace LogLevel;

//typedef uint16_t WORD;
//typedef
//class Logger;
//class I_LogEntryOutputter;
class FormattedLogEntryProcessor;

struct PointerToLogFileEntryMemberAndNumFormatChars
{
  BYTE m_numCharsToFormat;
  const void * m_p_logfileentrymember;
  PointerToLogFileEntryMemberAndNumFormatChars(BYTE numCharsToFormat,
    const void * p_logfileentrymember)
    : m_numCharsToFormat(numCharsToFormat),
      m_p_logfileentrymember(p_logfileentrymember)
  {
  }
};

class uint16_tPointerAndBYTE
{
public:
//  const uint16_t * m_p_uint16_t;
//  BYTE m_numCharsToFormat;
  PointerToLogFileEntryMemberAndNumFormatChars *
    m_p_p_logfileentrymember_and_num_formatchars;
  BYTE m_numCharsToSkip;
//  BYTE m_charIndexOfLeftPercentSign;
  uint16_t m_charIndexOfLeftPercentSign;
  uint16_tPointerAndBYTE(
//    const uint16_t * p_uint16_t,
    PointerToLogFileEntryMemberAndNumFormatChars *
      p_p_logfileentrymember_and_num_formatchars,
    BYTE byte, //# bytes to skip on replacement of place holder on left "%"
    uint16_t charIndexOfLeftPercentSign//,
//    BYTE numCharsToFormat
    )
    : //m_p_uint16_t(p_uint16_t),
      m_p_p_logfileentrymember_and_num_formatchars(
        p_p_logfileentrymember_and_num_formatchars),
      m_numCharsToSkip (byte),
      m_charIndexOfLeftPercentSign(charIndexOfLeftPercentSign//,
//      m_numCharsToFormat(numCharsToFormat)
      )
  {
  }
};

/** @brief Base class for log stream formatter. Child classes may e.g. format as HTML.
 * Name should not contain a log destination like a file (because formatting
 * ought to be independent of the log destination), so name it like
 * "log formatter". */
class I_LogFormatter
{
private:
protected:
//  const Logger * m_p_logger;
//  const I_LogEntryOutputter * m_p_outputhandler;
  const FormattedLogEntryProcessor * m_p_formattedlogentryprocessor;
  char * m_p_chTimeString;
//  std::ofstream * m_p_std_ostream;
  std::basic_ostream<char> * m_p_std_ostream;
  std::string m_TimeFormatString;
  static const std::string s_std_strDefaultLinuxLogTimeFormatString;
  static const std::string s_std_strDefaultWindowsLogTimeFormatString;
  const LogFileEntry * m_p_logfileentry;
//  NodeTrie<const uint16_t *> m_nodetrieTimePlaceHolderToLogFileEntryMember;
  NodeTrie<PointerToLogFileEntryMemberAndNumFormatChars *>
    m_nodetrieTimePlaceHolderToLogFileEntryMember;
//  std::vector<uint16_tPointerAndBYTE> m_vecPointerToTimeElementFromLogFileEntry;
  std::vector<uint16_tPointerAndBYTE> m_vecPointerToTimeElementFromLogFileEntry;
public:

  I_LogFormatter(//std::ofstream * p_std_ofstream
    const /*Logger * p_logger I_LogEntryOutputter */
    FormattedLogEntryProcessor * );
  virtual
  ~I_LogFormatter();

  void CreateTimePlaceHolderToLogFileEntryMemberMapping();
  /*NodeTrie::size_type*/ unsigned
    DeleteTimePlaceHolderToLogFileEntryMemberNodeTrie()
  {
    /*NodeTrie::size_type*/ unsigned numNodes;
    m_nodetrieTimePlaceHolderToLogFileEntryMember.DeleteWithMember(numNodes);
    return numNodes;
  }
  uint16_t GetNeededArraySizeForTimeString(const std::string & timeFormatString);
  //inline
  unsigned long GetNumberOfTimePlaceHolderToLogFileEntryMemberNodes()
  {
    return m_nodetrieTimePlaceHolderToLogFileEntryMember.getNumberOfNodes();
  }
  void GetTimeAsString(const LogFileEntry & logfileentry//,
//    std::string & std_strTime
    );
  void Init(std::ostream /*&*/ * p_std_ostream = NULL,
    const std::string * p_std_strLogTimeFormatString = NULL
    );
  void SetStdOstream(std::ostream * p_std_ostream)
    { m_p_std_ostream = p_std_ostream; }
  void SetDefaultTimeFormat();
  void SetTimeFormat(const std::string & TimeFormatString);
  /** Must be virtual for polymorphism
   * @brief write HTML header (opening tags) for instance. */
  virtual void WriteHeader() {}
  /** Must be virtual for polymorphism
   * @brief write HTML footer (closing tags) for instance. */
  virtual void WriteTrailer() {}

  /** Must be virtual for polymorphism
   * @brief for an HTML formatter write "table row" ("<TR>")tags for instance
   *   for every logentry. */
  virtual void WriteLogFileEntry(
    const LogFileEntry & logfileentry,
    enum MessageType messageType = LogLevel::info,
    const char * const prettyFunctionFormattedFunctionName = NULL
    )
  {
//    static std::string std_strTime;
    GetTimeAsString(logfileentry//, std_strTime
      );
    * m_p_std_ostream
      << m_p_chTimeString
      << " thread ID:" << logfileentry.threadID << " "
      << prettyFunctionFormattedFunctionName << " "
      << * logfileentry.p_std_strMessage
//      << "\n"
      ;
  }

  virtual void WriteMessage(const std::string & r_std_strMessage,
    enum MessageType messageType = LogLevel::info)
  {
    * m_p_std_ostream << r_std_strMessage << "\n";
  }
  virtual void WriteTimeStamp(const std::stringstream & std_str_stream)
  {
    * m_p_std_ostream << std_str_stream.str() << ":";
  }
};

#endif /* ILOGFILEWRITER_HPP_ */
