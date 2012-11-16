/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany
 * ("Trilobyte SE") 2010-at least 2012.
 * You are allowed to modify and use the source code from Trilobyte SE for free
 * if you are not making profit directly or indirectly with it or its adaption.
 * Else you may contact Trilobyte SE. */
/*
 * wxThreadBasedI_Thread.cpp
 *
 *  Created on: Jun 16, 2010
 *      Author: Stefan
 */
#include "wxThreadBasedI_Thread.hpp"
//#include <global.h>
#include <preprocessor_macros/logging_preprocessor_macros.h> //LOGN(...)

wxThreadFuncStarterThread::wxThreadFuncStarterThread(
  pfnThreadFunc pfn_threadfunc ,
  void * p_v ,
  BYTE byThreadType
  )
  //TODO program crashes here (segmentation fault under Linux)
  : wxThread ( //wxTHREAD_JOINABLE
    (wxThreadKind) byThreadType
    )
{
  LOGN("starter thread--byThreadType:" << (WORD) byThreadType )
  m_thread_func = pfn_threadfunc ;
  mp_v = p_v ;
}

void *
//ExitCode
wxThreadFuncStarterThread::Entry()
{
  LOGN("starter thread : before calling the worker function")
  DWORD dwReturn = m_thread_func( mp_v ) ;
  LOGN("starter thread: return code of the thread function:" << dwReturn)
  return (void*) dwReturn;
}

//  BYTE wxThreadBasedI_Thread::Entry( )
//  {
//
//  }

wxThreadBasedI_Thread::wxThreadBasedI_Thread( BYTE byThreadType )
  : mp_wxthreadfuncstarterthread( NULL )
{
  LOGN("thread type:" << (WORD) byThreadType )
  m_byThreadType = byThreadType ;
}

wxThreadBasedI_Thread::~wxThreadBasedI_Thread()
{
  Delete() ;
  LOGN("end of thread's destructor")
}

void wxThreadBasedI_Thread::Delete()
{
  DEBUGN("wxThreadBasedI_Thread::Delete()")
  LOGN("..ThreadBasedI_Thread::Delete()  starter thread pointer:" <<
    mp_wxthreadfuncstarterthread)
  if( mp_wxthreadfuncstarterthread
      //only delete when joinable (detached wxThreads are auto-deleted: else
      //the program may crash: terminated unexpectedly)
      && m_byThreadType == I_Thread::joinable)
  {
    LOGN("before deleting the thread with ID "
      << mp_wxthreadfuncstarterthread->GetId() )
    //http://docs.wxwidgets.org/2.6/wx_wxthread.html#wxthreadwait:
    //"and you also must delete the corresponding wxThread
    //object yourself"

    //http://docs.wxwidgets.org/2.8/wx_wxthread.html#deletionwxthread:
    //"If you created a joinable thread on the heap, remember to delete it
    //manually with the delete operator or similar means as only detached
    //threads handle this type of memory management."
    delete mp_wxthreadfuncstarterthread ;
    //If this function is not called in the destructor of this class, we
    //set to NULL to prevent a second "delete".
    mp_wxthreadfuncstarterthread = NULL ;
    LOGN("after deleting the thread." )
  }
}

//@return I_Thread::no_error on success, else I_Thread::error
  //static
  BYTE wxThreadBasedI_Thread::start( pfnThreadFunc pfn_threadfunc, void * p_v,
    BYTE priority)
  {
    LOGN("wxThreadBasedI_Thread::start(" << (void *) pfn_threadfunc
        << "," << p_v << ") begin")
    //make the same thread type like Win32 threads.
    //http://docs.wxwidgets.org/2.6/wx_wxthread.html#wxthreadentry:
    //"[...]unlike Win32 threads where all threads are joinable[...]
    //"Detached threads (the default type) cannot be waited for."
//    wxThread wxthread(wxTHREAD_JOINABLE) ;
    //"all detached threads must be created on the heap"
//    wxThreadFuncStarterThread wxthreadfuncstarterthread ( pfn_threadfunc , p_v );
//    wxThreadFuncStarterThread * p_wxthreadfuncstarterthread = new
    mp_wxthreadfuncstarterthread = new
        wxThreadFuncStarterThread( pfn_threadfunc , p_v , m_byThreadType );
    wxThreadFuncStarterThread * p_wxthreadfuncstarterthread =
        mp_wxthreadfuncstarterthread ;
    if( p_wxthreadfuncstarterthread )
    {
      LOGN("starter thread successfully allocated")
      //http://docs.wxwidgets.org/2.6/wx_wxthread.html#wxthreadcreate:s
      //"Creates a new thread. The thread object is created in the suspended
      //state, and you should call Run  to start running it."
  //    wxThreadError wxthreaderror = wxthread.Create() ;
      wxThreadError wxthreaderror = //wxthreadfuncstarterthread.Create() ;
          p_wxthreadfuncstarterthread->Create() ;
      if( wxthreaderror == wxTHREAD_NO_ERROR )
      {
        LOGN("starter thread successfully created")
        //"Starts the thread execution. Should be called after Create."
  //      wxthread.Run() ;
//        return //wxthreadfuncstarterthread.Run() ;
        //http://docs.wxwidgets.org/stable/wx_wxthread.html#wxthreadsetpriority:
        //"It can only be set after calling Create() but before calling Run()."
        p_wxthreadfuncstarterthread->SetPriority(priority);
        wxThreadError wxthreaderr = p_wxthreadfuncstarterthread->Run() ;
        LOGN("result of starter thread.run:" << (WORD) wxthreaderr )
        switch(wxthreaderr)
        {
        case wxTHREAD_NO_ERROR :
          return I_Thread::no_error ;
          //Avoid g++ warnings like
          //"enumeration value `wxTHREAD_KILLED' not handled in switch"
        case wxTHREAD_NO_RESOURCE:  // No resource left to create a new thread
        case wxTHREAD_RUNNING:         // The thread is already running
        case wxTHREAD_NOT_RUNNING:       // The thread isn't running
        case wxTHREAD_KILLED:         // Thread we waited for had to be killed
        case wxTHREAD_MISC_ERROR:         // Some other error
        	break ;
        }
      }
      else
        LOGN("Failed to create starter thread.")
    }
    else
    {
      LOGN("Failed to allocate starter thread.")
    }
    return I_Thread::error ;
  }

  void * wxThreadBasedI_Thread::WaitForTermination()
  {
    DEBUGN("wxThreadBasedI_Thread::Wait()")
    if( mp_wxthreadfuncstarterthread && m_byThreadType == I_Thread::joinable )
    {
      wxThread::ExitCode wxthread_exit_code =
        //http://docs.wxwidgets.org/stable/wx_wxthread.html#wxthreadwait:
        //"Waits for a joinable thread to terminate and returns the value the
        //thread returned from wxThread::Entry  or (ExitCode)-1 on error.
        //Notice that, unlike Delete  doesn't cancel the thread in any way so
        //the caller waits for as long as it takes to the thread to exit.
        //You can only Wait() for joinable (not detached) threads.
        //This function can only be called from another thread context."
        mp_wxthreadfuncstarterthread->Wait() ;
      LOGN("exit code from starter thread:" << wxthread_exit_code )
      return wxthread_exit_code;
    }
    //TODO better return -1 for error?: Wait() also returns (ExitCode)-1" on
    //error
    return (void *) 1 ;
  }
//  BYTE wxThreadBasedI_Thread::start( pfnThreadFunc, void * p_v )
//  {
//    m_thread_func = pfnThreadFunc ;
//    mp_v = p_v ;
//    Run() ; //calls "Entry()"
//  }
