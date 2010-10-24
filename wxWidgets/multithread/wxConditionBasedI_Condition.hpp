/*
 * wxConditionBasedI_Condition.hpp
 *
 *  Created on: Jun 13, 2010
 *      Author: Stefan
 */

#ifndef WXCONDITIONBASEDI_CONDITION_HPP_
#define WXCONDITIONBASEDI_CONDITION_HPP_

#include <wx/thread.h> //for class wxCondition
#include <preprocessor_macros/logging_preprocessor_macros.h> //LOGN(...)

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
  ~wxConditionBasedI_Condition()
  {
    LOGN("~wxConditionBasedI_Condition()")
  }
  wxCondError Broadcast()
  {
#ifdef COMPILE_WITH_LOG
    wxCondError wxconderrorBroadcast = m_wxcondition.Broadcast() ;
    if( // <> wxCOND_NO_ERROR
        wxconderrorBroadcast )
      LOGN("wxConditionBasedI_Condition::Broadcast(): error code:"
        << wxconderrorBroadcast )
    return wxconderrorBroadcast ;
#else
    return m_wxcondition.Broadcast() ;
#endif
  }
  wxCondError LockedBroadcast()
  {
    //Lockimg the mutex before calling Broadcast ensures that the other thread
    //is _really_ waiting on the condition (because it unlocks the mutex then)
    //when calling Broadcast() ;

    //A mutex locker at first locks the mutex and unlocks it in its destructor.
    //Unlocking is important for "wxCondition::Wait()" to return.
    wxMutexLocker mlocker( m_wxmutex) ;
    return m_wxcondition.Broadcast() ;
  }
  wxMutexError Lock()
  {
#ifdef COMPILE_WITH_LOG
    wxMutexError wxmutexerrorLock = m_wxmutex.Lock() ;
    if( // <> wxMUTEX_NO_ERROR
      wxmutexerrorLock )
      LOGN("wxConditionBasedI_Condition::Lock error:" << wxmutexerrorLock )
    else
      LOGN("wxConditionBasedI_Condition::Lock success")
    return wxmutexerrorLock ;
#else
    return m_wxmutex.Lock() ;
#endif
  }
  void LockAndWait()
  {
    //http://docs.wxwidgets.org/stable/wx_wxcondition.html#wxconditionctor:
    //"The mutex must be locked by the caller before calling Wait  function."
//    m_wxmutex.Lock() ;
    Lock() ;
    //Waits until m_wxcondition.Signal() or m_wxcondition.Broadcast() is called
    // (by another thread).
//    m_wxcondition.Wait() ;
    Wait() ;
  }
  wxCondError Signal()
  {
#ifdef COMPILE_WITH_LOG
    wxCondError wxconderrorSignal = m_wxcondition.Signal() ;
    if( // <> wxCOND_NO_ERROR
        wxconderrorSignal )
      LOGN("wxConditionBasedI_Condition::Signal(): error code:"
        << wxconderrorSignal )
    else
      LOGN("wxConditionBasedI_Condition::Signal(): success")
    return wxconderrorSignal ;
#else
    return m_wxcondition.Signal() ;
#endif
  }
  wxCondError Wait()
  {
#ifdef COMPILE_WITH_LOG
    wxCondError wxconderrorWait = m_wxcondition.Wait() ;
    if( // <> wxCOND_NO_ERROR
        wxconderrorWait )
      LOGN("wxConditionBasedI_Condition::Wait(): error code:"
        << wxconderrorWait )
    else
      LOGN("wxConditionBasedI_Condition::Wait(): success")
    return wxconderrorWait ;
#else
    //Waits until m_wxcondition.Signal() or m_wxcondition.Broadcast() is called
    // (by another thread).
    return m_wxcondition.Wait() ;
#endif
  }
};

#endif /* WXCONDITIONBASEDI_CONDITION_HPP_ */
