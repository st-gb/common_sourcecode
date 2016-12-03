/*
 * I_Event.hpp
 *
 *  Created on: 28.08.2010
 *      Author: sgebauer
 */

#ifndef I_EVENT_HPP_
#define I_EVENT_HPP_

//see http://en.wikipedia.org/wiki/Event_%28synchronization_primitive%29:
//"An event is an abstract data type with a boolean state and the following operations:
//
//    * wait - when executed, causes the executing process to suspend until the event's state is set to true. If the state is already set to true has no effect.
//    * set - sets the event's state to true, release all waiting processes.
//    * clear - sets the event's state to false."
class I_Event
{
  void Clear() ;
  void Set() ;
  void Wait() ;
};

#endif /* I_EVENT_HPP_ */
