/*
 * GetLastErrorCode.hpp
 *
 *  Created on: Sep 9, 2010
 *      Author: Stefan
 */

#ifndef GETLASTERRORCODE_HPP_
#define GETLASTERRORCODE_HPP_

#include <windows.h> //::GetLastError()
#include <windef.h> //DWORD

namespace OperatingSystem //Windows_API
{
  /** Make the function inline because it includes just 1 instruction-> we would
  * not save space in the executable if it was a real function with a call stack. */
  inline DWORD GetLastErrorCode()
  {
    return ::GetLastError() ;
  }
}

#endif /* GETLASTERRORCODE_HPP_ */
