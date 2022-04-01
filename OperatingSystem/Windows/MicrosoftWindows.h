///Include guard, see http://en.wikipedia.org/wiki/Include_guard
#pragma once
#ifndef TU_Berlin361095MicroSoftWindows_h
#define TU_Berlin361095MicroSoftWindows_h
/** http://docs.microsoft.com/en-us/cpp/preprocessor/predefined-macros :
 *  , section "Standard predefined macros" : "_WIN32 Defined as 1 when the
 *  compilation target is 32-bit ARM, 64-bit ARM, x86, or x64. Otherwise,
 *  undefined."*/
///Is defined if compiling under Microsoft Windows (also non-32 bit).
#ifdef _WIN32
  /**Use author's matriculation number because it is unique. So no name clashes
   *  with an already defined macro with the same name should appear.*/
  #define TU_Bln361095MicroSoftWindows
#endif
#endif///TU_Berlin361095MicroSoftWindows_h