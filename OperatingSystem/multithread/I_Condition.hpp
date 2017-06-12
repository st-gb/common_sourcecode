/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany
 * ("Trilobyte SE") 2010-at least 2012.
 * You are allowed to modify and use the source code from Trilobyte SE for free
 * if you are not making profit directly or indirectly with it or its adaption.
 * Else you may contact Trilobyte SE. */
/*
 * I_Condition.hpp
 *
 *  Created on: Jun 13, 2010
 *      Author: Stefan
 */

#ifndef I_CONDITION_HPP_
#define I_CONDITION_HPP_

#include <hardware/CPU/fastest_data_type.h>//typedef fastestUnsignedDataType

/** @ see http://en.wikipedia.org/wiki/Virtual_method_table
 * using the Virtual_method_table it is slower: 
 * http://en.wikipedia.org/wiki/Virtual_method_table#Efficiency
 *  "A virtual call requires at least an extra indexed dereference, 
 *  and sometimes a "fixup" addition, compared to a non-virtual call, 
 *  which is simply a jump to a compiled-in pointer. 
 *  Therefore, calling virtual functions is inherently slower than calling 
 *  non-virtual functions" */
#define USE_VIRTUAL_METHODS

#ifdef USE_VIRTUAL_METHODS
  #define VIRTUALITITY virtual
#else
  #define VIRTUALITITY
#endif

class I_Condition
{
  public:
//    //define, else "undefined reference to `vtable for I_Condition'"
//    virtual ~I_Condition() {};
//    enum WaitTimeOut_state { signaled = 0, timed_out, wait_failed, wait_abandoned, other_error};
    enum state { success = 0, signaled, timed_out, wait_failed, wait_abandoned, other_error};
    //http://en.wikipedia.org/wiki/Monitor_%28synchronization%29
    // #Waiting_and_signaling:
    //"Thus there are two main operations on condition variables:
  //  * wait c is called by a thread that needs to wait until the assertion Pc is
  //    true before proceeding. While the thread is waiting, it does not occupy
  //    the monitor.
  //  * signal c (sometimes written as notify c) is called by a thread to
  //    indicate that the assertion Pc is true.
#ifdef USE_VIRTUAL_METHODS
    VIRTUALITITY I_Condition::state Broadcast() = 0;// {}
    VIRTUALITITY I_Condition::state Wait() = 0; //{}
    VIRTUALITITY I_Condition::state WaitTimeOut(fastestUnsignedDataType 
      dwMilliSecondsToWait) = 0;//{};
#endif
} ;

#endif /* I_CONDITION_HPP_ */
