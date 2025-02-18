/**(c) Stefan Gebauer(Computer Science Master from TU Berlin)
 * Created on: Jul 15, 2010(Berlin, Germany time zone)
 * @author: Stefan Gebauer(TU Berlin matriculation number 361095)*/

#ifndef TU_Bln361095cmnSrc__Logger__Log_preprocessor_macros_h
#define TU_Bln361095cmnSrc__Logger__Log_preprocessor_macros_h

///Stefan Gebauer's(TU Berlin matric. number 361095) ~"cmnSrc" repository files:
#ifndef _DEBUG
  #include "no_op_debug_output_macros.h"
#endif

#include <compiler/C,C++/currFuncSig.h>///TU_Bln361095progLangC_andCppCurrFnSig

//MinGW can't use wide stream (at least low versions of MinGW)
#ifndef __MINGW32__
  #define USE_STD_WCOUT
#endif

    #if defined(TU_Bln361095useOwnLogger)
      #ifndef TU_Bln361095buildWithLogging
        #define TU_Bln361095buildWithLogging
      #endif
    #endif

//  //Keep away the dependency on Logger class for dyn libs.
//  #if ! defined(COMPILE_LOGGER_MULTITHREAD_SAFE) //&& !defined(_DEBUG)
  //  #define LOG(...) /* ->empty/ no instructions*/
  //  #else
    #if defined( _DEBUG) //only debug DLLs should log
      #define COMPILE_WITH_DEBUG
    #endif
//  #else //#if !defined(COMPILE_LOGGER_MULTITHREAD_SAFE) && !defined(_DEBUG)
//    //Even release version of the service / GUI should output to the log file.
////    #define COMPILE_WITH_LOG
//    #if defined(_DEBUG)
//      #define COMPILE_WITH_DEBUG
//    #endif
//  #endif//#if !defined(COMPILE_LOGGER_MULTITHREAD_SAFE) && !defined(_DEBUG)

  #if defined(_DEBUG) //&& defined(USE_STD_WCOUT)
    #include <iostream> //for std::cout
    //this macro may NOT be called like the other one with "..."/ "__VA_ARGS__",
    //else many errors
    #define DEBUG_COUT(coutArgs)  {std::cout << coutArgs ; std::cout.flush(); }
    #define DEBUG_COUTN(coutArgs) { std::cout << coutArgs << "\n" ; \
      std::cout.flush(); }
    #ifdef USE_STD_WCOUT
      #define DEBUG_WCOUTN(coutArgs) { std::wcout << coutArgs << L"\n" ; \
        std::cout.flush(); }
    #else
      #define DEBUG_WCOUTN(coutArgs) ;//->empty;block can be used after"if"/"else"
    #endif
    //MinGW is able to use wprintf() but not std::wcout()
    #define DEBUG_WPRINTFN(...) { wprintf(__VA_ARGS__) ; wprintf(L"\n"); \
      fflush(stdout) ; }
  #else //#ifdef _DEBUG
    //Following macros: because of ";": block can be used after "if"/"else"
    #define DEBUG_COUT(coutArgs) ;/*empty;block can be used after "if"/"else"*/
    #define DEBUG_COUTN(coutArgs) ;/*empty; can be used after "if"/"else"*/
    #define DEBUG_WCOUTN(coutArgs) ;//->empty;block can be used after"if"/"else"
    #define DEBUG_WPRINTFN(...) ;//->empty; block can be used after "if"/"else"
//    #define DEBUG_SPRINTF(...) { } /* block can be used for "if"/"else"*/
//    #define DEBUGWN_WSPRINTF(...) { } /* block can be used after "if"/"else"*/
  #endif //#ifdef _DEBUG

//May be useful for finding logging errors: if the/ a global Logger variable
//has already been destroyed this leads/ may lead to program crashs.
#ifdef LOG_LOGGER_OUTPUT_TO_STDOUT_BEFORE
  #if LOGGING_CHARACTER_TYPE_ID == 0
    #define POSSIBLY_LOG_TO_STDOUT(coutArgs) \
      { /*std::wcout << coutArgs ; std::wcout.flush();*/ }
  #else //#if LOGGING_CHARACTER_TYPE_ID == 0
    #define POSSIBLY_LOG_TO_STDOUT(coutArgs) \
      { std::cout << coutArgs ; std::cout.flush(); }
  #endif //#if LOGGING_CHARACTER_TYPE_ID == 0
