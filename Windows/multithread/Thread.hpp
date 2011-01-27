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
    HANDLE m_handleThread ;
  public:
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
