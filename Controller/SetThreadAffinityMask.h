/*
 * SetThreadAffinityMask.h
 *
 *  Created on: Aug 14, 2010
 *      Author: Stefan
 */

#ifndef SETTHREADAFFINITYMASK_H_
#define SETTHREADAFFINITYMASK_H_

#include <preprocessor_macros/determine_OS.h>

#ifdef _WIN32 //Built-in preprocessor macro for MSVC, MinGW (also for 64 bit)
  #include <Windows/SetThreadAffinityMask.h>
#endif
#ifdef __linux__
  #include <OperatingSystem/Linux/SetThreadAffinityMask.h>
#endif

namespace OperatingSystem
{
  inline unsigned long int SetThreadAffinityMask(//DWORD
    unsigned long dwThreadAffinityMask)
  {
#ifdef __linux__
    return Linux::SetThreadAffinityMask(dwThreadAffinityMask);
#endif
  }
}

#endif /* SETTHREADAFFINITYMASK_H_ */