#else //#ifdef LOG_LOGGER_OUTPUT_TO_STDOUT_BEFORE
  #define POSSIBLY_LOG_TO_STDOUT(coutArgs) ; /* ->empty; block can be used
    after"if"/"else" */
#endif //#ifdef LOG_LOGGER_OUTPUT_TO_STDOUT_BEFORE

  //#include <iostream> //for std::cout
  #if defined( LOGGING_CHARACTER_TYPE_ID) && LOGGING_CHARACTER_TYPE_ID == 0
    #define WRITE_TO_STD_OUT_AND_FLUSH(to_ostream) \
      {       \
      css::basic_stringstream<LOGGING_CHARACTER_TYPE> stringstream ; \
      stringstream << to_ostream; \
      std::wcout << stringstream.str() << std::endl ; std::wcout.flush(); }
  #else
    #define WRITE_TO_STD_OUT_AND_FLUSH(to_ostream) \
    { \
      css::basic_stringstream<LOGGING_CHARACTER_TYPE> stringstream ; \
      stringstream << to_ostream; \
      std::cout << stringstream.str() << std::endl ; std::cout.flush(); \
    }
  #endif //#if LOGGING_CHARACTER_TYPE_ID == 0

#ifdef TU_Bln361095buildWithLogging
///Stefan Gebauer's(TU Berlin matric. number 361095) ~"cmnSrc" repository files:
  #include "css_basic_stringstream.hpp" //class css::basic_stringstream

//  #define USE_OWN_LOGGER
  #ifdef TU_Bln361095useOwnLogger
    #ifdef _WIN32
//      #include <Windows/Logger/Logger.hpp> //for class Windows_API::Logger
//    //Should have the same type as in the difintion.
//    extern Windows_API::Logger g_logger ;
    #endif //#ifdef _WIN32
//#else
///Stefan Gebauer's(TU Berlin matric. number 361095) ~"cmnSrc" repository files:
    #include <Controller/Logger/Logger.hpp> //for class Logger
    #include <Controller/Logger/LogLevel.hpp> //for enum LogLevel::MessageType
//    //Should have the same type as in the difintion.
    extern Logger g_logger ;
