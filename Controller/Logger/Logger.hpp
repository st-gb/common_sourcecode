#ifndef LOGGER_HPP
  #define LOGGER_HPP

  #include <fstream> //for class std::ofstream ;
  //#include <strstream> //for class std::ostrstream
  #include <set> //for class std::set
  #include <string> //for std::wstring
  //#include <sstream>
#ifndef COMPILE_FOR_CPUCONTROLLER_DYNLIB
  #include <wx/thread.h> //wxCriticalSection
#endif //#ifndef COMPILE_FOR_CPUCONTROLLER_DYNLIB

  #include <Controller/character_string/stdtstr.hpp> //for std::tstring
#ifndef COMPILE_FOR_CPUCONTROLLER_DYNLIB
  #include <data_structures/Trie.hpp>
#endif //#ifndef COMPILE_FOR_CPUCONTROLLER_DYNLIB

#ifdef _WINDOWS
  //Use "windows.h" for g++ because the case matters.
  #include <windows.h> //for SYSTEMTIME
//  #include <winbase.h> //for SYSTEMTIME
#endif

  #include <windef.h> //for WORD
  //class std::ofstream ;

  class Logger
  {
#ifdef _WINDOWS
    //Use member variable: so it does not need to be created on stack for
    //every call to "Log(...)".
    SYSTEMTIME systemtime ;
#endif
  public:
#ifndef COMPILE_FOR_CPUCONTROLLER_DYNLIB
    //Make public because accessed from preprocessor macro.
    wxCriticalSection m_wxcriticalsectionLogging ;
#endif
    enum log_class
    {
      sync = 0
    };
    std::set<WORD> m_stdsetLogClass ;
    std::set<std::string> m_stdsetstdstrExcludeFromLogging ;
    //std::ofstream m_ofstream ;
    std::ofstream * mp_ofstream ;
#ifndef COMPILE_FOR_CPUCONTROLLER_DYNLIB
    Trie m_trie ;
#endif //#ifndef COMPILE_FOR_CPUCONTROLLER_DYNLIB
    void AddExcludeFromLogging(const std::string & cr_stdstr ) ;
    Logger( //const std::set<std::string> & cr_stdsetstdstrExcludeFromLogging
      ) ;
    ~Logger() ;
    Logger( std::string & stdstrFilePath ) ;

    bool IsOpen() ;
    //void Log(//ostream & ostr
    //    std::ostrstream & r_ostrstream
    //    ) ;

    void Log(//ostream & ostr
        std::string & r_stdstr
        )
    {
      //  if(r_stdstr.end().)
    //Synchronization is not used in CPU controller logging.
    #ifndef COMPILE_FOR_CPUCONTROLLER_DYNLIB
      //Protect access to the trie: if 2 or more threads access the
      // trie then an invalid array index for a trie level might be used?!
      //If the outpur is _not_ synchronized and 2 or more threads are
      // logging concurrently: the output may be mixed like:
      // "22010.8.10 2010.99h:824.min 1051 19491msad24hread ID:tC8296ntCP51os
      //  ter getting DOM implementationt("
//      m_wxcriticalsectionLogging.Enter() ;
    #endif //#ifndef COMPILE_FOR_CPUCONTROLLER_DYNLIB

      if(
        //Fasted evaluatable condition.
        mp_ofstream &&
        //If NOT in the container.
      //Filtering is not used in CPU controller logging.
      #ifndef COMPILE_FOR_CPUCONTROLLER_DYNLIB
      //      m_stdsetstdstrExcludeFromLogging.find(r_stdstr) ==
      //      m_stdsetstdstrExcludeFromLogging.end()
        ! m_trie.exists_inline(
          (unsigned char*) r_stdstr.c_str() ,
          (WORD) r_stdstr.length( ) ,
          false // allow prefix match: e.g. "hello" is prefix of "hello1"
          )
      //  )
      //if( //m_ofstream.good()
      &&
    #endif //#ifndef COMPILE_FOR_CPUCONTROLLER_DYNLIB
        mp_ofstream->good()
        )
      {
      #ifdef _WINDOWS
    //    SYSTEMTIME systemtime ;
        //GetSystemTime(&systemtime);              // gets current time
        //gets the same time as the Windows clock.
    //    ::GetLocalTime( & systemtime );
        ::GetLocalTime( & systemtime );
      #else

      #endif
        //m_ofstream << r_stdstr ;
        *mp_ofstream
          #ifdef _WINDOWS
          << systemtime.wYear << "."
          << systemtime.wMonth << "."
          << systemtime.wDay << " "
          << systemtime.wHour << "h:"
          << systemtime.wMinute << "min "
          << systemtime.wSecond << "s "
          << systemtime.wMilliseconds << "ms"
          << " thread ID:" << ::GetCurrentThreadId()
          << ":"
          #else
          #endif
          << r_stdstr
          << "\n"
          ;
        //m_ofstream.flush() ;
        mp_ofstream->flush() ;
//        #ifndef COMPILE_FOR_CPUCONTROLLER_DYNLIB
//        m_wxcriticalsectionLogging.Leave() ;
//        #endif
        //TODO write into RAM for having 2 possibilties:
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
//      #ifndef COMPILE_FOR_CPUCONTROLLER_DYNLIB
      }
//#ifndef COMPILE_FOR_CPUCONTROLLER_DYNLIB
//      else
//        m_wxcriticalsectionLogging.Leave() ;
//#endif
#ifndef COMPILE_FOR_CPUCONTROLLER_DYNLIB
//      m_wxcriticalsectionLogging.Leave() ;
#endif

//      #endif //#ifndef COMPILE_FOR_CPUCONTROLLER_DYNLIB
    }
    void Log(//ostream & ostr
        std::string & r_stdstr
        , WORD wType
        ) ;
    void Log(//ostream & ostr
        char * p_ch
        ) ;
    #ifdef COMPILE_WITH_WSTRING
    //wide char version for output of Windows power scheme names etc.
    void LogW(//ostream & ostr
      std::wstring & r_stdstr
      ) ;
    #endif //#ifdef COMPILE_WITH_WSTRING
#ifndef COMPILE_FOR_CPUCONTROLLER_DYNLIB
    //void
    bool OpenFile( //std::string & r_stdstrFilePath
      std::tstring & r_stdtstrFilePath ) ;
#endif
    bool OpenFile2( std::string & r_stdstrFilePath ) ;

    void TruncateFileToZeroAndRewrite() ;
  };

#endif //LOGGER_HPP
