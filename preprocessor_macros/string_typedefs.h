/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */
#pragma once

//from winnt.h
typedef char CHAR;
#define CONST               const
typedef CONST CHAR *LPCSTR, *PCSTR;

#ifndef _MAC
typedef wchar_t WCHAR;    // wc,   16-bit UNICODE character
#else
// some Macintosh compilers don't define wchar_t in a convenient location, or define it as a char
typedef unsigned short WCHAR;    // wc,   16-bit UNICODE character
#endif
typedef WCHAR * LPWSTR, * PWSTR;
typedef CONST WCHAR * LPCWSTR, *PCWSTR;
//typedef CONST LPWSTR LPCWSTR, * PCWSTR;

//#ifdef  UNICODE
#if defined( _UNICODE) || defined(UNICODE)
typedef LPCWSTR PCTSTR, LPCTSTR;
#else
typedef LPCSTR PCTSTR, LPCTSTR, PCUTSTR, LPCUTSTR;
#endif
//Keep 1 newline after this line to avoid g++ warning"no newline at end of file"
