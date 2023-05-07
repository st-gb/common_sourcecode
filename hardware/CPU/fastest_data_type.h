///(c)from 2022:Stefan Gebauer,Computer Science Master(TU Berlin,matric.#361095)
/**File location rationale:The fastest executed data type depends on CPU.
 * So place it in <hardware/CPU> directory.*/

///Include guard, see http://en.wikipedia.org/wiki/Include_guard
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
//#pragma once
///Include guard supported by (nearly) all industry compilers:
#ifndef TU_Bln361095cmnSrcHarwareCPUfaststDataType_h
#define TU_Bln361095cmnSrcHarwareCPUfaststDataType_h

///Stefan Gebauer's(TU Berlin mat.#361095) "common_sourcecode" repository files:
///TU_Bln361095CPUŃmSpcBgn,TU_Bln361095hardwareCPUnmSpcEnd,TU_Bln361095CPUdef
#include "ID_prefix.h"

//#include <stdint.h> //int_fast32_t

//TODO This only applies to x86?
/** "unsigned" has same bit width as CPU architecture a program is compiled 
 * for. -> this is maximum speed according to Dr. Ullrich Pohl because aligned to a CPU 
 * archicteture. */
typedef unsigned /*int_fast32_t*/ fastestUnsignedDataType;
typedef signed int fastestSignedDataType;

TU_Bln361095hardwareCPUnmSpcBgn

///"CPU" in macro name because fastest unsigned int is related to CPU.
typedef unsigned TU_Bln361095CPUdef(FaststUint);
typedef int TU_Bln361095CPUdef(FaststInt);

TU_Bln361095hardwareCPUnmSpcEnd

#endif///#ifndef TU_Bln361095cmnSrcHarwareCPUfaststDataType_h
