/** File:   Event.cpp
 * Author: sg
 * Created on 3. Mai 2017, 21:26 */

#include "Event.hpp"

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
