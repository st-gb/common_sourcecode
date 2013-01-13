/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany
 * ("Trilobyte SE") 2010-at least 2012.
 * You are allowed to modify and use the source code from Trilobyte SE for free
 * if you are not making profit directly or indirectly with it or its adaption.
 * Else you may contact Trilobyte SE. */
/*
 * I_Thread.hpp
 *
 *  Created on: Jun 16, 2010
 *      Author: Stefan
 */

#ifndef I_THREAD_HPP_
#define I_THREAD_HPP_

typedef unsigned char BYTE ;
typedef unsigned long DWORD ;

//Same function signature as for Win32 thread procedures.
//DWORD (WINAPI *LPTHREAD_START_ROUTINE)(LPVOID);

#include "thread_function_calling_convention.h"

/** Meets the thread procedure's signature for Windows API's
 * ::CreateThread(...) */
typedef DWORD ( //__stdcall is important for Windows' ::CreateThread()
  THREAD_FUNCTION_CALLING_CONVENTION
  * pfnThreadFunc)( void * p ) ;

/** Base class for specific (Linux/ POSIX etc.) thread implementation */
class I_Thread
{
protected:
  BYTE m_byThreadType ;
public:
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
    maximum_priority
  };
//  //else "undefined reference to `vtable for I_Thread'"
//  I_Thread() {} ;
  /** For releasing ressources */
  virtual void Delete() {} ;
  virtual int GetThreadPriority() = 0;
  virtual bool IsRunning() = 0;//{ return false;};
//  virtual I_Thread( BYTE byThreadType ) = 0 ;
  virtual //static
    BYTE start(pfnThreadFunc, void * p_v, BYTE priority = default_priority) = 0 ;
  /** Blocking/ synchronous wait until the thread is terminated */
  virtual void * WaitForTermination() { return 0 ; }
//  virtual ~I_Thread() {} ;
} ;

#endif /* I_THREAD_HPP_ */
