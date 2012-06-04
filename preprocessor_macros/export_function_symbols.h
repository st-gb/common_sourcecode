/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */
/*
 * export_function_symbols.h
 *
 *  Created on: Dec 29, 2010
 *      Author: Stefan
 */

#ifndef EXPORT_FUNCTION_SYMBOLS_H_
#define EXPORT_FUNCTION_SYMBOLS_H_

#ifdef _WIN32 //Built-in macro for MSVC, MinGW (also for 64 bit Windows)

  //http://en.wikipedia.org/wiki/Dynamic-link_library#C_and_C.2B.2B:
  //"When external names follow the C naming conventions, they must also be
  //declared as extern "C" in C++ code, to prevent them from using C++ naming
  //conventions."

  //For exporting this function with the same name as in the source file.
  //Especially for MinGW this is needed in order to be called automatically
  //for DLL attach / detach etc. actions.
  #define EXPORT extern "C" __declspec(dllexport)
#else
  //http://www.linuxquestions.org/questions/programming-9/
  // how-to-export-function-symbols-750534/:
  //"__attribute__ ((visibility("default")))  // (similar to __declspec(dllexport))"
  #define EXPORT extern "C" //__attribute__ ((visibility("default")))
#endif

#endif /* EXPORT_FUNCTION_SYMBOLS_H_ */
