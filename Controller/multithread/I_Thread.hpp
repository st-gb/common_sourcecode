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

typedef DWORD ( //__stdcall is important for Windows' ::CreateThread()
  THREAD_FUNCTION_CALLING_CONVENTION
  * pfnThreadFunc)( void * p ) ;

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
//  //else "undefined reference to `vtable for I_Thread'"
//  I_Thread() {} ;
  virtual void Delete() {} ;
//  virtual I_Thread( BYTE byThreadType ) = 0 ;
  virtual //static
    BYTE start(pfnThreadFunc, void * p_v ) = 0 ;
  virtual void * WaitForTermination() { return 0 ; }
//  virtual ~I_Thread() {} ;
} ;

#endif /* I_THREAD_HPP_ */
