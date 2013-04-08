/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany
 * ("Trilobyte SE") 2010-at least 2012.
 * You are allowed to modify and use the source code from Trilobyte SE for free
 * if you are not making profit directly or indirectly with it or its adaption.
 * Else you may contact Trilobyte SE. */
/*
 * wxConditionBasedI_Condition.cpp
 *
 *  Created on: Jul 16, 2010
 *      Author: Stefan
 */

//#include "wxConditionBasedI_Condition.hpp"

//wxConditionBasedI_Condition::wxConditionBasedI_Condition()
//  : m_wxcondition (m_wxmutex)
//{
//
//}
//
//wxCondError wxConditionBasedI_Condition::Broadcast()
//{
//  return m_wxcondition.Broadcast() ;
//}
//
//wxMutexError wxConditionBasedI_Condition::Lock()
//{
//  return m_wxmutex.Lock() ;
//}
//
//void wxConditionBasedI_Condition::LockAndWait()
//{
//  //http://docs.wxwidgets.org/stable/wx_wxcondition.html#wxconditionctor:
//  //"The mutex must be locked by the caller before calling Wait  function."
//  m_wxmutex.Lock() ;
//  //Waits until m_wxcondition.Signal() or m_wxcondition.Broadcast() is called
//  // (by another thread).
//  m_wxcondition.Wait() ;
//}
//
//void wxConditionBasedI_Condition::LockedBroadcast()
//{
//  wxMutexLocker mlocker( m_wxmutex) ;
//  m_wxcondition.Broadcast() ;
//}
//
//wxCondError wxConditionBasedI_Condition::Signal()
//{
//  return m_wxcondition.Signal() ;
//}
//
//wxCondError wxConditionBasedI_Condition::Wait()
//{
//  //Waits until m_wxcondition.Signal() or m_wxcondition.Broadcast() is called
//  // (by another thread).
//  return m_wxcondition.Wait() ;
//}
