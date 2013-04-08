/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */
/*
 * determine_OS.h
 *
 *  Created on: Aug 17, 2010
 *      Author: Stefan
 */

#ifndef DETERMINE_OS_H_
#define DETERMINE_OS_H_

#ifdef _WIN32 //Built-in macro for MSVC, MinGW (also for 64 bit Windows)
  #ifndef _WINDOWS
    #define _WINDOWS
  #endif
#endif

#endif /* DETERMINE_OS_H_ */
