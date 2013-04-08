/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */
/*
 * Win32EventBasedCondition.cpp
 *
 *  Created on: Jun 13, 2010
 *      Author: Stefan
 */
//#include "Win32EventBasedCondition.hpp"
//#include <windows.h> //::WaitForSingleObject(...)
//
//Win32EventBasedCondition::Win32EventBasedCondition()
//{
//  //cites from http://msdn.microsoft.com/en-us/library/
//  // ms682396%28v=VS.85%29.aspx
//  m_handleEvent =
//    //"If the function fails, the return value is NULL."
//    ::CreateEvent(
//    NULL,               // default security attributes
//    TRUE,               // manual-reset event
////    FALSE ,
//    FALSE,              // initial state is nonsignaled
//    //"If lpName is NULL, the event object is created without a name."
//    NULL //TEXT("WriteEvent")  // object name
//    );
//}
//
//Win32EventBasedCondition::~Win32EventBasedCondition()
//{
//  if( m_handleEvent )
//    ::CloseHandle(m_handleEvent);
//}
//
//void Win32EventBasedCondition::Broadcast()
//{
//  //All threads that wait on the event handle (e.g. via
//  //WaitForSingleObject(m_handleEvent) continue.
//  ::SetEvent(m_handleEvent) ;
//}
//
//void Win32EventBasedCondition::ResetEvent()
//{
//  ::ResetEvent(m_handleEvent) ;
//}
//
//void Win32EventBasedCondition::Wait()
//{
//  ::WaitForSingleObject(
//    m_handleEvent, // event handle
//    INFINITE);    // infinite wait
//}
