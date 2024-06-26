/**Created on: 26.04.2012
 * @author Stefan Gebauer(TU Berlin matriculation number 361095)*/

///Include guard,see http://en.wikipedia.org/wiki/Include_guard :

/**Define on compiler command line,for example for GCC:
 * (see http://gcc.gnu.org/onlinedocs/gcc/Preprocessor-Options.html :)
 * "gcc -D TU_Bln361095UsePrgmInclGuard"*/
/**Bln=BerLiN: http://www.acronymfinder.com/Berlin-(Bln).html
 * Prgm=PRaGMa
 * Incl=INCLude: http://www.abbreviations.com/abbreviation/include
 * Grd=GuaRD: http://www.abbreviations.com/abbreviation/Guard */
#ifdef TU_Bln361095usePrgmInclGrd
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
  #pragma once
#endif
#if defined TU_Bln361095usePrgmInclGrd ||\
/**Include guard supported by (nearly) all industry compilers:*/\
/**Bln=BerLiN: http://www.acronymfinder.com/Berlin-(Bln).html
 * cmn=CoMmoN: http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe: http://www.abbreviations.com/abbreviation/source */\
 !defined TU_Bln361095cmnSrc__Logger__Formatter__I_LogFormatter_hpp
  #define TU_Bln361095cmnSrc__Logger__Formatter__I_LogFormatter_hpp

///C(++) standard library header files:
 #include <fstream>///class std::ofstream ;
 #include <sstream>///class std::basic_stringstream ;
 #include <vector>///class std::vector

///Stefan Gebauer's(TU Berlin matricul. number 361095) ~"cmnSrc" repository files:
 #include "../LogFileEntry.hpp"///class LogFileEntry
 #include "../LogLevel.hpp"///namespace LogLevel::MessageType
 #include <data_structures/Trie/NodeTrie/NodeTrie.hpp>///class NodeTrie
//using namespace LogLevel;

//typedef uint16_t WORD;
//typedef
//class Logger;
//class I_LogEntryOutputter;
class FormattedLogEntryProcessor;

struct PointerToLogFileEntryMemberAndNumFormatChars
{
  BYTE m_numCharsToFormat;///NUMber of CHARacter TO FORMAT 
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
  /** Formatted string with placeholders replaced with actual time, e.g. 
   *   "{year} {day]" -> "2010 6" */
  char * m_p_chFormattedTimeString;
//  std::ofstream * m_p_std_ostream;
  std::basic_ostream<char> * m_p_std_ostream;
  /** Format string with placeholders for time members like "{year}{day]" */
  std::string m_TimeFormatString;
  static const std::string s_std_strDefaultLinuxLogTimeFormatString;
  static const std::string s_std_strDefaultWindowsLogTimeFormatString;
  const LogFileEntry * m_p_logfileentry;
//  NodeTrie<const uint16_t *> m_nodetrieTimePlaceHolderToLogFileEntryMember;
  NodeTrie<PointerToLogFileEntryMemberAndNumFormatChars *>
    m_nodetrieTimePlaceHolderToLogFileEntryMember;
  std::vector<uint16_tPointerAndBYTE>
    ///VECtor of PoinTeR TO TiMe ELEment FROM LOG FILE ENTRY
    m_vecPtrToTmEleFromLogFileEntry;
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
    enum LogLevel::MessageType messageType = LogLevel::info,
    const char * const prettyFunctionFormattedFunctionName = NULL
    )
  {
//    static std::string std_strTime;
    GetTimeAsString(logfileentry//, std_strTime
      );
#ifdef __ANDROID__
    * m_p_std_ostream
      << m_p_chFormattedTimeString
      << prettyFunctionFormattedFunctionName << " "
      << (* logfileentry.p_std_strMessage).c_str()
//      << "\n"
      ;
#else
    * m_p_std_ostream
      << m_p_chFormattedTimeString
      << " thread ID:" << logfileentry.threadID << " "
      << prettyFunctionFormattedFunctionName << " "
      << * logfileentry.p_std_strMessage
//      << "\n"
      ;
#endif
  }

  virtual void WriteMessage(const std::string & r_std_strMessage,
    enum LogLevel::MessageType messageType = LogLevel::info)
  {
    /** "c_str()" is needed for ANDROID compiler */
    * m_p_std_ostream << r_std_strMessage.c_str() << "\n";
  }
  virtual void WriteTimeStamp(const std::stringstream & std_str_stream)
  {
	/** "c_str()" is needed for ANDROID compiler */
    * m_p_std_ostream << std_str_stream.str().c_str() << ":";
  }
};

#endif///include guard
