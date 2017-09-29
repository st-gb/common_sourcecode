/** File:   Event.hpp
 * Author: sg
 * Created on 3. Mai 2017, 21:26  */

#ifndef EVENT_HPP
#define EVENT_HPP

#include <OperatingSystem/multithread/I_Condition.hpp> //base class I_Condition
#include <pthread.h> //

namespace pthread
{
  class Condition
    : public I_Condition
  {
  public:
    Condition();
    Condition(const Condition& orig);
    virtual ~Condition();

    I_Condition::state Wait();
    I_Condition::state Broadcast();
    I_Condition::state WaitTimeOut(fastestUnsignedDataType dwMilliSecondsToWait) { return other_error;}
  private:
    pthread_mutex_t m_mutex;
    pthread_cond_t m_condition;
  };
}

#endif /* EVENT_HPP */

