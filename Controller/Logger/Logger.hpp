/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany
 * ("Trilobyte SE") 2010-at least 2012.
 * You are allowed to modify and use the source code from Trilobyte SE for free
 * if you are not making profit directly or indirectly with it or its adaption.
 * Else you may contact Trilobyte SE. */
#ifndef LOGGER_HPP
  #define LOGGER_HPP

//  #define COMPILE_LOGGER_MULTITHREAD_SAFE
//  #define COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
  #define COMPILE_LOGGER_WITH_TSTRING_SUPPORT

  #include <fstream> //for class std::ofstream ;
  //#include <strstream> //for class std::ostrstream
  #include <set> //for class std::set
  #include <string> //for std::wstring
  #include <vector> //for std::vector<BYTE>
  //#include <sstream>

#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
  //#include <wx/thread.h> //wxCriticalSection
//  #include <Windows/multithread/I_CriticalSection.hpp>
  #include <Controller/multithread/nativeCriticalSectionType.hpp>
#endif //#ifndef COMPILE_FOR_CPUCONTROLLER_DYNLIB

  //for std::tstring
  #include <Controller/character_string/stdtstr.hpp>

#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
  //#include <data_structures/Trie/byteTrie/Trie.hpp> //class Trie
  #include <data_structures/Trie/NodeTrie/NodeTrie.hpp> //class Trie
#endif //#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT

  #include "log_file_prefix.hpp"
//  #include "HTMLlogFormatter.hpp"
  #include "ILogFormatter.hpp" //class ILogFormatter::WriteLogFileEntry(...)
  #include "LogLevel.hpp" //namespace LogLevel::MessageType
  using namespace LogLevel;

  #include "LogFileEntry.hpp" //class LogFileEntry

  #include <windef.h> //for WORD
  //from http://stackoverflow.com/questions/3243454/what-is-the-linux-equivalent-to-maxdword
  #include <limits.h> //UINT_MAX

  //Forward decl. (faster than to #include a file)
  //class std::ofstream ;
