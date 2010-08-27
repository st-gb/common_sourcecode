/*
 * wxConditionBasedI_Condition.hpp
 *
 *  Created on: Jun 13, 2010
 *      Author: Stefan
 */

#ifndef WXCONDITIONBASEDI_CONDITION_HPP_
#define WXCONDITIONBASEDI_CONDITION_HPP_

#include <wx/thread.h> //for class wxCondition

class wxConditionBasedI_Condition
{
public:
  wxMutex m_wxmutex ;
  wxCondition m_wxcondition ;

//  inline wxConditionBasedI_Condition() ;
//  inline wxCondError Broadcast() ;
//  inline void LockedBroadcast() ;
//  inline wxMutexError Lock() ;
//  inline void LockAndWait() ;
//  inline wxCondError Signal() ;
//  inline wxCondError Wait() ;

  //The implementations of the functions must be inside the class, else if in
  //the .cpp file they are not inline.
  //(this is because if #including a file its whole content is inserted, but
  // cpp files usually are not being included?!)
  wxConditionBasedI_Condition()
    : m_wxcondition (m_wxmutex)
  {

  }
  wxCondError Broadcast()
  {
    return m_wxcondition.Broadcast() ;
  }
  void LockedBroadcast()
  {
    wxMutexLocker mlocker( m_wxmutex) ;
    m_wxcondition.Broadcast() ;
  }
  wxMutexError Lock()
  {
    return m_wxmutex.Lock() ;
  }
  void LockAndWait()
  {
    //http://docs.wxwidgets.org/stable/wx_wxcondition.html#wxconditionctor:
    //"The mutex must be locked by the caller before calling Wait  function."
    m_wxmutex.Lock() ;
    //Waits until m_wxcondition.Signal() or m_wxcondition.Broadcast() is called
    // (by another thread).
    m_wxcondition.Wait() ;
  }
  wxCondError Signal()
  {
    return m_wxcondition.Signal() ;
  }
  wxCondError Wait()
  {
    //Waits until m_wxcondition.Signal() or m_wxcondition.Broadcast() is called
    // (by another thread).
    return m_wxcondition.Wait() ;
  }
};

#endif /* WXCONDITIONBASEDI_CONDITION_HPP_ */