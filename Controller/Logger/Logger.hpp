/**(c)from 2010 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
 * created ca. 19 Aug 2010 18:37
 * @author Stefan Gebauer(TU Berlin matriculation number 361095)*/

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
/**Include guard supported by (nearly) all compilers:*/\
/**Bln=BerLiN: http://www.acronymfinder.com/Berlin-(Bln).html
 * cmn=CoMmoN: http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe: http://www.abbreviations.com/abbreviation/Source */\
 !defined TU_Bln361095cmnSrc_Logger_Logger_hpp
  #define TU_Bln361095cmnSrc_Logger_Logger_hpp

//  #define COMPILE_LOGGER_MULTITHREAD_SAFE
//  #define COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
  #define COMPILE_LOGGER_WITH_TSTRING_SUPPORT

///C(++) standard library header files:
  #include <fstream> //for class std::ofstream ;
  //#include <strstream> //for class std::ostrstream
  #include <set> //for class std::set
  #include <string> //for std::wstring
  #include <vector> //for std::vector<BYTE>
  //#include <sstream>

#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
  //#include <wx/thread.h> //wxCriticalSection
///Stefan Gebauer's(TU Berlin mat.#361095)~"common_sourcecode" repository files:
//  #include <Windows/multithread/I_CriticalSection.hpp>
  #include <OperatingSystem/multithread/nativeCriticalSectionType.hpp>
#endif //#ifndef COMPILE_LOGGER_MULTITHREAD_SAFE

///Stefan Gebauer's(TU Berlin mat.#361095) ~"common_sourcecode"repository files:
 ///TU_Bln361095disableUnusedVarWarn,TU_Bln361095enableUnusedVarWarn
 #include <compiler/C,C++/enableAndDisableWarn.h>
 #include <dataType/charStr/stdtstr.hpp>///typedef std::tstring
 ///TU_Bln361095MicroSoftWindows
 #include <OperatingSystem/Windows/MicrosoftWindows.h>

//#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
//  //#include <data_structures/Trie/byteTrie/Trie.hpp> //class Trie
//  #include <data_structures/Trie/NodeTrie/NodeTrie.hpp> //class Trie
//#endif //#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT

///Stefan Gebauer's(TU Berlin mat.#361095) ~"common_sourcecode"repository files:
  #include "log_file_prefix.hpp" // GetLogFilePrefix(LogFileEntry)
  #include <OperatingSystem/multithread/GetCurrentThreadNumber.hpp>
//  #include "HTMLlogFormatter.hpp"
//  #include "Formatter/I_LogFormatter.hpp" //class ILogFormatter::WriteLogFileEntry(...)
  //#include "LogLevel.hpp" //namespace LogLevel::MessageType
  //using namespace LogLevel;
  #include "LogFileEntry.hpp" //class LogFileEntry

#ifdef _MSC_VER///MicroSoft Compiler
/**Microsoft Visual Studio has compile errors when including <windef.h>
 * directly. So include <windows.h> for DWORD*/
  #include <windows.h>///for DWORD
#else
  #include <windef.h>///for DWORD
#endif
//from http://stackoverflow.com/questions/3243454/what-is-the-linux-equivalent-to-maxdword
  #include <limits.h> //UINT_MAX

  //Forward decl. (faster than to #include a file)
  //class std::ofstream ;
//  class I_LogFormatter;