//#endif
//    extern GLOBAL_LOGGER_FULLY_QUALIFIED_CLASS_NAME g_logger;
    #define OWN_LOGGER_LOG(stdstr) g_logger.Log( stdstr ) ;
    #include <Controller/character_string/getUTF8string.hpp>
    #include <vector> /*class std::vector*/
    #if defined(LOGGING_CHARACTER_TYPE_ID) && LOGGING_CHARACTER_TYPE_ID == 0
      #define OWN_LOGGER_LOG_LOGGER_NAME(logger_name, std_basic_string) \
        std::string std_strUTF8 = getUTF8string(std_basic_string); \
        logger_name.Log( std_strUTF8 ) ;
      #define OWN_LOGGER_LOG_LOGGER_NAME_TYPE(logger_name, std_basic_string, \
        messageType) \
        std::string std_strUTF8 = getUTF8string(std_basic_string); \
        logger_name.Log( std_strUTF8, messageType) ;
      #define OWN_LOGGER_LOG_LOGGER_NAME_FUNCNAME_TYPE(logger_name, \
        std_basic_string, messageType) \
        std::string std_strUTF8 = getUTF8string(std_basic_string); \
        logger_name.Log(std_strUTF8, messageType,\
          TU_Bln361095progLangC_andCppCurrFnSig);
    #else //#if defined(LOGGING_CHARACTER_TYPE_ID) && LOGGING_CHARACTER_TYPE_ID == 0
      #define OWN_LOGGER_LOG_LOGGER_NAME(logger_name, std_basic_string) \
        logger_name.Log( std_basic_string ) ;
      #define OWN_LOGGER_LOG_LOGGER_NAME_TYPE(logger_name, std_basic_string, \
        messageType) \
        logger_name.Log( std_basic_string, messageType) ;
      #define OWN_LOGGER_LOG_LOGGER_NAME_FUNCNAME_TYPE(logger_name, \
        std_basic_string, messageType) \
        logger_name.Log(std_basic_string, messageType,\
          TU_Bln361095progLangC_andCppCurrFnSig);
    #endif //#if defined(LOGGING_CHARACTER_TYPE_ID) && LOGGING_CHARACTER_TYPE_ID == 0
      /*std::vector<unsigned char> std_vec_by;
      getUTF8string(std_basic_string, std_vec_by);
      logger_name.Log(
        std_vec_by
        ) ;*/
    #ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
      #define OWN_LOGGER_LOG_ENTER_CRIT_SEC g_logger.m_critical_section_typeLogging.\
        Enter() ;
      #define OWN_LOGGER_LOG_LEAVE_CRIT_SEC g_logger.m_critical_section_typeLogging.\
        Leave();
      #define OWN_LOGGER_LOG_ENTER_CRIT_SEC_LOGGER_NAME(logger_name) logger_name.\
          m_critical_section_typeLogging.Enter() ;
      #define OWN_LOGGER_LOG_LEAVE_CRIT_SEC_LOGGER_NAME(logger_name) logger_name.\
          m_critical_section_typeLogging.Leave();
    #else //#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
      #define OWN_LOGGER_LOG_ENTER_CRIT_SEC
      #define OWN_LOGGER_LOG_LEAVE_CRIT_SEC
      #define OWN_LOGGER_LOG_ENTER_CRIT_SEC_LOGGER_NAME(logger_name) /* ->empty */
      #define OWN_LOGGER_LOG_LEAVE_CRIT_SEC_LOGGER_NAME(logger_name) /* ->empty */
    #endif //#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
  #endif //#ifdef USE_OWN_LOGGER
    #include <string>
    //LOGGING_CHARACTER_TYPE
    #include <preprocessor_macros/logging_preprocessor_macros_definitions.h>
    extern std::basic_string<LOGGING_CHARACTER_TYPE>
      g_std_basicstring_log_char_typeLog;
    //class Logger ;
    //#ifndef _MSC_VER //else compile errors with gcc
    #include <sstream> //for class std::stringstream
    //#endif
//#define USE_LOG4CPLUS
  #ifdef USE_LOG4CPLUS
    #include <log4cplus/loggingmacros.h> //for LOG4CPLUS_INFO(...)
