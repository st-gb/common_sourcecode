/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */
/*
 * logging_preprocessor_macros_definitions.h
 *
 *  Created on: 07.05.2011
 *      Author: Stefan
 */

#ifndef LOGGING_PREPROCESSOR_MACROS_DEFINITIONS_H_
#define LOGGING_PREPROCESSOR_MACROS_DEFINITIONS_H_

//This file is included by
// -the source file that defines the global logging string
// -the preprocessor logging macros header file

//  #ifdef _GLIBCXX_USE_WCHAR_T //defined for GCC 4.5.2, but not for 3.4.5
//    #define LOGGING_CHARACTER_TYPE wchar_t
//  #else
//    #define LOGGING_CHARACTER_TYPE char
//  #endif

//  #define LOGGING_CHARACTER_TYPE_ID 0//1

#if defined(LOGGING_CHARACTER_TYPE_ID) && LOGGING_CHARACTER_TYPE_ID == 0//1
  #define LOG_CHAR_TYPE(x) L##x
  #define LOGGING_CHARACTER_TYPE wchar_t
#else
  #define LOG_CHAR_TYPE(x) x
  #define LOGGING_CHARACTER_TYPE char
#endif
//  GetLogStringType();

#endif /* LOGGING_PREPROCESSOR_MACROS_DEFINITIONS_H_ */
