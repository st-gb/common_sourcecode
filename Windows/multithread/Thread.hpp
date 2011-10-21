/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */
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
    void Delete() {} ;
    BYTE start( pfnThreadFunc, void * p_v ) ;
    Thread()
      : m_handleThread( NULL )
    {
    }
    Thread( BYTE byThreadType );
    virtual
    ~Thread();
    void * WaitForTermination() ;
  };

}

#endif /* THREAD_HPP_ */
