/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */
/*
 * Thread.cpp
 *
 *  Created on: Jul 16, 2010
 *      Author: Stefan
 */

#include <Windows/multithread/Thread.hpp>
#include <windows.h> //::CreateThread(...)
#include <preprocessor_macros/logging_preprocessor_macros.h> //LOGN(...)

namespace Windows_API
{

  Thread::Thread(BYTE byThreadType)
    :
    m_byThreadType (byThreadType)
    , m_handleThread( NULL )
  {

  }

  int Thread::GetThreadPriority()
  {
    return ::GetThreadPriority(m_handleThread);
  }

  inline void Thread::PossiblyCloseThreadHandle()
  {
    LOGN_DEBUG( FULL_FUNC_NAME << " m_handleThread:" << m_handleThread)
    if( m_handleThread )
      ::CloseHandle(m_handleThread ) ;
  }

  BYTE Thread::start(pfnThreadFunc pfn_threadfunc, void * p_v, BYTE prio )
  {
    //Because "start" may be called for the same object multiple times.
    PossiblyCloseThreadHandle();
    m_handleThread =
      ::CreateThread(
        NULL,                   // default security attributes
        0,                      // use default stack size
        pfn_threadfunc,       // thread function name
        p_v ,// argument to thread function
        0,                      // use default creation flags
        & m_dwThreadId
        );   // returns the thread identifier
    if( m_handleThread )
    {
#ifdef _DEBUG
      int ThreadPriority = ::GetThreadPriority(m_handleThread);
      LOGN_DEBUG( "current thread priority " << ThreadPriority)
#endif
      if( prio != I_Thread::default_priority)
      {
        int nWinAPIpriority = GetWinAPIpriority(prio);
        LOGN_DEBUG( "setting Thread priority " << nWinAPIpriority)
        ::SetThreadPriority(
          m_handleThread, //_In_  HANDLE hThread,
          nWinAPIpriority //_In_  int nPriority
        );
      }
      return I_Thread::no_error ;
    }
    return I_Thread::error ;
  }

  Thread::~Thread()
  {
    LOGN_DEBUG( FULL_FUNC_NAME << " begin" )
    PossiblyCloseThreadHandle();
  }
  void * Thread::WaitForTermination()
  {
    DWORD dwExitCode ;
    //Waits for the end of the thread determined by the handle.
    ::WaitForSingleObject(m_handleThread, INFINITE) ;
    ::GetExitCodeThread(m_handleThread, & dwExitCode ) ;
    return (void *) dwExitCode ;
  }
}
