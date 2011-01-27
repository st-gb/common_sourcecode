/*
 * export_function_symbols.h
 *
 *  Created on: Dec 29, 2010
 *      Author: Stefan
 */

#ifndef EXPORT_FUNCTION_SYMBOLS_H_
#define EXPORT_FUNCTION_SYMBOLS_H_

//http://en.wikipedia.org/wiki/Dynamic-link_library#C_and_C.2B.2B:
//"When external names follow the C naming conventions, they must also be
//declared as extern "C" in C++ code, to prevent them from using C++ naming
//conventions."
//For exporting this function with the same name as here in the source file.
#ifdef _WIN32 //Built-in macro for MSVC, MinGW (also for 64 bit Windows)
  #define EXPORT extern "C" __declspec(dllexport)
#else
  //http://www.linuxquestions.org/questions/programming-9/
  // how-to-export-function-symbols-750534/:
  //"__attribute__ ((visibility("default")))  // (similar to __declspec(dllexport))"
  #define EXPORT extern "C" //__attribute__ ((visibility("default")))
#endif

#endif /* EXPORT_FUNCTION_SYMBOLS_H_ */
