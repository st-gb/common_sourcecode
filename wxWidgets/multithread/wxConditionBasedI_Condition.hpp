/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany
 * ("Trilobyte SE") 2010-at least 2012.
 * You are allowed to modify and use the source code from Trilobyte SE for free
 * if you are not making profit directly or indirectly with it or its adaption.
 * Else you may contact Trilobyte SE. */
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
#include <OperatingSystem/multithread/I_Condition.hpp> //base class I_Condition

class wxConditionBasedI_Condition
  : public I_Condition
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
  /** By "virtual" : avoid g++ warning: "`class wxConditionBasedI_Condition' has
  * virtual functions but non-virtual destructor" */
  virtual ~wxConditionBasedI_Condition()
  {
    //WARNING Only output when the logger object is not destroyed before!
//    LOGN("~wxConditionBasedI_Condition()")
  }
  static I_Condition::state wxCondError2I_Condition_state(wxCondError wxconderror)
  {
    I_Condition::state i_condition_state = I_Condition::other_error;
    switch(wxconderror)
    {
      case wxCOND_NO_ERROR:
        //"Returns wxCOND_NO_ERROR if the condition was signalled"
        i_condition_state = I_Condition::signaled;
        break;
      case wxCOND_TIMEOUT:
        //"wxCOND_TIMEOUT if the timeout elapsed"
        i_condition_state = I_Condition::timed_out;
        break;
      case wxCOND_INVALID:
      case wxCOND_MISC_ERROR:
        i_condition_state = I_Condition::other_error;
        break;
    }
    return i_condition_state;
  }
  I_Condition::state Broadcast()
  {
#ifdef COMPILE_WITH_LOG
    wxCondError wxconderrorBroadcast = m_wxcondition.Broadcast() ;
    if( // <> wxCOND_NO_ERROR
        wxconderrorBroadcast )
      LOGN("wxConditionBasedI_Condition::Broadcast(): error code:"
        << wxconderrorBroadcast )
    return wxCondError2I_Condition_state(wxconderrorBroadcast) ;
#else
    return m_wxcondition.Broadcast() ;
#endif
  }
  wxCondError LockedBroadcast()
  {
    //Locking the mutex before calling Broadcast ensures that the other thread
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

  /** Sets the specified event object to the nonsignaled state. */
  void ResetEvent()
  {
    //m_wxcondition.
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

  I_Condition::state Wait()
  {
#ifdef COMPILE_WITH_LOG
    wxCondError wxconderrorWait = m_wxcondition.
      //http://docs.wxwidgets.org/2.8/wx_wxcondition.html:
      //"Returns wxCOND_NO_ERROR on success, another value if an error occurred."
      Wait() ;
    if( // <> wxCOND_NO_ERROR
        wxconderrorWait )
      LOGN("wxConditionBasedI_Condition::Wait(): error code:"
        << wxconderrorWait )
    else
      LOGN("wxConditionBasedI_Condition::Wait(): success")
    return wxCondError2I_Condition_state(wxconderrorWait);
#else
    //Waits until m_wxcondition.Signal() or m_wxcondition.Broadcast() is called
    // (by another thread).
    return m_wxcondition.Wait() ;
#endif
  }
  /** Overrides I_condition.WaitTimeout(...)  */
  I_Condition::state WaitTimeOut(fastestUnsignedDataType dwMilliSecondsToWait)
  {
    wxCondError wxconderrorWait = m_wxcondition.WaitTimeout(
      dwMilliSecondsToWait);
    return wxCondError2I_Condition_state(wxconderrorWait);
  }
};

#endif /* WXCONDITIONBASEDI_CONDITION_HPP_ */
