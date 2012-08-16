/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany
 * ("Trilobyte SE") 2010-at least 2012.
 * You are allowed to modify and use the source code from Trilobyte SE for free
 * if you are not making profit directly or indirectly with it or its adaption.
 * Else you may contact Trilobyte SE. */
/*
 * Win32EventBasedCondition.hpp
 *
 *  Created on: Jun 13, 2010
 *      Author: Stefan
 */

#ifndef WIN32EVENTBASEDCONDITION_HPP_
#define WIN32EVENTBASEDCONDITION_HPP_

#include <windows.h> //for HANDLE, ::WaitForSingleObject(...)
#include <Controller/multithread/I_Condition.hpp> //Base class I_Condition

  class Win32EventBasedCondition
    : public I_Condition
  {
  public :
    HANDLE m_handleEvent ;
//    Win32EventBasedCondition() ;
//    ~Win32EventBasedCondition() ;
//
//    void Broadcast() ;
//    void ResetEvent() ;
//    void Wait() ;

    //Define the functions here in the header: inline-> faster
    Win32EventBasedCondition()
    {
      //cites from http://msdn.microsoft.com/en-us/library/
      // ms682396%28v=VS.85%29.aspx
      m_handleEvent =
        //"If the function fails, the return value is NULL."
        ::CreateEvent(
        NULL,               // default security attributes
        TRUE,               // manual-reset event
    //    FALSE ,
        FALSE,              // initial state is nonsignaled
        //"If lpName is NULL, the event object is created without a name."
        NULL //TEXT("WriteEvent")  // object name
        );
    }

    virtual ~Win32EventBasedCondition()
    {
      if( m_handleEvent )
        ::CloseHandle(m_handleEvent);
    }

    I_Condition::state Broadcast()
    {
      //All threads that wait on the event handle (e.g. via
      //WaitForSingleObject(m_handleEvent) continue.
      //http://msdn.microsoft.com/en-us/library/windows/desktop/ms686211%28v=vs.85%29.aspx:
      //"If the function succeeds, the return value is nonzero."
      if( ::SetEvent(m_handleEvent) )
        //When manual reset event then must reset it after SetEvent(...) else
        //malfunctions as I remember.
        //"If the function succeeds, the return value is nonzero."
        if( //"Sets the specified event object to the nonsignaled state."
            ::ResetEvent(m_handleEvent) )
          return I_Condition::success;
      return I_Condition::other_error;
    }

//    void ResetEvent()
//    {
//      ::ResetEvent(m_handleEvent) ;
//    }
    void SetEvent()
    {
      //All threads that wait on the event handle (e.g. via
      //WaitForSingleObject(m_handleEvent) continue.
      ::SetEvent(m_handleEvent) ;
      //When manual reset event then must reset it after SetEvent(...) else
      //malfunctions as I remember.
      ::ResetEvent(m_handleEvent) ;
    }

    void ResetEvent()
    {
      //Sets the state to nonsignaled?!
      ::ResetEvent(m_handleEvent) ;
    }

    I_Condition::state WaitForSingleObjectResultToI_ConditionState(
      DWORD WaitForSingleObjectResult)
    {
      switch( WaitForSingleObjectResult)
      {
        //"The state of the specified object is signaled."
        case WAIT_OBJECT_0:
          return I_Condition::signaled;
          //"The time-out interval elapsed, and the object's state is nonsignaled."
        case WAIT_TIMEOUT:
          return I_Condition::timed_out;
          //"The function has failed. To get extended error information, call GetLastError."
        case WAIT_FAILED:
          return I_Condition::wait_failed;
        case WAIT_ABANDONED:
          //"The specified object is a mutex object that was not released by
          //the thread that owned the mutex object before the owning thread
          //terminated. Ownership of the mutex object is granted to the calling
          //thread and the mutex state is set to nonsignaled.
          //If the mutex was protecting persistent state information, you
          //should check it for consistency."
          return I_Condition::wait_abandoned;
      }
      return I_Condition::other_error;
    }

    I_Condition::state Wait()
    {
      DWORD dw = ::WaitForSingleObject(
        m_handleEvent, // event handle
        INFINITE);    // infinite wait
      return WaitForSingleObjectResultToI_ConditionState(dw);
    }

    I_Condition::state WaitTimeOut(DWORD dwMilliSecondsToWait)
    {
      DWORD dwResult =
        //http://msdn.microsoft.com/en-us/library/windows/desktop/ms687032%28v=vs.85%29.aspx
        ::WaitForSingleObject(
          m_handleEvent, dwMilliSecondsToWait);
      return WaitForSingleObjectResultToI_ConditionState(dwResult);
    }
  };

#endif /* WIN32EVENTBASEDCONDITION_HPP_ */
