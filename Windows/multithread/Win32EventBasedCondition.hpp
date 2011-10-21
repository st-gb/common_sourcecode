/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */
/*
 * Win32EventBasedCondition.hpp
 *
 *  Created on: Jun 13, 2010
 *      Author: Stefan
 */

#ifndef WIN32EVENTBASEDCONDITION_HPP_
#define WIN32EVENTBASEDCONDITION_HPP_

#include <windows.h> //for HANDLE, ::WaitForSingleObject(...)

  class Win32EventBasedCondition
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

    ~Win32EventBasedCondition()
    {
      if( m_handleEvent )
        ::CloseHandle(m_handleEvent);
    }

    void Broadcast()
    {
      //All threads that wait on the event handle (e.g. via
      //WaitForSingleObject(m_handleEvent) continue.
      ::SetEvent(m_handleEvent) ;
      //When manual reset event then must reset it after SetEvent(...) else
      //malfunctions as I remember.
      ::ResetEvent(m_handleEvent) ;
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
      ::ResetEvent(m_handleEvent) ;
    }

    DWORD Wait()
    {
      DWORD dw = ::WaitForSingleObject(
        m_handleEvent, // event handle
        INFINITE);    // infinite wait
      return dw;
    }
  };

#endif /* WIN32EVENTBASEDCONDITION_HPP_ */
