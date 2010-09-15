/*
 * winnt.h
 *
 *  Created on: 28.08.2010
 *      Author: sgebauer
 */

#ifndef WINNT_H_
#define WINNT_H_

//from MinGW's <winnt.h>
typedef char CHAR;
#define CONST               const
typedef CONST CHAR *LPCSTR, *PCSTR;

#ifndef _MAC
typedef wchar_t WCHAR;    // wc,   16-bit UNICODE character
#else
// some Macintosh compilers don't define wchar_t in a convenient location, or define it as a char
typedef unsigned short WCHAR;    // wc,   16-bit UNICODE character
#endif

#ifdef  UNICODE
typedef CONST WCHAR *LPCWSTR, *PCWSTR;
typedef LPCWSTR PCTSTR, LPCTSTR;
#else
typedef LPCSTR PCTSTR, LPCTSTR, PCUTSTR, LPCUTSTR;
#endif
typedef WCHAR *PWCHAR,*LPWCH,*PWCH,*NWPSTR,*LPWSTR,*PWSTR;

#ifdef __GNUC__
  #define _HAVE_INT64
  #define _INTEGRAL_MAX_BITS 64
  #undef __int64
  #define __int64 long long
#elif defined(__WATCOMC__) && (defined(_INTEGRAL_MAX_BITS) && _INTEGRAL_MAX_BITS >= 64 )
  #define _HAVE_INT64
#endif /* __GNUC__/__WATCOMC */
#if defined(_HAVE_INT64) || (defined(_INTEGRAL_MAX_BITS) && _INTEGRAL_MAX_BITS >= 64)
  typedef __int64 LONGLONG;
  typedef unsigned __int64 DWORDLONG;
#else
  typedef double LONGLONG,DWORDLONG;
#endif

typedef DWORDLONG ULONGLONG,*PULONGLONG;

#endif /* WINNT_H_ */
