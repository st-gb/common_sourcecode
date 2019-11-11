/** pthreadBasedI_Thread.cpp
 *  Created on: Oct 12, 2010
 *      Author: sgebauer  */
#include "pthreadBasedI_Thread.hpp"
#include <pthread.h> //int pthread_create(...)
#include <compiler/GCC/enable_disable_warning.h>///GCC_DIAG_OFF(...)
#include <OperatingSystem/GetErrorMessageFromErrorCode.h>
#include <OperatingSystem/GetErrorMessageFromLastErrorCode.hpp>
#include <OperatingSystem/multithread/GetCurrentThreadNumber.hpp>
#include <preprocessor_macros/logging_preprocessor_macros.h> //LOGN(...)

#pragma message "link with -pthread."

/** http://man7.org/linux/man-pages/man3/pthread_create.3.html : 
 *  "CONFORMING TO: POSIX.1-2001, POSIX.1-2008." */
namespace POSIX
{
  typedef void * (* pthread_start_func_type) (void *) ;
  pthreadBasedI_Thread::pthreadBasedI_Thread(
    I_Thread::thread_type i_thread_thread_type )
    : m_pthread_t(0)
     , successfullyCreated(0)
  {
    m_i_thread_thread_type = i_thread_thread_type ;
  }

pthreadBasedI_Thread::~pthreadBasedI_Thread()
{
  if( m_i_thread_thread_type == I_Thread::joinable && successfullyCreated &&
     notJoinedYet)
    /** http://man7.org/linux/man-pages/man3/pthread_create.3.html , "NOTES" 
     * section:
    * "Only when a terminated joinable thread has been joined are the last of 
    * its resources released back to the system." */
    pthread_join(
      m_pthread_t ,
      /** http://man7.org/linux/man-pages/man3/pthread_join.3.html, 
       * "DESCRIPTION" section :
       * "If retval is not NULL, then pthread_join() copies the exit status of
      * the target thread"*/
      NULL
      );
  }

  int pthreadBasedI_Thread::GetThreadPriority()
  {
    if( successfullyCreated )
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
#ifdef __ANDROID__
        return I_Thread::error_getting_priority;
#else
      return sched_paramVal.__sched_priority;
#endif
    }
    return 0;
  }

bool pthreadBasedI_Thread::IsRunning()
{
  bool isRunning = false;
  if(successfullyCreated)///Prevent using m_pthread_t if thread not created
  {
    const int pthread_killRetVal =
      ///From
      ///http://stackoverflow.com/questions/2156353/how-do-you-query-a-pthread-to-see-if-it-is-still-running
      pthread_kill(m_pthread_t,
        /** http://man7.org/linux/man-pages/man3/pthread_kill.3.html : 
         * "If sig is 0, then no signal is sent, but error checking is still
         * performed." */
        0);
    isRunning = pthread_killRetVal !=
      /** http://man7.org/linux/man-pages/man3/pthread_kill.3.html :
       * "POSIX.1-2008 recommends that if an implementation detects the use of
       * a thread ID after the end of its lifetime, pthread_kill() should
       * return the error ESRCH." */
      ESRCH && pthread_killRetVal !=
      /** In Android emulator (x86) value was EINVAL after end of thread
       * function/after setting thread exit code*/
      EINVAL;
  }
  return isRunning;
}

  fastestUnsignedDataType pthreadBasedI_Thread::start(
    pfnThreadFunc pfn_threadfunc,
    void * p_vThreadFunctionArgument,
    /*BYTE*/ I_Thread::priority priority /*= default_priority*/ )
  {
    int nRetVal = 1 ;
    if( m_i_thread_thread_type == I_Thread::joinable )
      nRetVal =
      /**from http://www.kernel.org/doc/man-pages/online/pages/man3/pthread_create.3.html:
      * "On success, pthread_create() returns 0; on error, it returns an
      * error number, and the contents of *thread are undefined." */
        pthread_create (
  //        pthread_t *__restrict __newthread,
          & m_pthread_t ,
  //      __const pthread_attr_t *__restrict __attr,
          //"If attr is NULL, then the thread is created with default attributes."
          //"By default, a new thread is created in a joinable state
          NULL ,
          /* void *(*__start_routine) (void *),*/
          ( pthread_start_func_type ) pfn_threadfunc ,
          p_vThreadFunctionArgument /** void *__restrict __arg */
          );
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
      //TODO 1.:really rely on logging functions? 2.:1 error message was: 
      // "Failed to create thread: Cannot allocate memory", nRetVal=11, errno=12
      LOGN_ERROR("Failed to create thread: " << OperatingSystem::
        GetErrorMessageFromLastErrorCodeA() )
    else
    {
      successfullyCreated = 1;
      //TODO m_pthread_t is not the OS thread ID
      LOGN_INFO("--created thread with POSIX ID " << m_pthread_t)
      if( priority != default_priority )
      {
        LOGN_INFO("pthreadBasedI_Thread::start(...)--setting thread prio to "
          << (unsigned) priority)
        struct sched_param param_set, param_get;
#ifndef __ANDROID__
        param_set.__sched_priority = priority;
#endif
        int policy;
        if( pthread_getschedparam(m_pthread_t, &policy, &param_get) == 0)
          if( pthread_setschedparam(m_pthread_t, policy, &param_set) == 0)
            return I_Thread::no_error;
      }
//      LOGN("Successfully created thread with thread ID " << m_pthread_t )
    }
    return nRetVal ;
  }

