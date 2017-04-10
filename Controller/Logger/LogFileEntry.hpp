/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany
 * ("Trilobyte SE") 2010-at least 2012.
 * You are allowed to modify and use the source code from Trilobyte SE for free
 * if you are not making profit directly or indirectly with it or its adaption.
 * Else you may contact Trilobyte SE. */
/*  LogFileEntry.hpp
 *  Created on: 29.04.2012
 *  Author: Stefan  */

#ifndef LOGFILEENTRY_HPP_
#define LOGFILEENTRY_HPP_

typedef unsigned char BYTE;
#include <stdint.h> //uint16_t

//namespace CSS
//{
class LogFileEntry
{
  /** All time members need to have the same data type for unified access
  * ( to not access beyond the space for a data type ) to node members of a
  * NodeTrie. */
  typedef uint16_t datatype_for_1_byte_numbers ;
public:
  uint16_t threadID; //0-2^16 numbers -> needs at least 2 bytes
  uint16_t year; //data type need to have at least 2 bytes.
  datatype_for_1_byte_numbers month;
  datatype_for_1_byte_numbers day;
  datatype_for_1_byte_numbers hour;
  datatype_for_1_byte_numbers minute;
  datatype_for_1_byte_numbers second;
  uint16_t millisecond;
  uint16_t microsecond;
  uint16_t nanosecond;
  //TODO make private for not be inherited to subclass
  std::string * p_std_strMessage;
  const std::string * p_std_strThreadName;
//  LogFileEntry() : p_std_strThreadName(p_std_strThreadName) {  }
};
//}

#endif /* LOGFILEENTRY_HPP_ */
