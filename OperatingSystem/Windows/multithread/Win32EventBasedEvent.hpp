/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */
/** Win32EventBasedCondition.hpp
 *  Created on: Jun 13, 2010
 *  Author: Stefan Gebauer, M.Sc. Comp.Sc. */

#ifndef WIN32EVENTBASEDEVENT_HPP_
#define WIN32EVENTBASEDEVENT_HPP_

///Windows Operating System header files:
/// WAIT_OBJECT_0 in winbase.h
#include <synchapi.h>///::WaitForSingleObjectEx(...)
#include <windows.h> //for HANDLE, ::WaitForSingleObject(...)

///Stefan Gebauer's "common sourcecode" repository header files:
#include <OperatingSystem/multithread/I_Condition.hpp>///I_Condition::state

class Win32EventBasedEvent
{
    HANDLE m_handleEvent ;
  public :
//    Win32EventBasedEvent() ;
//    ~Win32EventBasedEvent() ;
//
//    void Broadcast() ;
//    void ResetEvent() ;
//    void Wait() ;

    //Define the functions here in the header: inline-> faster
    Win32EventBasedEvent()
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

    ~Win32EventBasedEvent()
    {
      if( m_handleEvent )
        ::CloseHandle(m_handleEvent);
    }

    void SetEvent()
    {
      //All threads that wait on the event handle (e.g. via
      //WaitForSingleObject(m_handleEvent) continue.
      ::SetEvent(m_handleEvent) ;
      //When manual reset event then must reset it after SetEvent(...) else
      //malfunctions as I remember.
      ::ResetEvent(m_handleEvent) ;
    }

  //TODO use return value from "::SetEvent(...)"?
  void Broadcast(){
	SetEvent();
  }

    void ResetEvent()
    {
      ::ResetEvent(m_handleEvent) ;
    }

    void Wait()
    {
      ::WaitForSingleObject(
        m_handleEvent, // event handle
        INFINITE);    // infinite wait
    }

I_Condition::state WaitForSignalOrTimeoutInMs(
  const fastestUnsignedDataType timeOutInMs)
{
  DWORD rtrnVal = ::WaitForSingleObjectEx(
    m_handleEvent,
    timeOutInMs,
    FALSE/**bAlertable*/);
  switch(rtrnVal){
   case WAIT_ABANDONED:
    return I_Condition::wait_abandoned;
   /** https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-waitforsingleobject :
    * "The state of the specified object is signaled." */
   case WAIT_OBJECT_0:
    return I_Condition::signaled;
   case WAIT_TIMEOUT:
    return I_Condition::timed_out;
   case WAIT_FAILED:
    return I_Condition::wait_failed;
  }
  return I_Condition::other_error;
}
};///end class

#endif /* WIN32EVENTBASEDEVENT_HPP_ */