//TODO better return a value like from enum thread_start?
void * pthreadBasedI_Thread::WaitForTermination()
{
  const DWORD currentThreadNumber = OperatingSystem::GetCurrentThreadNumber();
  ///Only log in debug versions to avoid unnessary output.
  LOGN_DEBUG("thread ID:" << /*m_pthread_t*/ currentThreadNumber)
  if( successfullyCreated && notJoinedYet)
  {
    /** http://man7.org/linux/man-pages/man3/pthread_join.3.html, "NOTES" :
     * "Failure to join with a thread that is joinable (i.e., one that is not
     * detached), produces a "zombie thread".
     * Prevent this by setting this flag. */
    notJoinedYet = false;
    int * threadRetCode;
    ///http://www.informit.com/articles/article.aspx?p=2085690&seqNum=5
    /** http://www.kernel.org/doc/man-pages/online/pages/man3/pthread_join.3.html:
    * "The pthread_join() function waits for the thread specified by thread to
    * terminate."
    * "On success, pthread_join() returns 0; on error, it returns an error
    * number." */
    const int nReturn = pthread_join(
      m_pthread_t ,
    /** http://man7.org/linux/man-pages/man3/pthread_join.3.html
      * "If retval is not NULL, then pthread_join() copies the exit status of 
      * the target thread" */
        /*NULL*/ (void**)&threadRetCode
        ) ;
    if( nReturn )
      ///Only log in debug versions to avoid unnessary output.
      LOGN_DEBUG("pthread_join failed:" << OperatingSystem::
        GetErrorMessageFromErrorCodeA( nReturn ) )
    else
    {
      ///Only log in debug versions to avoid unnessary output.
      LOGN_DEBUG("pthread_join successful return value:" << nReturn << " "
        << (long long) threadRetCode)
      m_threadRetCode = threadRetCode;
      //LOGN_DEBUG("pthread_join succeeded")
    }
    return (void *) nReturn;
  }
  return (void *) -1;
}

//TODO return the thread function termination code as call-by-reference and the
// whether succeeded as (enum) return value?
int pthreadBasedI_Thread::GetTermCode()//const
{
  //GCC_DIAG_OFF(-fno-permissive)
  //#pragma GCC diagnostic ignored "-fpermissive"
  // "void *" can't be directly casted to "int"
  // https://en.cppreference.com/w/cpp/language/reinterpret_cast
//  const int termCode = //static_cast
//    //dynamic_cast
//    reinterpret_cast<
//    //https://bytes.com/topic/c/answers/482159-cast-void-int
//    long long>(WaitForTermination() );
 
  if(successfullyCreated)
  {
    if(notJoinedYet)
    {
     if(/** If finished--prevent waiting for thread end via "pthread_join"*/
       ! IsRunning() )
     {
      int * threadRetCode;
      ///http://www.informit.com/articles/article.aspx?p=2085690&seqNum=5

      /** http://man7.org/linux/man-pages/man3/pthread_join.3.html , sections
      * "DESCRIPTION", RETURN VALUE" :
      * "The pthread_join() function waits for the thread specified by thread to
      * terminate."
      * "On success, pthread_join() returns 0; on error, it returns an error
      * number." */
      const int nReturn = 
        /** The thread return code can only be determined by calling 
         * "pthread_join".*/
        pthread_join(
          m_pthread_t ,
          /** http://man7.org/linux/man-pages/man3/pthread_join.3.html , section
           * "DESCRIPTION" :
           * "If retval is not NULL, then pthread_join() copies the exit status
           *  of the target thread" */
          /*NULL*/ (void**)& threadRetCode
          );
      /** http://man7.org/linux/man-pages/man3/pthread_join.3.html, "NOTES" :
       * "Failure to join with a thread that is joinable (i.e., one that is not
       * detached), produces a "zombie thread".
       * Prevent this by setting this flag. */
      notJoinedYet = false;
      LOGN_DEBUG("pthread_join return value:" << nReturn << " " << (long long)
        m_threadRetCode)
      if( nReturn == 0)///successfully joined.
      {
        m_threadRetCode = threadRetCode;
        /** Casting to "long" to avoids g++ 7.3.0 error "error: cast from 
         * ‘int*’ to ‘int’ loses precision [-fpermissive]" */
        return (long)m_threadRetCode;
      }
      /** http://man7.org/linux/man-pages/man3/pthread_join.3.html:
       * errno "ESRCH" if thread is already finished. */
      if( nReturn == ESRCH )//TODO return threadRetCode or m_threadRetCode?
        return (long long) threadRetCode;
     }
    }
    else///Already joined--i.e. finished yet?
      return (long long) m_threadRetCode;
  }
  return -1;
}
}///End namepace
