/*
 * pthreadBasedI_Thread.hpp
 *
 *  Created on: Oct 12, 2010
 *      Author: sgebauer
 */

#ifndef PTHREADBASEDI_THREAD_HPP_
#define PTHREADBASEDI_THREAD_HPP_

#include <OperatingSystem/multithread/I_Thread.hpp> //class I_Thread
//#include <bits/pthreadtypes.h> //pthread_t
#include <pthread.h> //pthread_t
//#include <bits/sigthread.h> //pthread_kill(..)
#include <signal.h> //pthread_kill(..)
#include <errno.h> //ESRCH

namespace POSIX
{

  class pthreadBasedI_Thread
    : public I_Thread
  {
    I_Thread::thread_type m_i_thread_thread_type ;
    pthread_t m_pthread_t ;
    unsigned successfullyCreated;
  public:
    pthreadBasedI_Thread(I_Thread::thread_type = I_Thread::joinable );
    virtual
    ~pthreadBasedI_Thread();
//    unsigned GetThreadID() { pthread_getthreadid_np() }
    /** impl. with same method name seems to hide base class function
    //see http://stackoverflow.com/questions/16005894/a-function-from-a-base-class-is-being-hidden-in-the-subclass-how-do-i-fix-this */
    using I_Thread::start;
//    pthread_t GetThreadHandle(){ return m_pthread_t; }
    fastestUnsignedDataType start(
      pfnThreadFunc,
      void * p_vThreadFuncParameter,
      /*BYTE*/ I_Thread::priority priority = default_priority) ;
//    BYTE start(DWORD (*)(void*), void*, I_Thread::priority)
    //inline
      void * WaitForTermination() ;
    int GetThreadPriority();
    void * GetThreadHandle() {return (void *) & m_pthread_t;}
    //TODO implement IsRunning
    bool IsRunning();
  };

}

#endif /* PTHREADBASEDI_THREAD_HPP_ */
