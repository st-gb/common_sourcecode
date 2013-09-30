/*
 * pthreadBasedI_Thread.cpp
 *
 *  Created on: Oct 12, 2010
 *      Author: sgebauer
 */

#include "pthreadBasedI_Thread.hpp"
#include <pthread.h> //int pthread_create(...)
#include <Controller/GetErrorMessageFromLastErrorCode.hpp>
//#include <Controller/Err GetLastErrorCode.hpp>
#include <preprocessor_macros/logging_preprocessor_macros.h> //LOGN(...)

namespace Linux
{
  typedef void * (* pthread_start_func_type) (void *) ;
  pthreadBasedI_Thread::pthreadBasedI_Thread(
    I_Thread::thread_type i_thread_thread_type )
  {
    m_i_thread_thread_type = i_thread_thread_type ;
  }

  pthreadBasedI_Thread::~pthreadBasedI_Thread()
  {
    // TODO Auto-generated destructor stub
  }

  int pthreadBasedI_Thread::GetThreadPriority()
  {
    if( m_pthread_t != 0 )
    {
  //      pthread_getspecific()
  //          sched_
      struct sched_param sched_paramVal;
      int policy;
  //      return default_priority;
      int n =
        //http://pubs.opengroup.org/onlinepubs/7908799/xsh/pthread_setschedparam.html:
        //"If successful, the pthread_getschedparam() and pthread_setschedparam()
        //functions return zero."
        pthread_getschedparam (
        m_pthread_t //pthread_t __target_thread
        , & policy //int *__restrict __policy,
        , & sched_paramVal //struct sched_param *__restrict __param
        );
      if( n != 0)
        return I_Thread::error_getting_priority;
      return sched_paramVal.__sched_priority;
    }
    return 0;
  }

  bool pthreadBasedI_Thread::IsRunning()
  {
    return m_pthread_t != 0 &&
      //From http://stackoverflow.com/questions/2156353/how-do-you-query-a-pthread-to-see-if-it-is-still-running
      pthread_kill(m_pthread_t, 0) != ESRCH;
  }

  BYTE pthreadBasedI_Thread::start(
    pfnThreadFunc pfn_threadfunc,
    void * p_v,
    /*BYTE*/ I_Thread::priority priority /*= default_priority*/ )
  {
    int nRetVal = 1 ;
    if( m_i_thread_thread_type == I_Thread::joinable )
      nRetVal =
        //cites from http://www.kernel.org/doc/man-pages/online/pages/man3/
        // pthread_create.3.html:
        //"On success, pthread_create() returns 0; on error, it returns an
        //error number, and the contents of *thread are undefined."
        pthread_create (
  //        pthread_t *__restrict __newthread,
          & m_pthread_t ,
  //      __const pthread_attr_t *__restrict __attr,
          //"If attr is NULL, then the thread is created with default attributes."
          //"By default, a new thread is created in a joinable state
          NULL ,
    //      void *(*__start_routine) (void *),
          ( pthread_start_func_type ) pfn_threadfunc ,
  //        void *__restrict __arg
          p_v
          ) ;
//    else
//    {
//      pthread_attr_t pthread_attr_t_ ;
//      pthread_attr_t_.__
//      nRetVal =
//        //cites from http://www.kernel.org/doc/man-pages/online/pages/man3/
//        // pthread_create.3.html:
//        //"On success, pthread_create() returns 0; on error, it returns an
//        //error number, and the contents of *thread are undefined."
//        pthread_create (
//  //        pthread_t *__restrict __newthread,
//          & m_pthread_t ,
//  //      __const pthread_attr_t *__restrict __attr,
//          //"If attr is NULL, then the thread is created with default attributes."
//          //"By default, a new thread is created in a joinable state
//          NULL ,
//    //      void *(*__start_routine) (void *),
//          ( pthread_start_func_type ) pfn_threadfunc ,
//  //        void *__restrict __arg
//          p_v
//          ) ;
//    }
    if( nRetVal )
      LOGN_ERROR("Failed to create thread: " << GetErrorMessageFromLastErrorCodeA() )
    else
    {
      LOGN_INFO("pthreadBasedI_Thread::start(...)--created thread with ID"
        << m_pthread_t)
      if( priority != default_priority )
      {
        LOGN_INFO("pthreadBasedI_Thread::start(...)--setting thread prio to "
          << (unsigned) priority)
        struct sched_param param_set, param_get;
        param_set.__sched_priority = priority;
        int policy;
        if( pthread_getschedparam(m_pthread_t, &policy, &param_get) == 0)
          if( pthread_setschedparam(m_pthread_t, policy, &param_set) == 0)
            return I_Thread::no_error;
      }
//      LOGN("Successfully created thread with thread ID " << m_pthread_t )
    }
    return nRetVal ;
  }

  void * pthreadBasedI_Thread::WaitForTermination()
  {
    LOGN("pthreadBasedI_Thread::WaitForTermination()--thread ID:"
      << m_pthread_t)
    if( m_pthread_t != 0 )
    {
      //http://www.kernel.org/doc/man-pages/online/pages/man3/pthread_join.3.html:
      //"The pthread_join() function waits for the thread specified by thread to
      //terminate."
      //"On success, pthread_join() returns 0; on error, it returns an error
      //number."
      int nReturn = pthread_join(
        m_pthread_t ,
        //"If retval is not NULL, then pthread_join() copies the exit status of the
        //target thread"
        NULL
        ) ;
      if( nReturn )
        LOGN("pthread_join failed:" << GetErrorMessageFromErrorCodeA( nReturn ) )
      else
        LOGN("pthread_join succeeded")
      return (void *) nReturn ;
    }
    return (void *) false;
  }
}