///Stefan Gebauer's(TU Berlin matric. number 361095) ~"cmnSrc" repository files:
  #include "Appender/FormattedLogEntryProcessor.hpp"
  #include "LogLevel.hpp" //namespace LogLevel::MessageType

  //#define ASCII_CODE_FOR_LOW_Z_PLUS1 0x7B // 'z' + 1

  class Logger
    /** For log level string to number mapping: mapping needs to be . */
    : public LogLevel
  {
  private:
//    std::map<unsigned, std::string> m_threadNumber2Name;
//    LogWriter logwriter
    /*volatile*/ std::vector<FormattedLogEntryProcessor *> m_formattedLogEntryProcessors;
  public:
#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
  #ifdef TU_Bln361095MicrosoftWindows
    typedef //OperatingSystem::Windows::I_CriticalSection
      nativeCriticalSection_type CriticalSection_type;
  #else
  #endif
    /**Use member variable: so it does not need to be created on stack for
     * every call to "Log(...)".
     * Make public because accessed from preprocessor macro.*/
    //wxCriticalSection m_critical_section_typeLogging ;
    nativeCriticalSection_type m_critical_section_typeLogging ;
#endif
    /** Used for all FormattedLogEntryProcessors. */
    LogFileEntry m_logfileentry;
    /** Overall log level (for all in m_formattedLogEntryProcessors) : 
     *  "pre-filters" log messages */
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
//    static NodeTrie<BYTE> s_nodetrieLogLevelStringToNumber(
//      ASCII_CODE_FOR_LOW_Z_PLUS1,
//      LogLevel::beyondLastLogMessageType);
    //#include "LogLevel.hpp" //namespace LogLevel::MessageType
//    #include "LogLevel_GetAsNumber.hpp" //namespace LogLevel::MessageType
  
    Logger( //const std::set<std::string> & cr_stdsetstdstrExcludeFromLogging
      ) ;
    /** by "virtual": avoid warning: `class Logger' has virtual functions but
     * non-virtual destructor.  */
    virtual ~Logger() ;
    Logger( std::string & stdstrFilePath ) ;

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

#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT
    void AddExcludeFromLogging(const std::string & cr_stdstr ) ;
//    void ExcludeMessageFromLogging(const std::string & cr_stdstr ) ;
    void ExcludeFunctionFromLogging(const std::string & cr_stdstr ) ;
#endif //#ifdef COMPILE_LOGGER_WITH_STRING_FILTER_SUPPORT

    void AddFormattedLogEntryProcessor(
      FormattedLogEntryProcessor * p_formattedlogentryprocessor)
    {
      PossiblyEnterCritSec();
//      SetToLowestLogLevelOfAll();
      fastestSignedDataType logLevel = p_formattedlogentryprocessor->GetLogLevel();
      /** The lower the level the more messages are not pre-filtered.
       *  -> less performant. */
      if( logLevel <  m_logLevel)
        //TODO set thread-safe via atomic function ?
        m_logLevel = (LogLevel::MessageType) logLevel;
      m_formattedLogEntryProcessors.push_back(p_formattedlogentryprocessor);
      PossiblyLeaveCritSec();
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
//      PossiblyEnterCritSec();

      //Use local LogFileEntry variable because this function may be called by
      //multiple threads synchronously (if then using member variable this could
      //get corrupted data).
//      LogFileEntry logfileentry;
      GetLogFilePrefix(m_logfileentry
        //logfileentry
        );
      m_logfileentry //logfileentry
        .p_std_strMessage = (std::string *) & r_stdstrMessage;
      //"static" seemed to cause a SIGSEV error below
      /*volatile static*/ std::vector<FormattedLogEntryProcessor *>::const_iterator
        c_iterFormattedLogEntryProcessors;
      c_iterFormattedLogEntryProcessors = m_formattedLogEntryProcessors.begin();
      static FormattedLogEntryProcessor * p_formattedlogentryprocessor;
#ifdef _DEBUG
      TU_Bln361095disableUnusedVarWarn
      /**Use same data type as "std::vector::size()" to avoid MicroSoft
       * Visual C compiler warning "C4267" (data loss possible).*/
      const std::vector<FormattedLogEntryProcessor>::size_type
        numFormattedLogEntryProcessors = m_formattedLogEntryProcessors.size();
      TU_Bln361095enableUnusedVarWarn
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
//      PossiblyLeaveCritSec();
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
  ///@brief opens a file with 1 byte/8 bit ASCII file name
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

    void Remove(FormattedLogEntryProcessor * p_formattedLogEntryProcessor)
    {
      //Prevent concurrent writes while log formatter is exchanged.
      PossiblyEnterCritSec();
      //TODO thread safety
      std::vector<FormattedLogEntryProcessor *>::iterator iter =
//        m_formattedLogEntryProcessors.find(p_formattedlogentryprocessor);
        m_formattedLogEntryProcessors.begin();
      while(iter != m_formattedLogEntryProcessors.end() )
      {
        if( * iter == p_formattedLogEntryProcessor )
        {
          m_formattedLogEntryProcessors.erase(iter);
          break;
        }
        ++ iter;
      }
      PossiblyLeaveCritSec();
    }

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
  void SetLogLevel(const std::string & c_r_std_strLogLevel){
    m_logLevel = LogLevel::GetAsNumber(c_r_std_strLogLevel);
  }
  void SetLogLevel(const MessageType & messageType){
    m_logLevel = messageType;
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

#endif///include guard
