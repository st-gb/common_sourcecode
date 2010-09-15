/*
 * GetLastErrorCode.hpp
 *
 *  Created on: Sep 9, 2010
 *      Author: Stefan
 */

#ifndef GETLASTERRORCODE_HPP_
#define GETLASTERRORCODE_HPP_

//Make the function inline because it includes just 1 instruction-> we would
// nit save space in the exe if it was a real function with a call stack.
inline DWORD GetLastErrorCode()
{
  return ::GetLastError() ;
}

#endif /* GETLASTERRORCODE_HPP_ */
