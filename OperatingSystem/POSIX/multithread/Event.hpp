/** File: Event.hpp
 * Author: Stefan Gebauer, M.Sc. Comp.Sc.
 * Created on 3. Mai 2017, 21:26 */

#ifndef EVENT_HPP
#define EVENT_HPP

#include <OperatingSystem/multithread/I_Condition.hpp> //base class I_Condition
#include <pthread.h>///pthread_mutex_t, pthread_cond_t
#include <hardware/CPU/fastest_data_type.h>///fastestUnsignedDataType

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
  I_Condition::state WaitTimeOut(const fastestUnsignedDataType
    milliSecondsToWait)
    { return other_error;}
  I_Condition::state WaitForSignalOrTimeoutInMs(const fastestUnsignedDataType);
  private:
    pthread_mutex_t m_mutex;
    pthread_cond_t m_condition;
  };
}

#endif /* EVENT_HPP */

