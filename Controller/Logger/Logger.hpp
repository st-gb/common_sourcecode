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
#endif //#ifndef COMPILE_LOGGER_MULTITHREAD_SAFE

  //for std::tstring
  #include <Controller/character_string/stdtstr.hpp>

//#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
//  //#include <data_structures/Trie/byteTrie/Trie.hpp> //class Trie
//  #include <data_structures/Trie/NodeTrie/NodeTrie.hpp> //class Trie
//#endif //#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT

  #include "log_file_prefix.hpp" // GetLogFilePrefix(LogFileEntry)
  #include <Controller/multithread/GetCurrentThreadNumber.hpp>
//  #include "HTMLlogFormatter.hpp"
//  #include "Formatter/I_LogFormatter.hpp" //class ILogFormatter::WriteLogFileEntry(...)
  #include "LogLevel.hpp" //namespace LogLevel::MessageType
  using namespace LogLevel;

  #include "LogFileEntry.hpp" //class LogFileEntry

  #include <windef.h> //for WORD
  //from http://stackoverflow.com/questions/3243454/what-is-the-linux-equivalent-to-maxdword
  #include <limits.h> //UINT_MAX

  //Forward decl. (faster than to #include a file)
  //class std::ofstream ;
//  class I_LogFormatter;

  #include "Appender/FormattedLogEntryProcessor.hpp"

  class Logger
  {
  private:
//    std::map<unsigned, std::string> m_threadNumber2Name;
//    LogWriter logwriter
    std::vector<FormattedLogEntryProcessor *> m_formattedLogEntryProcessors;
  public:
#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
  #ifdef _WIN32 //Built-in preprocessor macro for MSVC, MinGW (also for 64 bit)
    //Use member variable: so it does not need to be created on stack for
    //every call to "Log(...)".
    typedef //OperatingSystem::Windows::I_CriticalSection
      nativeCriticalSection_type CriticalSection_type;
  #else
  #endif
    //Make public because accessed from preprocessor macro.
    //wxCriticalSection m_critical_section_typeLogging ;
    CriticalSection_type m_critical_section_typeLogging ;
#endif
    /** Used for all FormattedLogEntryProcessors. */
    LogFileEntry m_logfileentry;
    enum LogLevel::MessageType m_logLevel;
    enum log_class
    {
      sync = 0
    };
//    std::set<WORD> m_stdsetLogClass ;
//    std::set<std::string> m_stdsetstdstrExcludeFromLogging ;
    //std::ofstream m_ofstream ;

//    std::basic_ofstream<WCHAR> * m_p_std_ofstream ;
  protected:

  public:
    Logger( //const std::set<std::string> & cr_stdsetstdstrExcludeFromLogging
      ) ;
    /** by "virtual": avoid warning: `class Logger' has virtual functions but
     * non-virtual destructor.  */
    virtual ~Logger() ;
    Logger( std::string & stdstrFilePath ) ;

#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
    void AddExcludeFromLogging(const std::string & cr_stdstr ) ;
//    void ExcludeMessageFromLogging(const std::string & cr_stdstr ) ;
    void ExcludeFunctionFromLogging(const std::string & cr_stdstr ) ;
#endif //#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT

    void AddFormattedLogEntryProcessor(
      FormattedLogEntryProcessor * p_formattedlogentryprocessor)
    {
      m_formattedLogEntryProcessors.push_back(p_formattedlogentryprocessor);
    }
    /*const*/ std::vector<FormattedLogEntryProcessor *> &
      GetFormattedLogEntryProcessors() //const
    {
      return m_formattedLogEntryProcessors;
    }
    enum MessageType GetLogLevel() { return m_logLevel; }

    //void Log(//ostream & ostr
    //    std::ostrstream & r_ostrstream
    //    ) ;

//    inline void OutputTimeStampEtc_Inline(
//        const std::vector<BYTE> & c_r_std_vec_by)
//    {
//      outputLogFilePrefix(* m_p_std_ofstream);
////      * m_p_std_ofstream << r_stdstr;
////      << "\n"
////      ;
//    }

    /*FORCEINLINE*/ inline
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
                    
    inline void PossiblyLeaveCritSec()
    {
      /** #define COMPILE_LOGGER_MULTITHREAD_SAFE if multiple threads may do a
       *  logging output simultaneously. */
#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
      m_critical_section_typeLogging.Leave() ;
#endif //#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE      
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

    /** Do not call this method thread-unsafe -> enter a critical section before
     * calling it */
    DWORD Log_inline(//ostream & ostr
      const std::string & r_stdstrMessage,
      enum LogLevel::MessageType messageType =
        LogLevel::info,
      const char * const prettyFunctionFormattedFunctionName = NULL
      )
    {
      //NOTE: because of multithreaded logging:
      //Must guard the m_logfileentry variable because else it might be
      //changed while reading (in the logging OutputHandlers when the function
      //is entered a second time) from it.
      PossiblyEnterCritSec();
      //Use local LogFileEntry variable because this function may be called by
      //multiple threads synchronously (if then using member variable this could
      //get corrupted data).
//      LogFileEntry logfileentry;
      GetLogFilePrefix(m_logfileentry
        //logfileentry
        );
      m_logfileentry //logfileentry
        .p_std_strMessage = (std::string *) & r_stdstrMessage;
      static std::vector<FormattedLogEntryProcessor *>::const_iterator
        c_iterFormattedLogEntryProcessors;
      c_iterFormattedLogEntryProcessors = m_formattedLogEntryProcessors.begin();
      static FormattedLogEntryProcessor * p_formattedlogentryprocessor;
#ifdef _DEBUG
      const int numFormattedLogEntryProcessors = m_formattedLogEntryProcessors.size();
#endif
      while( c_iterFormattedLogEntryProcessors !=
          m_formattedLogEntryProcessors.end() )
      { //TODO SIGSEGV here called from MainFrame::OnClose->mp_wxx86infoandcontrolapp->EndGetCPUcoreDataViaIPCthread() ;:
        //the pointer is invalid (value: 0x20) (because of multithreaded logging wout crit sec?!)
        p_formattedlogentryprocessor = ( * c_iterFormattedLogEntryProcessors);
        if( messageType >= p_formattedlogentryprocessor->m_logLevel )
          p_formattedlogentryprocessor->Log(
            m_logfileentry // logfileentry,
            , messageType
            , prettyFunctionFormattedFunctionName);
        ++ c_iterFormattedLogEntryProcessors;
      }
      PossiblyLeaveCritSec();
      return 0;
    }
#ifndef __ANDROID__
    void AddConsoleLogEntryWriter();
#endif //#ifndef __ANDROID__
    DWORD Log(//ostream & ostr
      const std::string & r_stdstrMessage,
      enum LogLevel::MessageType messageType =
        LogLevel::info,
      const char * const prettyFunctionFormattedFunctionName = NULL
      );

//    void Log(
//      const std::string & r_stdstrCodePosition,
//      const std::string & r_stdstrMessage,
//      enum LogLevel::MessageType messageType =
//          LogLevel::info
//      )
//    {
////      EnterCritSec();
//      if( //Fastest evaluable condition at first.
//          m_p_std_ofstream )
////      {
//        if(
//          #ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
//            IsNotFiltered(r_stdstrMessage)
//            &&
//          #endif //#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
//            m_p_std_ofstream->good()
//          )
//        {
//          OutputTimeStampEtc_Inline(r_stdstrMessage, messageType);
//          //m_ofstream.flush() ;
//  //        m_p_std_ofstream->flush() ;
//  //        POSSIBLY_LEAVE_CRIT_SEC
//  //        Ideas();
//        }
////      }
////      else
////        m_std_vecLog
////      POSSIBLY_LEAVE_CRIT_SEC
//    }

//    void Log(//ostream & ostr
//        std::string & r_stdstr
//        , WORD wType
//        ) ;
//    void Log(//std::ostream & ostr
//      std::ostringstream & ostr
//      )
//    {
//      Log(ostr.str() );
//    }
//    void Log(//ostream & ostr
//      const char * p_ch
//      ) ;
//    void Log(std::vector<unsigned char> )
//    {
//
//    }
    //FORCEINLINE
//    void Log_inline(
//      const std::string & r_stdstrMessage,
//      enum LogLevel::MessageType messageType =
//          LogLevel::info
//      )
//    {
//#ifdef COMPILE_WITH_LOG
//      PossiblyEnterCritSec();
//
//      Log(r_stdstrMessage, messageType);
//
//    #ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
//      m_critical_section_typeLogging.Leave() ;
//    #endif
//#endif
//    }
//    //FORCEINLINE
//    void Log_inline(
//      const std::string & r_stdstrCodePosition,
//      std::string & r_stdstrMessage,
//      enum LogLevel::MessageType messageType =
//          LogLevel::info
//      )
//    {
//#ifdef COMPILE_WITH_LOG
//      PossiblyEnterCritSec();
//
////      Log(r_stdstrCodePosition, r_stdstrMessage, messageType);
//#endif
//    }
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
    bool OpenFileA(
      std::string & r_std_strFilePath,
      const char * const format = "log4j",
      unsigned numEntries = 500,
      LogLevel::MessageType lvl = LogLevel::info);
//    void SetCurrentThreadName(const char * const name)
//    {
//      unsigned currentThreadNumber = OperatingSystem::GetCurrentThreadNumber();
//      m_threadNumber2Name.insert( std::make_pair(std::string(name),
//        currentThreadNumber) );
//    }

    /** @brief Sets formatter for all formatted log entry processors (classes
     * like "RollingFileOutput"). */
    void SetFormatter(I_LogFormatter * p_logformatter)
    {
      //Prevent concurrent writes while log formatter is exchanged.
      PossiblyEnterCritSec();
      std::vector<FormattedLogEntryProcessor *>::const_iterator
        c_iterFormattedLogEntryProcessors;
      c_iterFormattedLogEntryProcessors = m_formattedLogEntryProcessors.begin();
      FormattedLogEntryProcessor * p_formattedlogentryprocessor;
      //I_LogEntryOutputter * p_outputHandler;
      while( c_iterFormattedLogEntryProcessors !=
          m_formattedLogEntryProcessors.end() )
      {
        p_formattedlogentryprocessor = ( * c_iterFormattedLogEntryProcessors);
        p_formattedlogentryprocessor->SetFormatter(p_logformatter);
        ++ c_iterFormattedLogEntryProcessors;
      }
      PossiblyLeaveCritSec();
    }
    void SetLogLevel(const std::string & c_r_std_strLogLevel)
    {
      m_logLevel = LogLevel::GetAsNumber(c_r_std_strLogLevel);
    }
    /** @brief Truncate output size of all formatted log entry processors to 0.
     * name [...]"OutputSize"[...] and not [...]"FileSize" because not only
     * files may be an output target. */
    void TruncateOutputSizeToZero()
    {
      //Prevent concurrent writes while log output is truncated.
      PossiblyEnterCritSec();
      std::vector<FormattedLogEntryProcessor *>::const_iterator
        c_iterFormattedLogEntryProcessors;
      c_iterFormattedLogEntryProcessors = m_formattedLogEntryProcessors.begin();
      FormattedLogEntryProcessor * p_formattedlogentryprocessor;
      I_LogEntryOutputter * p_outputHandler;
      while( c_iterFormattedLogEntryProcessors !=
          m_formattedLogEntryProcessors.end() )
      {
        p_formattedlogentryprocessor = ( * c_iterFormattedLogEntryProcessors);
        p_outputHandler = p_formattedlogentryprocessor->GetOutputHandler();
        if( p_outputHandler )
          p_outputHandler->TruncateOutputSizeToZero();
        ++ c_iterFormattedLogEntryProcessors;
      }
      PossiblyLeaveCritSec();
    }
  };

#endif //LOGGER_HPP
