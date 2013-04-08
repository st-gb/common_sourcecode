/*
 * GetLastErrorCode.hpp
 *
 *  Created on: Sep 9, 2010
 *      Author: Stefan
 */

#ifndef GETLASTERRORCODE_HPP_
#define GETLASTERRORCODE_HPP_

#include <errno.h> //for "errno"



//Make the function inline (->no function overhead/ call stack->faster)
//because it includes just 1 instruction->we would not save space in the exe
//if it was a real function with a call stack.
inline /*DWORD*/ unsigned long int GetLastErrorCode()
{
  return errno ;
}

#endif /* GETLASTERRORCODE_HPP_ */
