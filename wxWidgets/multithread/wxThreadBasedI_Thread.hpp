/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany
 * ("Trilobyte SE") 2010-at least 2012.
 * You are allowed to modify and use the source code from Trilobyte SE for free
 * if you are not making profit directly or indirectly with it or its adaption.
 * Else you may contact Trilobyte SE. */
/*
 * wxThreadBasedI_Thread.hpp
 *
 *  Created on: Jun 16, 2010
 *      Author: Stefan
 */

#ifndef WXTHREADBASEDI_THREAD_HPP_
#define WXTHREADBASEDI_THREAD_HPP_

#include <Controller/multithread/I_Thread.hpp>
#include <wx/thread.h>
#include <fastest_data_type.h> //typedef fastestUnsignedDataType

class wxThreadFuncStarterThread
  : public wxThread
{
  pfnThreadFunc m_thread_func ;
  void * mp_v ;
public:
  wxThreadFuncStarterThread(
    pfnThreadFunc pfn_threadfunc ,
    void * p_v ,
    BYTE byThreadType) ;
  void * Entry() ;
};

class wxThreadBasedI_Thread
  : public I_Thread
{
  wxThreadFuncStarterThread * mp_wxthreadfuncstarterthread ;
public:
  wxThreadBasedI_Thread( BYTE byThreadType = I_Thread::joinable ) ;
  //else "g++ warning: virtual function but non-virtual destructor"s
  virtual ~wxThreadBasedI_Thread() ;
  void Delete() ;
  //static
    BYTE start( pfnThreadFunc, void * p_v, BYTE priority =
      WXTHREAD_DEFAULT_PRIORITY) ;

  enum I_Thread::priority wxThreadPrio2I_ThreadPrio(
    fastestUnsignedDataType wxThreadPriority)
  {
    switch(wxThreadPriority)
    {
      case WXTHREAD_DEFAULT_PRIORITY:
        return I_Thread::default_priority;
      case WXTHREAD_MAX_PRIORITY:
        return I_Thread::maximum_priority;
    }
    return I_Thread::default_priority;
  }
  fastestUnsignedDataType I_ThreadPrio2wxThreadPrio(
    const I_Thread::priority priority)
  {
    switch(priority)
    {
      case I_Thread::default_priority:
        return WXTHREAD_DEFAULT_PRIORITY;
      case I_Thread::maximum_priority:
        return WXTHREAD_MAX_PRIORITY;
    }
    return WXTHREAD_DEFAULT_PRIORITY;
  }
  /** Implementation with same method name seems to hide base class function
   *  So declare base class's "start" function here again.
  //see http://stackoverflow.com/questions/16005894/a-function-from-a-base-class-is-being-hidden-in-the-subclass-how-do-i-fix-this */
  using I_Thread::start;
  BYTE start(pfnThreadFunc threadFunc, void * p_vThreadFuncParam,
    I_Thread::priority prio)
  {
    fastestUnsignedDataType wxThreadPrio = I_ThreadPrio2wxThreadPrio(prio);
    return start(threadFunc, p_vThreadFuncParam, wxThreadPrio);
  }
  int GetThreadPriority()
  {
    return mp_wxthreadfuncstarterthread->GetPriority();
  }
  bool IsRunning()
  {
    if( mp_wxthreadfuncstarterthread && m_byThreadType == I_Thread::joinable)
      return mp_wxthreadfuncstarterthread->IsRunning();
    return false;
  }
  void * WaitForTermination() ;
};

#endif /* WXTHREADBASEDI_THREAD_HPP_ */