//    //forward decl.
//    namespace log4cplus
//    {
//      class Logger ;
//    }
    #include <log4cplus/logger.h> //log4cplus::class Logger
    extern log4cplus::Logger log4cplus_logger ;
  #else //#ifdef USE_LOG4CPLUS
  //#define LOG4CPLUS_INFO(logger, logEvent) /* ->empty*/
  #endif //#ifdef USE_LOG4CPLUS
    #define MAKE_STRING_FROM_STRING_STREAM(string, to_ostream) { \
      css::basic_stringstream<LOGGING_CHARACTER_TYPE> stringstream ; \
      stringstream << to_ostream; \
      string = stringstream.str(); }
    //#include "log_logger_name_thread_safe.h"
    #define WRITE_INTO_STRING_STREAM(loggerName, to_ostream) { \
      /*std::basic_stringstream<LOGGING_CHARACTER_TYPE> stringstream ;*/ \
      css::basic_stringstream<LOGGING_CHARACTER_TYPE> stringstream ; \
      stringstream << to_ostream; \
      /*/for g++ compiler:
      //Because I want to call Log( std::string & ) I have to create an object at
      //first*/ \
      /*std::string stdstr = strstream.str() ;*/ \
      /*Use critical section for thread sync. else mixed/ corrupted output
       *  like here: "SendCommandAndGetResponse end\0pe"
       */ \
      /*OWN_LOGGER_LOG_ENTER_CRIT_SEC_LOGGER_NAME(loggerName)*/ \
      g_std_basicstring_log_char_typeLog = stringstream.str() ; \
      /*g_logger->Log(to_ostream) ; */ \
      /*g_logger.Log( stdstr ) ;*/ \
      POSSIBLY_LOG_TO_STDOUT(g_std_basicstring_log_char_typeLog) \
      }

    //LOGxx macros: should log no matter whether release or debug.
    //Because under _Linux_ unloading a dynamic library with a global g_logger
    //caused the global g_logger (->same variable name) of the executable the
    //dyn lib was attached to call the
    //logger's destructor, provide a macro with different logger variable names.
    #define LOG_LOGGER_NAME_TYPE(logger, to_ostream, messageType) { \
      /* E.g. do not log "info" messages if level is "warning". */ \
      if( messageType >= logger.GetLogLevel() ) { \
        css::basic_stringstream<LOGGING_CHARACTER_TYPE> stringstream ; \
        stringstream << to_ostream; \
        /** Avoid writing to the global string that gets the
         *  css::basic_stringstream result by different threads.
         *  Else multiple same log messages may appear for different threads/
         *  function names. */ \
        OWN_LOGGER_LOG_ENTER_CRIT_SEC_LOGGER_NAME(logger) \
        /*logger.PossiblyEnterCritSec() \ */ \
        g_std_basicstring_log_char_typeLog = stringstream.str() ; \
        \
        OWN_LOGGER_LOG_LOGGER_NAME_FUNCNAME_TYPE( logger , \
          g_std_basicstring_log_char_typeLog, messageType) \
        /*OWN_LOGGER_LOG_LEAVE_CRIT_SEC_LOGGER_NAME(logger)*/ \
        OWN_LOGGER_LOG_LEAVE_CRIT_SEC_LOGGER_NAME(logger) \
      } \
      /*LOG4CPLUS_INFO(log4cplus_logger, g_std_basicstring_log_char_typeLog ); */\
      /*g_logger.Log("test ") ; */ }
    #define LOG_FUNCNAME_LOGGER_NAME_TYPE(logger, to_ostream, messageType) { \
      /* E.g. do not log "info" messages if level is "warning". */ \
      if( messageType >= logger.GetLogLevel() ) { \
        WRITE_INTO_STRING_STREAM(logger, to_ostream) \
        \
        OWN_LOGGER_LOG_LOGGER_NAME_TYPE( logger , \
          g_std_basicstring_log_char_typeLog, messageType) \
        OWN_LOGGER_LOG_LEAVE_CRIT_SEC_LOGGER_NAME(logger) \
      } \

    //LOGxx macros: should log no matter whether release or debug.
    //Because under _Linux_ unloading a dynamic library with a global g_logger
    //caused the global g_logger (->same variable name) of the executable the
    //dyn lib was attached to call the
    //logger's destructor, provide a macro with different logger variable names.
    #define LOG_LOGGER_NAME(logger, to_ostream) { \
      /* WRITE_INTO_STRING_STREAM(logger, to_ostream) \
      OWN_LOGGER_LOG_LOGGER_NAME( logger , \
        g_std_basicstring_log_char_typeLog ) \
      OWN_LOGGER_LOG_LEAVE_CRIT_SEC_LOGGER_NAME(logger) \
      LOG4CPLUS_INFO(log4cplus_logger, g_std_basicstring_log_char_typeLog );*/ \
      LOG_LOGGER_NAME_TYPE(logger, to_ostream, LogLevel::info) \
      /*g_logger.Log("test ") ; */ }
//    #endif
    #define LOG_FUNCNAME_LOGGER_NAME(logger, to_ostream) { \
      LOG_FUNCNAME_LOGGER_NAME_TYPE(logger, to_ostream, LogLevel::info) }

    #include "log_logger_name_thread_unsafe.h"

    #define LOG(to_ostream) LOG_LOGGER_NAME(g_logger,to_ostream)
    #define LOG_FUNCNAME(to_ostream) LOG_FUNCNAME_LOGGER_NAME(g_logger,to_ostream)
    #define LOG_TYPE(to_ostream, messageType) \
      LOG_LOGGER_NAME_TYPE(g_logger, to_ostream, messageType)
    //#ifdef COMPILE_WITH_LOG
