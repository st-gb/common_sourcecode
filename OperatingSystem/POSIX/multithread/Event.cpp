/** File: Event.cpp
 * Author: Stefan Gebauer, M. Sc. Comp.Sc.
 * Created on 3. Mai 2017, 21:26 */

#include "Event.hpp"
#include <errno.h>///ETIMEDOUT

namespace pthread
{
Condition::Condition()
//  : m_mutex(PTHREAD_MUTEX_INITIALIZER)
//    , m_condition(PTHREAD_COND_INITIALIZER)
{
  pthread_cond_init(& m_condition, NULL);
  pthread_mutex_init(& m_mutex, NULL);
}

Condition::Condition(const Condition& orig) {
}

Condition::~Condition() {
  pthread_cond_destroy( & m_condition);
  pthread_mutex_destroy(& m_mutex);
}

I_Condition::state Condition::Broadcast()
{
  /** https://linux.die.net/man/3/pthread_mutex_lock :
   *  "If successful, the pthread_mutex_lock() and pthread_mutex_unlock()
   *  functions shall return zero" */
  const int lockResult = pthread_mutex_lock(& m_mutex);
  /** https://linux.die.net/man/3/pthread_cond_broadcast :
   *  "If successful, the pthread_cond_broadcast() and pthread_cond_signal() functions shall return
   *   zero" */
  const int broadcastResult = pthread_cond_broadcast( & m_condition);
  /** https://linux.die.net/man/3/pthread_mutex_unlock :
   *  "If successful, the pthread_mutex_lock() and pthread_mutex_unlock()
   *  functions shall return zero" */
  const int unlockResult = pthread_mutex_unlock(& m_mutex);
  return lockResult == broadcastResult == unlockResult == 0 ? success :
    other_error;
}

I_Condition::state Condition::WaitForSignalOrTimeoutInMs(const
  fastestUnsignedDataType ms)
{
  timespec ts;
  __syscall_slong_t remainingNs = ms % 1000 * 1000000/** To nanoseconds*/;
  clock_gettime(CLOCK_REALTIME, &ts);
//  timespec ts{ms/1000, remainingNs};
  ts.tv_sec += ms/1000;
  ts.tv_nsec += remainingNs;
  
  const int lockResult =
    /** https://linux.die.net/man/3/pthread_cond_timedwait :
     * "They shall be called with mutex locked by the calling thread or
     *  undefined behavior results." */
    pthread_mutex_lock(& m_mutex);
  const int retVal =
    /** https://linux.die.net/man/3/pthread_cond_timedwait :
     * "These functions atomically release mutex and cause the calling thread to
     * block on the condition variable cond; atomically here means "atomically
     * with respect to access by another thread to the mutex and then the
     * condition variable"." */
    pthread_cond_timedwait(&m_condition, &m_mutex,
      /// "system time equals or exceeds abstime."
      &ts);
  const int unlockResult = pthread_mutex_unlock(& m_mutex);//TODO:neccessary?
  if(retVal == 0)
    return I_Condition::success;
  else
  switch(retVal){
    /** https://linux.die.net/man/3/pthread_cond_timedwait :
     *"The time specified by abstime to pthread_cond_timedwait() has passed." */
   case ETIMEDOUT:
    return I_Condition::timed_out;
  }
  return I_Condition::other_error;
}

I_Condition::state Condition::Wait()
{
  /** https://linux.die.net/man/3/pthread_cond_wait :
   *  "They shall be called with mutex locked by the calling thread or 
   *   undefined behavior results."  */
  const int lockResult = pthread_mutex_lock(& m_mutex);
  /** https://linux.die.net/man/3/pthread_cond_wait : 
   *  "These functions atomically release mutex and cause the calling thread 
   *  to block on the condition variable cond" */
  const int waitResult = pthread_cond_wait( & m_condition, & m_mutex );
  const int unlockResult = pthread_mutex_unlock(& m_mutex);
  return lockResult == waitResult == unlockResult == 0 ? success : other_error;
}
}
