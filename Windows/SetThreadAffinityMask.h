/*
 * SetThreadAffinityMask.h
 *
 *  Created on: Aug 14, 2010
 *      Author: Stefan
 */

#ifndef SETTHREADAFFINITYMASK_H_WINDOWS_
#define SETTHREADAFFINITYMASK_H_WINDOWS_

  #include <windows.h> //SetThreadAffinityMask

  //Use inline->faster, avoid g++ error/ warning
  inline unsigned long int SetThreadAffinityMask(DWORD dwThreadAffinityMask)
  {
    return
      //http://msdn.microsoft.com/en-us/library/ms686247%28VS.85%29.aspx:
      //"If the function fails, the return value is zero."
      ::SetThreadAffinityMask( ::GetCurrentThread() ,
        dwThreadAffinityMask) ;
  }

#endif /* SETTHREADAFFINITYMASK_H_WINDOWS_ */
