/*
 * SetThreadAffinityMask.h
 *
 *  Created on: 30.08.2010
 *      Author: sgebauer
 */

#ifndef LINUX_SETTHREADAFFINITYMASK_H_
  #define LINUX_SETTHREADAFFINITYMASK_H_

  #include <sched.h> //sched_setaffinity(...)
  #include <preprocessor_macros/logging_preprocessor_macros.h> //DEBUGN(...)
//  #include <windef.h> //DWORD

namespace Linux
{
  /** Use inline->faster, avoid g++ error/ warning */
  inline unsigned long int SetThreadAffinityMask(//DWORD
    unsigned long dwThreadAffinityMask)
  {
    DEBUGN("inline unsigned long int SetThreadAffinityMask(...) begin")
    //see http://www.kernel.org/doc/man-pages/online/pages/man3/CPU_SET.3.html,
    // section "EXAMPLE"
//    static cpu_set_t * p_cpu_set_tAffMask = {;
//    cpu_set_tAffMask = CPU_ALLOC(num_cpus);
//    cpu_set_t * cpu_set_tAffinityMask ;
    //TODO check if it is working
    /** Cites from http://www.kernel.org/doc/man-pages/online/pages/man2/sched_setaffinity.2.html
     *  : "On success, sched_setaffinity() and sched_getaffinity() return 0.
     *     On error, -1 is returned, and errno is set appropriately." */
    static int nReturnValue;
    nReturnValue = sched_setaffinity(
        //"If pid is zero, then the calling process is used."
        0
        //"The argument cpusetsize is the length (in bytes) of the data
        // pointed to by mask"
        //"Normally this argument would be specified as sizeof(cpu_set_t)."
//        sizeof(cpu_set_t)
        , sizeof(//DWORD
          unsigned long)
        , //Convert to avoid Linux g++ error
        //"cannot convert ‘long unsigned int*’ to ‘const cpu_set_t*’ for
        //argument ‘3’ to ‘int sched_setaffinity(__pid_t, size_t,
        //const cpu_set_t*)’"
          (__const cpu_set_t *)
          & dwThreadAffinityMask // __const cpu_set_t *__cpuset
        ) ;
//    return 1 ;
    if( ! nReturnValue)
      return dwThreadAffinityMask;
    return 0;
//      //Invert return value
//      ! nReturnValue;
  }
}//namespace Linux

#endif /* LINUX_SETTHREADAFFINITYMASK_H_ */
