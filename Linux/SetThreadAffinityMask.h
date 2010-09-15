/*
 * SetThreadAffinityMask.h
 *
 *  Created on: 30.08.2010
 *      Author: sgebauer
 */

#ifndef LINUX_SETTHREADAFFINITYMASK_H_
  #define LINUX_SETTHREADAFFINITYMASK_H_

  #include <sched.h> //sched_setaffinity(...)
//  #include <windef.h> //DWORD

  //Use inline->faster, avoid g++ error/ warning
  inline unsigned long int SetThreadAffinityMask(//DWORD
    unsigned long dwThreadAffinityMask)
  {
//    cpu_set_t * cpu_set_tAffinityMask ;
    //TODO check if it is working
    return
      //Invert return value
      !
      //Cites from http://www.kernel.org/doc/man-pages/online/pages/man2/
      // sched_setaffinity.2.html:
      //"On success, sched_setaffinity() and sched_getaffinity() return 0.
      //On error, -1 is returned, and errno is set appropriately."
      sched_setaffinity(
        //"If pid is zero, then the calling process is used."
        0
        //"The argument cpusetsize is the length (in bytes) of the data
        // pointed to by mask"
        //"Normally this argument would be specified as sizeof(cpu_set_t)."
        //sizeof(cpu_set_t)
        , sizeof(//DWORD
          unsigned long)
        , dwThreadAffinityMask
        ) ;
//    return 1 ;
  }

#endif /* LINUX_SETTHREADAFFINITYMASK_H_ */
