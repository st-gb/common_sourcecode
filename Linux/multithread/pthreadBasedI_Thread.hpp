/*
 * pthreadBasedI_Thread.hpp
 *
 *  Created on: Oct 12, 2010
 *      Author: sgebauer
 */

#ifndef PTHREADBASEDI_THREAD_HPP_
#define PTHREADBASEDI_THREAD_HPP_

#include <Controller/multithread/I_Thread.hpp> //class I_Thread
//#include <bits/pthreadtypes.h> //pthread_t
#include <pthread.h> //pthread_t

namespace Linux
{

  class pthreadBasedI_Thread
    : public I_Thread
  {
    I_Thread::thread_type m_i_thread_thread_type ;
    pthread_t m_pthread_t ;
  public:
    pthreadBasedI_Thread(I_Thread::thread_type = I_Thread::joinable );
    virtual
    ~pthreadBasedI_Thread();
    BYTE start(pfnThreadFunc, void * p_v ) ;
    inline void * WaitForTermination() ;
  };

}

#endif /* PTHREADBASEDI_THREAD_HPP_ */