//  class I_LogFormatter;

  class Logger
  {
  private:
//    LogWriter logwriter
  protected:
//    HTMLformatLogFileWriter * m_p_log_writer;
    I_LogFormatter * m_p_log_formatter;
  public:
    enum LogLevel::MessageType m_logLevel;
    LogFileEntry m_logfileentry;
#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
  #ifdef _WIN32 //Built-in preprocessor macro for MSVC, MinGW (also for 64 bit)
    //Use member variable: so it does not need to be created on stack for
    //every call to "Log(...)".
    typedef //OperatingSystem::Windows::I_CriticalSection
      nativeCriticalSection CriticalSection_type;
  #else
  #endif
    //Make public because accessed from preprocessor macro.
    //wxCriticalSection m_critical_section_typeLogging ;
    CriticalSection_type m_critical_section_typeLogging ;
#endif
    std::string m_std_strLogFilePath;
    enum log_class
    {
      sync = 0
    };
    enum TrieNodeMemberValue
    {
      string_end = 1
    };
//    std::set<WORD> m_stdsetLogClass ;
//    std::set<std::string> m_stdsetstdstrExcludeFromLogging ;
    //std::ofstream m_ofstream ;
  private:
    std::ofstream * m_p_std_ofstream ;
//    std::basic_ofstream<WCHAR> * m_p_std_ofstream ;
  protected:
    std::ostream * m_p_std_ostream ;
#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
    //Trie m_trie ;
    NodeTrie<BYTE> m_trie ;
  public:
    NodeTrie<BYTE> GetTrie() { return m_trie; }
#endif //#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT

  public:
#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
    void AddExcludeFromLogging(const std::string & cr_stdstr ) ;
#endif //#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
    Logger( //const std::set<std::string> & cr_stdsetstdstrExcludeFromLogging
      ) ;
    /** by "virtual": avoid warning: `class Logger' has virtual functions but
     * non-virtual destructor.  */
    virtual ~Logger() ;
    Logger( std::string & stdstrFilePath ) ;

    I_LogFormatter * CreateTextFormatter()
    {
#ifdef _WIN32
      /** Windows can resolve times to milliseconds with GetLocalTime(...),
       * 100 ms with GetSystemTimeAsFileTime(...), so sesolution until "ms" is
       * ensured */
      std::string std_str =
        "%year%.%month%.%day%&nbsp;%hour%:%minute%:%second%s%millisecond%ms";
#endif
#ifdef __linux__
      /** Linux can resolve times to microiseconds with ::gettimeofday(...)*/
      std::string std_str =
        "%year%.%month%.%day% %hour%:%minute%:%second%s%millisecond%ms"
        "%microsecond%us";
#endif
      return CreateFormatter("", std_str
        );
    }
    I_LogFormatter * CreateFormatter(//BYTE type = 1
      //const std::string & std_strType //= std::string("html")
      const char * c_p_chType = "html"
      ,const std::string & std_strLogTimeFormatString =
        "%year%.%month%.%day%&nbsp;%hour%:%minute%:%second%s%millisecond%ms"
      //const char * c_p_chLogTimeFormatString
      );
    I_LogFormatter * GetFormatter() { return m_p_log_formatter; }
    enum MessageType GetLogLevel() { return m_logLevel; }

    //"virtual" because: allow polymorphism: call function of the actual type
    // (may be a direct or indirect subclass of this class).
    virtual std::ostream & GetStdOstream() const { return * m_p_std_ofstream; }
    //"virtual" because: allow polymorphism: call function of the actual type
    // (may be a direct or indirect subclass of this class).
    virtual bool IsOpen() ;
    //void Log(//ostream & ostr
    //    std::ostrstream & r_ostrstream
    //    ) ;

    inline void OutputTimeStampEtc_Inline(
        const std::vector<BYTE> & c_r_std_vec_by)
    {
      outputLogFilePrefix(* m_p_std_ofstream);
//      * m_p_std_ofstream << r_stdstr;
//      << "\n"
//      ;
    }

    inline DWORD OutputTimeStampEtc_Inline(
      const std::string & r_stdstr,
      enum LogLevel::MessageType messageType =
        LogLevel::info,
      const char * const prettyFunctionFormattedFunctionName = NULL
      )
    {
      if( m_p_log_formatter)
      {
//        std::stringstream std_str_stream;
        //m_ofstream << r_stdstr ;

//        outputLogFilePrefix(//* m_p_std_ofstream
//          std_str_stream);
//        static LogFileEntry s_logfileentry;
        GetLogFilePrefix(//* m_p_std_ofstream
//          s_logfileentry
          m_logfileentry);

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
          m_logfileentry.p_std_strMessage = (std::string *) & r_stdstr;
          m_p_log_formatter->WriteLogFileEntry(m_logfileentry, messageType,
            prettyFunctionFormattedFunctionName);
          return WriteToFile();
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

    //FORCEINLINE
    void PossiblyEnterCritSec()
    {
#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
  //Protect access to the trie: if 2 or more threads access the
  // trie then an invalid array index for a trie level might be used?!
  //If the output is _not_ synchronized and 2 or more threads are
  // logging concurrently: the output may be mixed like:
  // "22010.8.10 2010.99h:824.min 1051 19491msad24hread ID:tC8296ntCP51os
  //  ter getting DOM implementationt("
      m_critical_section_typeLogging.Enter() ;
#endif //#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
    }

    inline bool IsNotFiltered(const std::string & r_std_strTestIfFiltered)
    {
#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
      bool bIsNotFiltered = true;
    //      m_stdsetstdstrExcludeFromLogging.find(r_stdstr) ==
    //      m_stdsetstdstrExcludeFromLogging.end()
      NodeTrieNode<BYTE> * p_ntn =
        //If NOT in the container.
        m_trie.//exists_inline(
          contains_inline(
          (unsigned char*) r_std_strTestIfFiltered.c_str() ,
          (WORD) r_std_strTestIfFiltered.length( ) ,
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

    inline void Ideas()
    {
      //TODO write into RAM for having 2 possibilities:
      //-truncate the log file to zero for every startup
      //-append to log file at every startup

      //->Write into RAM until the config file that determines which of these
      //2 possibilities to use is completely read.
      //If the config says: always append: simply delete the RAM buffer.
      //If the config says: always truncate:
      // 1. truncate the log file to zero
      // 2. write the RAM buffer contents ( that are the same as in
      //   log file written from startup till then)
      // 3. delete the RAM buffer.
      //buffer.add( ofstream.str() ) ;
    }

#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
  #define POSSIBLY_LEAVE_CRIT_SEC //   m_critical_section_typeLogging.Leave() ;
#else
  #define POSSIBLY_LEAVE_CRIT_SEC
#endif

    DWORD Log(//ostream & ostr
      const std::string & r_stdstrMessage,
      enum LogLevel::MessageType messageType =
        LogLevel::info,
      const char * const prettyFunctionFormattedFunctionName = NULL
      )
    {
//      EnterCritSec();
      if( //Fastest evaluable condition at first.
        //m_p_std_ofstream &&
          m_p_std_ostream
        )
      {
        if(
        #ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
          //&&
          IsNotFiltered(r_stdstrMessage)
           &&
        #endif //#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
//          m_p_std_ofstream->good()
          m_p_std_ostream->good()
          )
        {
          //TODO make rolling log files possible
//          if( m_bRolling && m_numLogEntries > m_maxNumLogEntries )
//
//          if(m_numFiles > 1)
//          {
//            TruncateFileSizeToZero();
//          }
          return OutputTimeStampEtc_Inline(r_stdstrMessage, messageType,
            prettyFunctionFormattedFunctionName);
          //m_ofstream.flush() ;
  //        POSSIBLY_LEAVE_CRIT_SEC
  //        Ideas();
        }
      }
//      else
//        m_std_vecLogMessage.push_back( LogFileEntry() )
//#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
//      else
//        m_critical_section_typeLogging.Leave() ;
//#endif
//      POSSIBLY_LEAVE_CRIT_SEC
      return UINT_MAX;
    }
    void Log(
      const std::string & r_stdstrCodePosition,
      const std::string & r_stdstrMessage,
      enum LogLevel::MessageType messageType =
          LogLevel::info
      )
    {
//      EnterCritSec();
      if( //Fastest evaluable condition at first.
          m_p_std_ofstream )
//      {
        if(
          #ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
            IsNotFiltered(r_stdstrMessage)
            &&
          #endif //#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
            m_p_std_ofstream->good()
          )
        {
          OutputTimeStampEtc_Inline(r_stdstrMessage, messageType);
          //m_ofstream.flush() ;
  //        m_p_std_ofstream->flush() ;
  //        POSSIBLY_LEAVE_CRIT_SEC
  //        Ideas();
        }
//      }
//      else
//        m_std_vecLog
//      POSSIBLY_LEAVE_CRIT_SEC
    }

//    void Log(//ostream & ostr
//        std::string & r_stdstr
//        , WORD wType
//        ) ;
    void Log(//std::ostream & ostr
      std::ostringstream & ostr
      )
    {
      Log(ostr.str() );
    }
    void Log(//ostream & ostr
      const char * p_ch
      ) ;
//    void Log(std::vector<unsigned char> )
//    {
//
//    }
    //FORCEINLINE
    void Log_inline(
      const std::string & r_stdstrMessage,
      enum LogLevel::MessageType messageType =
          LogLevel::info
      )
    {
#ifdef COMPILE_WITH_LOG
      PossiblyEnterCritSec();

      Log(r_stdstrMessage, messageType);

    #ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
      m_critical_section_typeLogging.Leave() ;
    #endif
#endif
    }
    //FORCEINLINE
    void Log_inline(
      const std::string & r_stdstrCodePosition,
      std::string & r_stdstrMessage,
      enum LogLevel::MessageType messageType =
          LogLevel::info
      )
    {
#ifdef COMPILE_WITH_LOG
      PossiblyEnterCritSec();

//      Log(r_stdstrCodePosition, r_stdstrMessage, messageType);
#endif
    }
    #ifdef COMPILE_WITH_WSTRING
    //wide char version for output of Windows power scheme names etc.
    void LogW(//ostream & ostr
      std::wstring & r_stdstr
      ) ;
    #endif //#ifdef COMPILE_WITH_WSTRING
#ifdef COMPILE_LOGGER_WITH_TSTRING_SUPPORT
    //void
    bool OpenFile( //std::string & r_stdstrFilePath
      std::tstring & r_stdtstrFilePath ) ;
#endif //COMPILE_LOGGER_WITH_TSTRING_SUPPORT
    //"virtual" in order to "OpenFile" call subclasses overwritten function
    //if any.
    virtual bool OpenFileA( const std::string & r_stdstrFilePath, bool bRolling = false) ;
    virtual bool SetStdOstream(const std::string & c_r_stdstrFilePath);
    void SetFormatter(I_LogFormatter * p_logformatter)
    {
      if( m_p_log_formatter )
        delete m_p_log_formatter;
      m_p_log_formatter = p_logformatter;
    }
    void SetLogLevel(const std::string & c_r_std_strLogLevel)
    {
      m_logLevel = LogLevel::GetAsNumber(c_r_std_strLogLevel);
    }
    int RenameFile(const std::string & cr_std_strFilePath)
    {
      return RenameFileThreadSafe(cr_std_strFilePath);
    }
    int RenameFileThreadSafe(const std::string & cr_std_strFilePath);
    void TruncateFileToZeroAndRewrite() ;

    //"virtual" because: allow polymorphism
    virtual int RenameFileThreadUnsafe(const std::string & r_stdstrFilePath);
    //"virtual" because: allow polymorphism: call subclasses' function
    virtual void TruncateFileSizeToZero()
    {
#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
      //Sync with other code accessing the ofstream.
      m_critical_section_typeLogging.Enter();
#endif //#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
      if( m_p_std_ofstream )
      {
        m_p_std_ofstream->close();
        m_p_std_ofstream->open( m_std_strLogFilePath.c_str(), std::ios_base::trunc);
      }
#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
      m_critical_section_typeLogging.Leave();
#endif //#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
    }
    /** "virtual" because: allow polymorphism: call function of the actual type
    * (may be a direct or indirect subclass of this class).
    * @return 0: success  */
    virtual DWORD WriteToFile() { m_p_std_ofstream->flush(); return 0;}
  };

#endif //LOGGER_HPP
