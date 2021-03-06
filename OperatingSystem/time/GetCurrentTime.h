#pragma once

#ifdef _WIN32
  #include <windows.h> //for SYSTEMTIME, GetLocalTime(SYSTEMTIME)
  #include <time.h> //struct tm
  #ifdef GetCurrentTime /**  <winbase.h> : #define GetTickCount() GetCurrentTime()  */
    #undef GetCurrentTime
  #endif

  /** Version for the "C" programming language. */
  inline void GetCurrentTime(struct tm * tm_Current)
  {
    //static 
    SYSTEMTIME s_systemtime ;
  
    /** Gets the same time as the Windows clock. */
    ::GetLocalTime( & s_systemtime );
    tm_Current->tm_sec = s_systemtime.wSecond;
    tm_Current->tm_min = s_systemtime.wMinute;
    tm_Current->tm_hour = s_systemtime.wHour;
  }
#endif

#if defined( __unix__) //|| defined (__ANDROID__)
#include <sys/time.h> //gettimeofday
#include <string.h> //memcpy(...)

  inline void GetCurrentTime(struct tm * p_tm_Current)
  {
    static timeval timevalCurrentTime ;
    //see http://stackoverflow.com/questions/588307/c-obtaining-milliseconds-time-on-linux-clock-doesnt-seem-to-work-properly
    // answered Feb 25 '09 at 23:18 by "Jason Punyon"
    static struct tm * p_tm ;
    
    //from http://www.gamedev.net/community/forums/topic.asp?topic_id=437062
    //("best way to GetTickCount in Linux") :
    // / http://www.linuxquestions.org/questions/programming-9/c-c-api-for-retrieving-system-time-in-micro-or-milliseconds-441519/
    ::gettimeofday( & timevalCurrentTime,0);
    //see http://www.unix.com/programming/1991-time-microseconds.html
    //  submitted by "Perderabo" on 09-04-2001 :
    p_tm = ::localtime( & timevalCurrentTime.tv_sec ) ;
    /** http://www.cplusplus.com/reference/ctime/localtime/ :
    * "The returned value points to an internal object whose validity or value 
    *  may be altered by any subsequent call to gmtime or localtime."
    *  -> So make a copy. */
    ::memcpy(p_tm_Current, p_tm, sizeof(struct tm) );
  }
#endif
