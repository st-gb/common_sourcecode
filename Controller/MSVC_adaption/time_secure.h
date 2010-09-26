/* 
 * File:   time.h
 * Author: Stefan
 *
 * Created on 4. April 2009, 13:28
 */

#ifndef _TIME_H
#define	_TIME_H

#ifdef _WIN32 //Built-in macro for MSVC, MinGW (also for 64 bit Windows)
  #include <time.h>

#ifdef __CYGWIN__
  typedef struct timeb _timeb ;
#endif

#ifdef	__cplusplus
extern "C" {
#endif

//For not defining it a second time if building with Visual Studio.
#ifdef __CYGWIN__
  int _ftime_s(struct
    timeb *  p_timeb) ;

  int localtime_s(
    struct tm * p_tm
    , const time_t * time
    ) ;
//  {
//    int nRet = 0 ;
//    struct tm * p_tmLocalTimeResult = localtime(time) ;
//    if( p_tmLocalTimeResult )
//      * p_tm = * p_tmLocalTimeResult ;
//    else
//      nRet = 1;
//    return nRet ;
//  }
#endif //#ifdef __CYGWIN__

#ifdef	__cplusplus
}
#endif
#endif //#ifdef _WIN32

#endif	/* _TIME_H */

