/*
 * Linux_log_file_prefix.hpp
 *
 *  Created on: Jul 22, 2011
 *      Author: sgebauer
 */

#ifndef LINUX_LOG_FILE_PREFIX_HPP_
#define LINUX_LOG_FILE_PREFIX_HPP_

#include <ostream> //class ostream
#include <sys/time.h> // gettimeofday(...)
#include <time.h> // localtime(...)

//#define LOG_FILE_PREFIX()

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
