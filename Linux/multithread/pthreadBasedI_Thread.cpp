/*
 * pthreadBasedI_Thread.cpp
 *
 *  Created on: Oct 12, 2010
 *      Author: sgebauer
 */

#include "pthreadBasedI_Thread.hpp"
#include <pthread.h> //int pthread_create(...)
#include <Controller/GetErrorMessageFromLastErrorCode.hpp>
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

  BYTE pthreadBasedI_Thread::start( pfnThreadFunc pfn_threadfunc, void * p_v )
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
      LOGN("Failed to create thread: " << GetErrorMessageFromLastErrorCodeA() )
    else
      LOGN("Successfully created thread with thread ID " << m_pthread_t )
    return nRetVal ;
  }

  void * pthreadBasedI_Thread::WaitForTermination()
  {
    LOGN("pthreadBasedI_Thread::WaitForTermination()--thread ID:"
      << m_pthread_t)
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
}
