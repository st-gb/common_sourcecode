/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany
 * ("Trilobyte SE") 2010-at least 2012.
 * You are allowed to modify and use the source code from Trilobyte SE for free
 * if you are not making profit directly or indirectly with it or its adaption.
 * Else you may contact Trilobyte SE. */
/*
 * Thread.h
 *
 *  Created on: Jul 16, 2010
 *      Author: Stefan
 */

#ifndef THREAD_HPP_
#define THREAD_HPP_

#include <OperatingSystem/multithread/I_Thread.hpp> //pfnThreadFunc
#include <windows.h> //HANDLE
#include <hardware/CPU/fastest_data_type.h> //typedef fastestUnsignedDataType

namespace Windows_API
{

  class Thread
    : public I_Thread
  {
    BYTE m_byThreadType ;
    DWORD m_dwThreadId ;
  public:
    HANDLE m_handleThread ;
    Thread()
      : m_handleThread( NULL )
    {
    }
    Thread( BYTE byThreadType );
    virtual
    ~Thread();

    void Delete() {} ;
    unsigned GetThreadID() { return m_dwThreadId; }
    int GetThreadPriority();
    void * GetThreadHandle() { return m_handleThread; }
    int GetWinAPIpriority(BYTE prio)
    {
      switch(prio)
      {
      case I_Thread::default_priority:
        return THREAD_PRIORITY_NORMAL;
      case I_Thread::maximum_priority:
        return THREAD_PRIORITY_TIME_CRITICAL;
      }
      return THREAD_PRIORITY_NORMAL;
    }
    bool IsRunning()
    {
      //http://msdn.microsoft.com/en-us/library/windows/desktop/ms686724%28v=vs.85%29.aspx:
      //"Terminating a thread has the following results:"
      //  "The thread object is signaled."
      DWORD dw = ::WaitForSingleObject(m_handleThread, 0);
      //if running: WAIT_TIMEOUT when WaitForSingleObject(),
      return dw
//        //"The state of the specified object is signaled."->thread terminated.
//        != WAIT_OBJECT_0;
        == WAIT_TIMEOUT;
    }
    inline void PossiblyCloseThreadHandle();
    /** Implementation with same method name seems to hide base class function
     *  So declare base class's "start" function here again.
    //see http://stackoverflow.com/questions/16005894/a-function-from-a-base-class-is-being-hidden-in-the-subclass-how-do-i-fix-this */
    using I_Thread::start;
    fastestUnsignedDataType start(
      pfnThreadFunc,
      void * p_v,
      /*BYTE*/ enum I_Thread::priority prio = I_Thread::default_priority) ;
//  //TODO should be working when function is implemented in base class.
  BYTE start(
    pfnThreadFunc pfnthreadfunc,
    void * p_v,
    const char * const threadName,
    /*BYTE*/ enum priority prio = default_priority)
  {
//    GetThread m_handleThread
//    OpenThreadToken(m_handleThread, 0x1000, FALSE, )
//    SetCurrentThreadName(threadName);
    BYTE t_start = start(pfnthreadfunc, p_v, prio);
    if( t_start == I_Thread::no_error)
    {
      unsigned threadID = GetThreadID();
      SetThreadName(threadName, threadID);
    }
    return t_start;
  }
    void * WaitForTermination() const;
    void * WaitForTermination(fastestUnsignedDataType) const;
  };
}

#endif /* THREAD_HPP_ */
