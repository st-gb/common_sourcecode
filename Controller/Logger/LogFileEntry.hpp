/*
 * LogFileEntry.hpp
 *
 *  Created on: 29.04.2012
 *      Author: Stefan
 */

#ifndef LOGFILEENTRY_HPP_
#define LOGFILEENTRY_HPP_

typedef unsigned char BYTE;

class LogFileEntry
{
  //All time members need to have the same data type for unified access
  //( to not access beyond the space for a data type ) to node members of a
  //NodeTrie.
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
  uint16_t nanosecond;
  std::string * p_std_strMessage;
};

#endif /* LOGFILEENTRY_HPP_ */
