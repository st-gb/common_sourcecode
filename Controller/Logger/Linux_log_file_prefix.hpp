/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany
 * ("Trilobyte SE") 2010-at least 2012.
 * You are allowed to modify and use the source code from Trilobyte SE for free
 * if you are not making profit directly or indirectly with it or its adaption.
 * Else you may contact Trilobyte SE. */
/*
 * Linux_log_file_prefix.hpp
 *
 *  Created on: Jul 22, 2011
 *      Author: sgebauer
 */

#ifndef LINUX_LOG_FILE_PREFIX_HPP_
#define LINUX_LOG_FILE_PREFIX_HPP_

#include <ostream> //class ostream
#include <sys/time.h> // gettimeofday(...), struct timeval
//#include <sys/types.h> //gettid()
//#include <pthread.h> //pthread_self()
#include <sys/types.h> //gettid();
#include <sys/syscall.h> //syscall(...)
#include <time.h> // localtime(...)
#include <Controller/Logger/LogFileEntry.hpp> //class LogFileEntry
#include <Controller/multithread/I_Thread.hpp> //class I_Thread
#include <Linux/GetCurrentThreadNumber.h>

//#define LOG_FILE_PREFIX()

inline void GetLogFilePrefix(LogFileEntry & r_logfileentry)
{
  //from http://www.gamedev.net/community/forums/topic.asp?topic_id=437062
  //("best way to GetTickCount in Linux") :
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

  r_logfileentry.year = p_tm->tm_year
    //The years seem to be relative to the year 1900.
    + 1900;
  r_logfileentry.month = p_tm->tm_mon
    //The 1st month (January) seems to have the index 0.
      + 1;
  r_logfileentry.day = p_tm->tm_mday;
  r_logfileentry.hour = p_tm->tm_hour;
  r_logfileentry.minute = p_tm->tm_min;
  r_logfileentry.second = p_tm->tm_sec;
  r_logfileentry.millisecond =
    //Milliseconds (10^-3 s) part = microseconds (10^-6 s) / 10^3
     //e.g. 123456 microseconds / 1000 = 123 milliseconds
    timevalCurrentTime.tv_usec / 1000;
    //Microseconds (10^-6 s) part = microseconds (10^-6 s) % 10^3
    //e.g. 123456 microseconds % 1000 = 456 microseconds
  r_logfileentry.microsecond = timevalCurrentTime.tv_usec % 1000;
  //From http://linux.die.net/man/2/gettid
//  r_logfileentry.threadID = gettid();
  //http://www.kernel.org/doc/man-pages/online/pages/man3/pthread_self.3.html
  // "link with -pthread"
  r_logfileentry.threadID = Linux::GetCurrentThreadNumber();
  I_Thread::threadNameMapType::const_iterator c_iterThreadNumber2ThreadName =
    I_Thread::s_threadNumber2Name.find(r_logfileentry.threadID);
  if( c_iterThreadNumber2ThreadName != I_Thread::s_threadNumber2Name.end() )
  {
    r_logfileentry.p_std_strThreadName = (std::string * const)
      & c_iterThreadNumber2ThreadName->second;
  }
  else
    r_logfileentry.p_std_strThreadName = NULL;
}

inline void outputLogFilePrefix(std::ostream & r_ostream)
{
  //from http://www.gamedev.net/community/forums/topic.asp?topic_id=437062
  //("best way to GetTickCount in Linux") :
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

  r_ostream
//          << timevalCurrentTime.tv_sec << "s"
    << ( p_tm->tm_year
      //The years seem to be relative to the year 1900.
      + 1900 ) << "."
    << ( p_tm->tm_mon
      //The 1st month (January) seems to have the index 0.
        + 1 ) << "."
    << p_tm->tm_mday << " "
    << p_tm->tm_hour << "h:"
    << p_tm->tm_min << "min "
    << p_tm->tm_sec << "s "
    << //Milliseconds (10^-3 s) part = microseconds (10^-6 s) / 10^3
       //e.g. 123456 microseconds / 1000 = 123 milliseconds
      timevalCurrentTime.tv_usec / 1000 << "ms "
      //Microseconds (10^-6 s) part = microseconds (10^-6 s) % 10^3
      //e.g. 123456 microseconds % 1000 = 456 microseconds
    << timevalCurrentTime.tv_usec % 1000 << "us"
    << ":"
      //          << timevalCurrentTime.tv_usec << "us"
    ;
}

#endif /* LINUX_LOG_FILE_PREFIX_HPP_ */
