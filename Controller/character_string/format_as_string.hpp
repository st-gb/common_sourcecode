/*
 * format_as_string.hpp
 *
 *  Created on: Aug 18, 2010
 *      Author: Stefan
 */

#ifndef FORMAT_AS_STRING_HPP_
#define FORMAT_AS_STRING_HPP_
#include <string> //for class std::string

std::string format_output_data(
  const unsigned char arbyData [],
  DWORD dwByteSize,
  BYTE byCharactersPerColumn ) ;

//Use an object class like std::string instead of "char *". Advantage:
//So there is no need to care about releasing memory.
//char * getBinaryRepresentation(char arch [],unsigned long ulValue//,long size
std::string getBinaryRepresentation(unsigned long ulValue//,long size
  ) ;

#endif /* FORMAT_AS_STRING_HPP_ */
