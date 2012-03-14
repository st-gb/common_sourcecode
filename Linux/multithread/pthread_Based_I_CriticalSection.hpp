/*
 * pthread_Based_I_CriticalSection.hpp
 *
 *  Created on: Jan 16, 2012
 *      Author: sgebauer
 */

#ifndef PTHREAD_BASED_I_CRITICALSECTION_HPP_
#define PTHREAD_BASED_I_CRITICALSECTION_HPP_

#include <Controller/multithread/I_CriticalSection.hpp>
//Code from http://en.wikipedia.org/wiki/Critical_section#Application_Level_Critical_Sections
#include <pthread.h>

class pthread_Based_I_CriticalSection
  : public I_CriticalSection
{
  pthread_mutex_t m_cs_mutex;
public:
  pthread_Based_I_CriticalSection()
  {
    //m_cs_mutex = PTHREAD_MUTEX_INITIALIZER;
    //from https://computing.llnl.gov/tutorials/pthreads/#MutexCreation:
    pthread_mutex_init( & m_cs_mutex, NULL);
  }
  ~pthread_Based_I_CriticalSection()
  {
    pthread_mutex_destroy( & m_cs_mutex);
  }
  void Enter() { pthread_mutex_lock( & m_cs_mutex ); }
  void Leave() { pthread_mutex_unlock( & m_cs_mutex ); }
};

#endif /* PTHREAD_BASED_I_CRITICALSECTION_HPP_ */
