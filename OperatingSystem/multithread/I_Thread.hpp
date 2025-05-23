/**(c) Stefan Gebauer(Computer Science Master from TU Berlin)
 * Created on: Jun 16, 2010(Berlin, Germany time zone)
 * @author: Stefan Gebauer(TU Berlin matriculation number 361095) */

///Include guard, see http://en.wikipedia.org/wiki/Include_guard :

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
/**Include guard supported by (nearly) all industry compilers:*/\
/**Bln=BerLiN: https://www.acronymfinder.com/Berlin-(Bln).html
 * cmn=CoMmoN: http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe: http://www.abbreviations.com/abbreviation/Source
 * OpSys=OPerating SYStem */\
 ! defined TU_Bln361095cmnSrc__OpSys__multithread__I_Thread_hpp
   #define TU_Bln361095cmnSrc__OpSys__multithread__I_Thread_hpp

#ifndef I_THREAD_HPP_
#define I_THREAD_HPP_

typedef unsigned char BYTE ;
typedef unsigned long DWORD ;

//Same function signature as for Win32 thread procedures.
//DWORD (WINAPI *LPTHREAD_START_ROUTINE)(LPVOID);

///C(++) standard library header files:
 #include <map>///class std::map
 #include <string>///class std::string

///Stefan Gebauer's(TU Berlin matric. number 361095) ~"cmnSrc" repository files:
 #include "thread_function_calling_convention.h"
 #include <OperatingSystem/multithread/nativeCriticalSectionType.hpp>
 #include <hardware/CPU/fastest_data_type.h>///TU_Bln361095::CPU::faststUint

/** Meets the thread procedure's signature for Windows API's
 * ::CreateThread(...) */
typedef DWORD ( //__stdcall is important for Windows' ::CreateThread()
  THREAD_FUNCTION_CALLING_CONVENTION
  * pfnThreadFunc)( void * p ) ;

/** Base class for specific (Linux/ POSIX etc.) thread implementation */
class I_Thread
{
  typedef nativeCriticalSection_type cs_type;
  static cs_type s_critical_section_type;
protected:
  BYTE m_byThreadType ;
public:
  typedef std::map<unsigned, std::string> threadNameMapType;
  static threadNameMapType s_threadNumber2Name;
  enum thread_type{
    detached ,
    joinable
  };
  enum thread_start
  {
    no_error = 0
    , error
  };
  enum priority
  {
    default_priority,
    maximum_priority,
    error_getting_priority
  };
//  //else "undefined reference to `vtable for I_Thread'"
//  I_Thread() {} ;
  /** For releasing ressources */
  virtual void Delete() {} ;
  virtual unsigned GetThreadID() { return 0; }
  virtual int GetThreadPriority() = 0;
  virtual bool IsRunning() = 0;//{ return false;};
  /** @brief should be inline because is called from logger.
   *  @return value is valid until the container element is changed.
   *    To be safe, get a copy of its dereferenced ("*") value after calling this
   *    function */
  //TODO malfunction after getting thread name if more than 1 thread?!
  static const std::string * const GetThreadName(const unsigned threadID)
  {
    //Enter the critical section to guard against changing the thread name
    //container at the same time.
    s_critical_section_type.Enter();
    I_Thread::threadNameMapType::const_iterator c_iter =
      I_Thread::s_threadNumber2Name.find(threadID);
    if( c_iter != I_Thread::s_threadNumber2Name.end() )
    {
      s_critical_section_type.Leave();
      return & (std::string &) c_iter->second;
    }
    else
    {
      s_critical_section_type.Leave();
      return NULL;
    }
  }
  static void SetCurrentThreadName(const char * const);
  static void SetThreadName(const char * const, unsigned threadID);
//  virtual I_Thread( BYTE byThreadType ) = 0 ;
  virtual //static
    TU_Bln361095::CPU::faststUint start(
      pfnThreadFunc,
      void * p_vpfnThreadFuncParam,
      /*BYTE*/ enum priority prio = default_priority) = 0 ;
  virtual //static
    BYTE start(
      pfnThreadFunc pfnthreadfunc,
      void * p_vThreadFuncParam,
      const char * /*const*/ threadName,
      /*BYTE*/ enum priority prio = default_priority);
    BYTE start(
      pfnThreadFunc pfnthreadfunc,
      void * p_vThreadFuncParam,
      /*BYTE*/ enum priority prio,
      const char * const threadName);
  /** Blocking/ synchronous wait from thread that calls this function until the
   * thread is terminated
   * \return value=waiting succeeded? */
  virtual void * WaitForTermination() const { return 0 ; }
//  virtual ~I_Thread() {} ;
} ;

#endif /* I_THREAD_HPP_ */
