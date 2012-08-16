/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany
 * ("Trilobyte SE") 2010-at least 2012.
 * You are allowed to modify and use the source code from Trilobyte SE for free
 * if you are not making profit directly or indirectly with it or its adaption.
 * Else you may contact Trilobyte SE. */
/*
 * Thread.h
 *
 *  Created on: Jul 16, 2010
 *      Author: Stefan
 */

#ifndef THREAD_HPP_
#define THREAD_HPP_

#include <Controller/multithread/I_Thread.hpp>
#include <windows.h> //HANDLE

namespace Windows_API
{

  class Thread
    : public I_Thread
  {
    BYTE m_byThreadType ;
    DWORD m_dwThreadId ;
  public:
    HANDLE m_handleThread ;
    Thread()
      : m_handleThread( NULL )
    {
    }
    Thread( BYTE byThreadType );
    virtual
    ~Thread();

    void Delete() {} ;
    bool IsRunning()
    {
      //http://msdn.microsoft.com/en-us/library/windows/desktop/ms686724%28v=vs.85%29.aspx:
      //"Terminating a thread has the following results:"
      //  "The thread object is signaled."
      DWORD dw = ::WaitForSingleObject(m_handleThread, 0);
      //if running: WAIT_TIMEOUT when WaitForSingleObject(),
      return dw
//        //"The state of the specified object is signaled."->thread terminated.
//        != WAIT_OBJECT_0;
        == WAIT_TIMEOUT;
    }
    inline void PossiblyCloseThreadHandle();
    BYTE start( pfnThreadFunc, void * p_v ) ;
    void * WaitForTermination() ;
  };
}

#endif /* THREAD_HPP_ */
