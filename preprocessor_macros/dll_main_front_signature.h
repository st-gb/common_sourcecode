/*
 * dll_main_front_signature.h
 *
 *  Created on: 17.05.2012
 *      Author: Stefan
 */

#ifndef DLL_MAIN_FRONT_SIGNATURE_H_
#define DLL_MAIN_FRONT_SIGNATURE_H_

#include "export_function_symbols.h" //EXPORT

#ifndef APIENTRY
  #define APIENTRY
#endif

#ifdef _WIN32 //Built-in macro for MSVC, MinGW (also for 64 bit Windows)
  //For exporting this function with the same name as here in the source file.
  //Especially for MinGW this line is needed in order to be called automatically
  //for DLL attach / detach etc. actions.
  #define DLLMAIN_FRONT_SIGNATURE EXPORT BOOL APIENTRY
#else //#ifdef _WIN32
  //from http://tdistler.com/2007/10/05/
  // implementing-dllmain-in-a-linux-shared-library:
  #define DLLMAIN_FRONT_SIGNATURE void __attribute__ ((constructor))
#endif //#ifdef _WIN32

#endif /* DLL_MAIN_FRONT_SIGNATURE_H_ */
