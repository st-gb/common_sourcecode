/*
 * GetTickCount.hpp
 *
 *  Created on: Sep 15, 2010
 *      Author: Stefan
 */

#ifndef GETTICKCOUNT_HPP_
#define GETTICKCOUNT_HPP_

  #include <sys/time.h> // gettimeofday(...)
//  #include <windef.h> //DWORD

  typedef unsigned long DWORD ;

  inline DWORD GetTickCount()
  {
    //Static:don't create on stack each time (global variable with local scope)
    static DWORD dwReturnValue ;
    static timeval timevalCurrentTime ;
    //TODO
    //from http://en.wikipedia.org/wiki/System_time#Operating_systems:
    //see http://www.opengroup.org/onlinepubs/9699919799/functions/gettimeofday.html:
    // "Applications should use the clock_gettime() function instead of the
    //  obsolescent gettimeofday() function."
//    struct timeval * restrict tp;
//    void *restrict tzp ;
//    gettimeofday(tp, void *restrict tzp);
    //from http://www.gamedev.net/community/forums/topic.asp?topic_id=437062:
    gettimeofday(
      //http://www.gamedev.net/community/forums/topic.asp?topic_id=524616:
      //Problem: when the system time is changed, the "tick count" is wrong.
      & timevalCurrentTime,0);
    //from http://www.gamedev.net/community/forums/topic.asp?topic_id=437062:
//    timeval ts;
//    gettimeofday(&ts,0);
//    lGetTickCount = (INT64)(ts.tv_sec * 1000 + (ts.tv_usec / 1000));
    return
      //seconds to milliseconds
      timevalCurrentTime.tv_sec * 1000 +
      //Microseconds to milliseconds
      timevalCurrentTime.tv_usec / 1000 ;

//    http://www.tutorials.de/c-c/239813-gnu-c-gettickcount-unter-linux.html
//    #include <sys/sysinfo.h>
//    long getTickCount() // Zeit seit dem Booten in Sekunden
//    {
//     struct sysinfo si;
//     if(sysinfo(&si) == 0) return si.uptime;
//     else return -1L;
//    }
  }

#endif /* GETTICKCOUNT_HPP_ */
