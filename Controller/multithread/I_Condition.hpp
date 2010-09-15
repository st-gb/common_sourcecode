/*
 * I_Condition.hpp
 *
 *  Created on: Jun 13, 2010
 *      Author: Stefan
 */

#ifndef I_CONDITION_HPP_
#define I_CONDITION_HPP_

class I_Condition
{
  public:
  //http://en.wikipedia.org/wiki/Monitor_%28synchronization%29
  // #Waiting_and_signaling:
  //"Thus there are two main operations on condition variables:
//  * wait c is called by a thread that needs to wait until the assertion Pc is
//    true before proceeding. While the thread is waiting, it does not occupy
//    the monitor.
//  * signal c (sometimes written as notify c) is called by a thread to
//    indicate that the assertion Pc is true.
  void Broadcast() {}
  void Wait() {}
} ;

#endif /* I_CONDITION_HPP_ */
