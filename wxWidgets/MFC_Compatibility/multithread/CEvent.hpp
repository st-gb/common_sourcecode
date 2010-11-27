#pragma once

#include <wx/thread.h> //for wxCondition
//#include <wx/thrimpl.cpp> //for wxCondition
#include <preprocessor_macros/logging_preprocessor_macros.h> //LOGN(...)

namespace MFC_Compatibility
{
  class CEvent
//    : public
//    //"wxCondition" and NOT "wxEvent" is the correspondant to MFC's "CEvent"
//    //http://docs.wxwidgets.org/stable/wx_wxcondition.html#wxconditionwait:
//    //"wxCondition variables correspond to pthread conditions or to Win32 event objects."
//    wxCondition
  {
  protected:
    //Do not derive this class from wxCondition because this causes problems
    //like its member variable "wxConditionInternal" is not being inherited.
    //So better/ simply use a member of this class.
    wxCondition m_wxcondition ;
//    //Declare here because "m_internal" isn't inherited from wxCondition
//    //because it is private there.
//    wxConditionInternal * m_internal;
  public:
    wxMutex m_mutex ;
    CEvent()
      :
//      wxCondition(m_mutex)
      m_wxcondition(m_mutex)
    {
//      //From wxWidgets' source file "include/wx/thrimpl.cpp" :
//      m_internal = new wxConditionInternal(m_mutex);
//
//      if ( !m_internal->IsOk() )
//      {
//          delete m_internal;
//          m_internal = NULL;
//      }
    }
    ~CEvent()
    {
//      //From wxWidgets' source file "include/wx/thrimpl.cpp" :
//      delete m_internal;
    }
    void ResetEvent()
    {
      
    }
    //http://msdn.microsoft.com/de-de/library/5sw81wy1(VS.80).aspx 
    //(CEvent.SetEvent()):
    //"Sets the state of the event to signaled, releasing any waiting threads."
    inline BOOL SetEvent()
    {
      LOGN("MFC_Compatibility::CEvent::SetEvent() begin")
      //http://docs.wxwidgets.org/stable/wx_wxcondition.html#wxconditionsignal: 
      //"Signals the object waking up at most one thread."
//      Signal() ;
      m_wxcondition.
        //Calling wxCondition::Signal() causes a debug alert: "m_internal"
        // not initialized.
        Signal() ;
      LOGN("MFC_Compatibility::CEvent::SetEvent() before \"return TRUE\"")
      return TRUE ;
    }
  };
}