//    //Allows easy transition from "printf"
/*    #define LOG_TYPE(to_ostream, type) { std::stringstream strstream ; \
//      strstream << to_ostream; \ */
//      /*/for g++ compiler:
//      //Because I want to call Log( std::string & ) I have to create an object at
//      //first*/ /*
//      std::string stdstr = strstream.str() ;\ */
//      /*g_logger->Log(to_ostream) ; */ /*
//      g_logger.Log( stdstr , type) ;
//      } */
    #define LOG_SPRINTF(...) { char arch_buffer[1000] ; \
      sprintf( arch_buffer, __VA_ARGS__ ) ; \
      std::string stdstr(arch_buffer) ; \
      stdstr += '\n' ; \
      g_logger.Log( stdstr ) ; \
      }
    //#define LOGN(to_ostream) LOG (to_ostream << "\n" )
    #define LOGN(to_ostream) LOG (to_ostream << "\n" /*std::endl*/)
    #define LOGN_TYPE(to_ostream, messageType) \
      LOG_TYPE (to_ostream << "\n" /*std::endl*/, messageType)
    #define LOGN_ERROR(to_ostream) LOGN_TYPE(to_ostream, LogLevel::error)
    #define LOGN_ERROR_AND_STD_ERR(to_ostream) \
      LOGN_TYPE(to_ostream, LogLevel::error) \
      std::cerr << to_ostream << std::endl;
    #define LOGN_INFO(to_ostream) LOGN_TYPE(to_ostream, LogLevel::info)
    #define LOGN_DEBUG(to_ostream) LOGN_TYPE(to_ostream, LogLevel::debug)
    #define LOGN_SUCCESS(to_ostream) LOGN_TYPE(to_ostream, LogLevel::success)
    #define LOGN_WARNING(to_ostream) LOGN_TYPE(to_ostream, LogLevel::warning )
    #define LOG_FUNC_NAME_LN(to_ostream) LOG( __F << to_ostream )
    #define LOGN_LOGGER_NAME(logger_name,to_ostream) \
      LOG_LOGGER_NAME(logger_name,to_ostream << "\n")
//    #define LOGN_TYPE(to_ostream, type) LOG_TYPE (to_ostream << "\n" , type)

    #ifdef __linux__ //Linux' swprintf(...) also needs the buffer size
      #define SWPRINTF(...) swprintf( arwch_buffer, 999, __VA_ARGS__ ) ;
    #else
      #define SWPRINTF(...) swprintf( arwch_buffer, __VA_ARGS__ ) ;
    #endif
    //Necessary for MinGW that does not know "std::wstringstream"
    #define LOGWN_WSPRINTF(...) { wchar_t arwch_buffer[1000] ; \
      /*swprintf( arwch_buffer, 999, __VA_ARGS__ ) ;*/ \
      SWPRINTF(__VA_ARGS__) \
      std::wstring stdwstr(arwch_buffer) ; \
      /*stdwstr += L'\n' ;*/ \
      std::string stdstr ( stdwstr.begin(), stdwstr.end() ); \
      stdstr += "\n"; \
      g_logger.Log( stdstr ) ; \
      }
    #if defined(__MINGW32__) //MinGW does not know std::wstringstream
      #define LOGW(to_ostream) /*empty->do not log*/
      #define LOGWN(to_ostream) /*empty->do not log*/
    #else
      #define LOGW(to_ostream) { std::wstringstream strstream ; \
        strstream << to_ostream; \
        /*/for g++ compiler:
        //Because I want to call Log( std::string & ) I have to create an object at
        //first*/ \
        std::wstring stdwstr = strstream.str() ;\
        std::string stdstr ( stdwstr.begin(), stdwstr.end() ) ;\
        /*g_logger->Log(to_ostream) ; */ \
        /*g_logger.LogW( stdwstr ) ; */ \
        g_logger.Log( stdstr ) ; \
        /*g_logger.Log("test ") ; */ }
      #define LOGWN(to_ostream) LOGW (to_ostream << L"\n" )
    #endif //#if defined(__MINGW32__)

    //for outputting wide strings also with MinGW:
