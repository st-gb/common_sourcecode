/*
 * FormattedLogEntryProcessor.hpp
 *
 *  Created on: 07.02.2013
 *      Author: Stefan
 */

#ifndef FORMATTEDLOGENTRYPROCESSOR_HPP_
#define FORMATTEDLOGENTRYPROCESSOR_HPP_

//#include <Controller/Logger/Logger.hpp> //class Logger
#include <Controller/Logger/LogLevel.hpp> //class LogLevel::enum MessageType
#include <Controller/Logger/LogFileEntry.hpp> //class LogFileEntry
#include <Controller/Logger/OutputHandler/I_LogEntryOutputter.hpp>
#include <Controller/Logger/Formatter/I_LogFormatter.hpp> //class ILogFormatter
#include <limits.h> //UINT_MAX
#include <fastest_data_type.h>

//Fwd decl.
class I_LogFormatter;
class Logger;

/** @brief Handles the (output of a) log entry _after_ it has been formatted.
 *  So e.g. following subclasses are possible:
 *  -rolling file output (if log file exceeds >>n<< entries then it is logged
 *   to another file )
 *  -appending file output: writes always to the same log file.
 *
 *  So in contrast to log4j the calling of the _actual_/physical output (Windows API, std::ofstream, ...)
 *  is separated from the appending (rolling file or not) and does not need to
 *  be implemented in 1 single class.
 *  So _not_ all appender+outputter combinations must be implemented in a single class.
 *
 *  This class holds (pointers to)
 *   -@see outputter
 *   -@see formatter
 *  */
class FormattedLogEntryProcessor
{
protected:
  std::string m_filePath;
  LogFileEntry * m_p_logfileentry;
//    HTMLformatLogFileWriter * m_p_log_writer;
  I_LogEntryOutputter * m_p_outputhandler;
  I_LogFormatter * m_p_log_formatter;
//  protected:
    std::ostream * m_p_std_ostream ;
#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
    //Trie m_trie ;
    NodeTrie<BYTE> m_trie ;
  public:
    /** Important: return reference ("&"): else changes on it do not affect
     * _this_ object's trie */
    NodeTrie<BYTE> & GetTrie() { return m_trie; }
#endif //#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
public:
  LogFileEntry * GetLogFileEntry() const { return m_p_logfileentry; }
  enum TrieNodeMemberValue
  {
    no_string_end = 0,
    string_end
  };
//  FormattedLogEntryProcessor();
//  virtual
//  ~FormattedLogEntryProcessor();
  enum LogLevel::MessageType m_logLevel;
  std::ostream /*&*/ * GetStdOstream() const {
    if( m_p_outputhandler )
      return m_p_outputhandler->GetStdOstream();
    return NULL;
  }

#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
    void AddExcludeFromLogging(const std::string & cr_stdstr ) ;
#endif //#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT

  FormattedLogEntryProcessor( /*std::string & stdstrFilePath*/
    Logger & logger,
    I_LogEntryOutputter * p_outputhandler,
    I_LogFormatter * p_log_formatter,
    enum LogLevel::MessageType logLevel = LogLevel::info
    );
  FormattedLogEntryProcessor( /*std::string & stdstrFilePath*/
    Logger & logger,
    const std::string & filePath,
    I_LogEntryOutputter * p_outputhandler,
    const std::string & format = "txt",
    enum LogLevel::MessageType logLevel = LogLevel::info
    );
//  {
//      //m_ofstream.open(stdstrFilePath.c_str() );
//  //  m_stdsetLogClass.insert(Logger::sync) ;
//  }

  virtual ~FormattedLogEntryProcessor();

  I_LogFormatter * CreateTextFormatter()
  {
#ifdef _WIN32
    /** Windows can resolve times to milliseconds with GetLocalTime(...),
     * 100 ms with GetSystemTimeAsFileTime(...), so sesolution until "ms" is
     * ensured */
    std::string std_str =
      "{year}.{month}.{day} {hour}:{minute}:{second}s{millisecond}ms";
#endif
#ifdef __linux__
    /** Linux can resolve times to microiseconds with ::gettimeofday(...)*/
    std::string std_str =
      "{year}.{month}.{day} {hour}:{minute}:{second}s{millisecond}ms{microsecond}us"
      "{microsecond}us";
#endif
    return CreateFormatter("", std_str
      );
  }
  I_LogFormatter * CreateFormatter(//BYTE type = 1
    //const std::string & std_strType //= std::string("html")
    const char * c_p_chType = "html"
    ,const std::string & std_strLogTimeFormatString =
      "{year}.{month}.{day}&nbsp;{hour}:{minute}:{second}s{millisecond}ms"
    //const char * c_p_chLogTimeFormatString
    );
  /** Get really used file path. e.g. for rolling files it may be
   * "program_">>number<<"_log", for instance program_0_log". */
  virtual bool GetActualFilePath(std::string & std_str)
    { std_str = m_filePath; return true; }
  const std::string & GetFilePath() const { return m_filePath; }
  I_LogFormatter * GetFormatter() { return m_p_log_formatter; }
  enum LogLevel::MessageType GetLogLevel() { return m_logLevel; }

