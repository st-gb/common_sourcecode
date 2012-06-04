/*
 * WaitAndExecuteFunction.hpp
 *
 *  Created on: 09.04.2012
 *      Author: Stefan
 */

#ifndef WAITANDEXECUTEFUNCTION_HPP_
#define WAITANDEXECUTEFUNCTION_HPP_

#include <windef.h> //DWORD

namespace Windows_API
{
  struct WaitTimeAndThreadFunc
  {
    DWORD m_dwWaitTimeInMillis;
//    pfnThreadFunc m_pfn_threadfunc;
//    void m_pfn_threadfunc(void ) ;
    typedef void (* functionToExecuteType)();
    functionToExecuteType m_pfn_threadfunc;

    WaitTimeAndThreadFunc(
      DWORD dwWaitTimeInMillis,
//      pfnThreadFunc pfn_threadfunc
//      void pfn_threadfunc(void )
      functionToExecuteType pfn_threadfunc
      )
    {
      m_dwWaitTimeInMillis = dwWaitTimeInMillis;
      m_pfn_threadfunc = pfn_threadfunc;
    }
  };

  DWORD THREAD_FUNCTION_CALLING_CONVENTION WaitAndExec_ThreadFunc(void * p_v)
  {
//    pfnThreadFunc pfn_threadfunc = (pfnThreadFunc) p_v;
    WaitTimeAndThreadFunc * p_waittimeandthreadfunc = (WaitTimeAndThreadFunc *)
      p_v;
    if( //pfn_threadfunc
        p_waittimeandthreadfunc )
    {
      ::Sleep(p_waittimeandthreadfunc->m_dwWaitTimeInMillis);
      p_waittimeandthreadfunc->m_pfn_threadfunc();
      //Was created on heap on the thread that spawned _this_ thread.
      delete p_waittimeandthreadfunc;
    }
    return 0;
  }

  void WaitAsyncAndExec(DWORD dwMilliseconds, //pfnThreadFunc pfn_threadfunc
    WaitTimeAndThreadFunc::functionToExecuteType pfn_threadfunc
    //, void * p_v
    )
  {
    WaitTimeAndThreadFunc * p_waittimeandthreadfunc = new WaitTimeAndThreadFunc(
      dwMilliseconds, pfn_threadfunc);
    ::CreateThread(
      NULL,
      //"The initial size of the stack, in bytes."
      //"If this parameter is zero, the new thread uses the default size for
      //the executable.
      0,
      WaitAndExec_ThreadFunc,
//      (void *) pfn_threadfunc,
      (void *) p_waittimeandthreadfunc,
      0, //dwCreationFlags: 0=The thread runs immediately after creation.
      NULL //"If this parameter is NULL, the thread identifier is not returned."
      );
  }
}

#endif /* WAITANDEXECUTEFUNCTION_HPP_ */