/*    #define LOG_VIA_WSPRINTFN(...) { wchar_t ar_wch[1024] ; \ */
//      wwsprintfW(ar_wch,__VA_ARGS__) ;

    #include <iostream> //for std::cout
    //#endif
    #define WRITE_TO_LOG_FILE_AND_STDOUT_NEWLINE(to_ostream) { \
      /*LOG(to_ostream << std::endl; ); */ \
      LOGN( to_ostream ) ; \
      WRITE_TO_STD_OUT_AND_FLUSH(to_ostream) \
      }
#else //#ifdef COMPILE_WITH_LOG
  #define LOG(to_ostream) ; /* ";" for use in "else LOG(...)" -> "else ;" */
  #define LOG_SPRINTF(...) ; /**/
  #define LOGN(to_ostream) ;/*empty->do not log*/
  #define LOGN_ERROR(to_ostream) ; /*empty->do not log*/
  #define LOGN_SUCCESS(to_ostream) ; /*empty->do not log*/
  #define LOGN_DEBUG(to_ostream) ; /*empty->do not log*/
  #define LOGN_INFO(to_ostream) ; /*empty->do not log*/
  #define LOGN_WARNING(to_ostream) ; /*empty->do not log*/
  #define LOGW(to_ostream) ;/*empty->do not log*/
  #define LOGWN(to_ostream) ;/*empty->do not log*/
  #define LOGWN_WSPRINTF(...) ;/*empty->do not log*/
  #define WRITE_TO_LOG_FILE_AND_STDOUT_NEWLINE(...) ;/*empty->do not log*/
#endif //#ifdef COMPILE_WITH_LOG

//The DEBUGxx() macros that use / depend on LOGxx(), should be inside the
//   #ifdef COMPILE_WITH_LOG
#ifdef COMPILE_WITH_DEBUG
  #ifdef _DEBUG
    //#define DEBUG(...) { g_logger->Log(__VA_ARGS__) ; }
    //This macro should only be expanded to log outputs on debug versions.
    #define DEBUG(to_ostream) LOG(to_ostream)
    #define DEBUG_SPRINTF(...) LOG_SPRINTF(__VA_ARGS__)
    #define DEBUGN(to_ostream) LOGN(to_ostream)
    #define DEBUGN_LOGGER_NAME(logger_name,to_ostream) \
      LOGN_LOGGER_NAME(logger_name,to_ostream)
    #define DEBUGWN(to_ostream) LOGWN(to_ostream)
    #define DEBUGWN_WSPRINTF(...) LOGWN_WSPRINTF(__VA_ARGS__)
  #else //#ifdef _DEBUG
    #define DEBUGWN_WSPRINTF(...) { } /* block can be used for "if"/"else"*/
  #endif //#ifdef _DEBUG
  #define CPP_WRITE_TO_LOG_FILE_AND_STDOUT_NEWLINE(coutArgs) { \
    std::cout coutArgs ; std::cout.flush(); \
    g_ofstream coutArgs ; g_ofstream.flush(); }
  //Use C comment, else compiler warning: multi-line comment because of "\" at
  // line end.
  /*#define WRITE_TO_LOG_FILE_AND_STDOUT_NEWLINE(...) { \
  //  fprintf(fileDebug,__VA_ARGS__); fflush(fileDebug); \
  //  printf(__VA_ARGS__); fflush(stdout); } */
  //#ifndef _MSC_VER //else compile errors with gcc
#endif//#ifdef COMPILE_WITH_DEBUG

#ifdef VERBOSE_LOGGING
  #define LOGN_VERBOSE(to_ostream) LOGN(to_ostream)
#else
  #define LOGN_VERBOSE(to_ostream) /*empty->do not log*/
#endif

#endif///include guard
