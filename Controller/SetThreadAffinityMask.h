/*
 * SetThreadAffinityMask.h
 *
 *  Created on: Aug 14, 2010
 *      Author: Stefan
 */

#ifndef SETTHREADAFFINITYMASK_H_
#define SETTHREADAFFINITYMASK_H_

#include <preprocessor_macros/determine_OS.h>

#ifdef _WINDOWS
  #include <windows.h> //SetThreadAffinityMask

  unsigned long int SetThreadAffinityMask(DWORD dwThreadAffinityMask)
  {
    return
    //http://msdn.microsoft.com/en-us/library/ms686247%28VS.85%29.aspx:
    //"If the function fails, the return value is zero."
    ::SetThreadAffinityMask( ::GetCurrentThread() ,
      dwThreadAffinityMask) ;
  }
#endif

#endif /* SETTHREADAFFINITYMASK_H_ */
