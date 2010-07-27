/*
 * Win32EventBasedCondition.hpp
 *
 *  Created on: Jun 13, 2010
 *      Author: Stefan
 */

#ifndef WIN32EVENTBASEDCONDITION_HPP_
#define WIN32EVENTBASEDCONDITION_HPP_

#include <windows.h> //for HANDLE

  class Win32EventBasedCondition
  {
    HANDLE m_handleEvent ;
  public :
    Win32EventBasedCondition() ;
    ~Win32EventBasedCondition() ;

    void Broadcast() ;
    void ResetEvent() ;
    void Wait() ;
  };

#endif /* WIN32EVENTBASEDCONDITION_HPP_ */