  /** @param p_ch : char data type, so "std::string::c_str()" and char string
   * are possible.
   *  @param strLen : for std::string pass std::string::length() */
  inline bool FunctionIsNotFiltered(/*const std::string & r_std_strTestIfFiltered*/
    const char * const p_ch, const fastestUnsignedDataType strLen) const
  {
#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
    bool bIsNotFiltered = true;
  //      m_stdsetstdstrExcludeFromLogging.find(r_stdstr) ==
  //      m_stdsetstdstrExcludeFromLogging.end()
    NodeTrieNode<BYTE> * p_ntn =
      //If NOT in the container.
      ( (NodeTrie<BYTE> &) m_trie).//exists_inline(
        contains_inline(
        (unsigned char*) /*r_std_strTestIfFiltered.c_str()*/ p_ch ,
        /*(WORD) r_std_strTestIfFiltered.length()*/ strLen ,
        false // allow prefix match: e.g. "hello" is prefix of "hello1"
        );
    if( p_ntn
        //If a >string inside the trie< wholly matches or is a prefix of
        //the "string to test if filtered".
        && p_ntn->m_member == string_end
        )
      bIsNotFiltered = false;
    //if( //m_ofstream.good()
    return bIsNotFiltered;
#else
    return true;
#endif //#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
  }

  I_LogEntryOutputter * GetOutputHandler()
  {
    return m_p_outputhandler;
  }
  
  virtual unsigned Log(//ostream & ostr
//    const std::string & r_stdstrMessage,
    const LogFileEntry & logfileentry,
    enum LogLevel::MessageType messageType =
      LogLevel::info,
    const char * const prettyFunctionFormattedFunctionName = NULL
    ) const = 0;
//  //"virtual" in order to "OpenFile" call subclasses overwritten function
//  //if any.
  virtual bool Open(std::string & actualFilePath);
//  virtual bool OpenA( const std::string & r_stdstrFilePath, bool bRolling = false) ;
  inline unsigned OutputTimeStampEtc_Inline(
//    const std::string & r_stdstr,
    const LogFileEntry & logfileentry,
    enum LogLevel::MessageType messageType =
      LogLevel::info,
    const char * const prettyFunctionFormattedFunctionName = NULL
    ) const
  {
    if( m_p_log_formatter)
    {
//        std::stringstream std_str_stream;
      //m_ofstream << r_stdstr ;

//        outputLogFilePrefix(//* m_p_std_ofstream
//          std_str_stream);
//        static LogFileEntry s_logfileentry;
//      GetLogFilePrefix(//* m_p_std_ofstream
////          s_logfileentry
//        m_logfileentry);

//        m_p_log_formatter->WriteTimeStamp(std_str_stream);
//  ////        << "\n"
//  //        ;
//  //      //for writing UTF-8 data (else problems writing a char value < 0 ?!)
//  //       m_p_std_ofstream->write(r_stdstr.c_str(), r_stdstr.length() );
//  //      * m_p_std_ofstream << r_stdstr;
//        m_p_log_formatter->WriteMessage(r_stdstr);

//        s_logfileentry.p_std_strMessage = (std::string *) & r_stdstr;
//        m_p_log_formatter->WriteLogFileEntry(s_logfileentry, messageType);
//        if( //Fastest evaluable condition at first.
//            m_p_std_ofstream )
//        {
        m_p_log_formatter->WriteLogFileEntry(
          /* *m_p_logfileentry */ logfileentry,
          messageType,
          prettyFunctionFormattedFunctionName);
        return m_p_outputhandler->DoOutput();
//        }
//        else
//        {
//          m_logfileentry.p_std_strMessage = new std::string(r_stdstr);
////          m_std_vecLogMessage.push_back(m_logfileentry);
//          return 0;
//        }
    }
    return UINT_MAX - 1;
  }
  void RenameThreadSafe(std::string & c_r_std_strName)
  {
    m_filePath = c_r_std_strName;
    if(m_p_outputhandler)
    {
      GetActualFilePath(c_r_std_strName);
      m_p_std_ostream = m_p_outputhandler->GetStdOstream();
      if( m_p_log_formatter)
        m_p_log_formatter->SetStdOstream(m_p_std_ostream);
      m_p_outputhandler->RenameThreadSafe(c_r_std_strName);
    }
  }
  void SetFormatter(I_LogFormatter * p_logformatter);
  void SetLogLevel(const std::string & c_r_std_strLogLevel)
  {
    m_logLevel = LogLevel/*Logger*/::GetAsNumber(c_r_std_strLogLevel);
  }
  /** For outputting to a std::ostream or derived class
  * see http://www.cplusplus.com/forum/general/20792/
  * see http://www.learncpp.com/cpp-tutorial/93-overloading-the-io-operators/:
  */
  friend std::ostream & operator << (std::ostream & std_ostream,
    const FormattedLogEntryProcessor &
    ) //const
    ;
};

#endif /* FORMATTEDLOGENTRYPROCESSOR_HPP_ */
