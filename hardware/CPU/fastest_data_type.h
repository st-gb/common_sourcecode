///(c)from 2022:Stefan Gebauer,Computer Science Master(TU Berlin,matric.#361095)
/**File location rationale:The fastest executed data type depends on CPU.
 * So place it in <hardware/CPU> directory.
 * @author Stefan Gebauer:TU Berlin matriculation number 361095*/

///Include guard, see http://en.wikipedia.org/wiki/Include_guard :

/**Bln=BerLiN:http://www.acronymfinder.com/Berlin-(Bln).html
 * Prgm=PRaGMa
 * Incl=INCLude:http://www.abbreviations.com/abbreviation/include
 * Grd=GuaRD:http://www.abbreviations.com/abbreviation/guard */
#ifdef TU_Bln361095usePrgmInclGrd
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
  #pragma once
#endif
#if defined TU_Bln361095usePrgmInclGrd ||\
/**Include guard supported by (nearly) all industry compilers:*/\
/**Bln=BerLiN: https://www.acronymfinder.com/Berlin-(Bln).html
 * cmn=CoMmoN: http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe: http://www.abbreviations.com/abbreviation/Source */\
 ! defined TU_Bln361095cmnSrc_Hardware_CPU_faststDataType_h
   #define TU_Bln361095cmnSrc_Hardware_CPU_faststDataType_h

///Stefan Gebauer's(TU Berlin mat.#361095) "common_sourcecode" repository files:
/**TU_Bln361095CPUnmSpcBgn,TU_Bln361095CPUnmSpcEnd,TU_Bln361095CPUdef
 * TU_Bln361095hardwareCPUnmSpcBgn,TU_Bln361095hardwareCPUnmSpcEnd,
 * TU_Bln361095hardwareCPUdef */
#include "hardwareCPU_ID_prefix.h"

//#include <stdint.h> //int_fast32_t

//TODO This only applies to x86?
/**"unsigned" has same bit width as CPU architecture a program is compiled for.
 * -> this is maximum speed according to Dr. Ullrich Pohl because aligned to a
 * CPU architecture.*/
typedef unsigned /*int_fast32_t*/ fastestUnsignedDataType;
typedef signed int fastestSignedDataType;

TU_Bln361095CPUnmSpcBgn

///unprecisely scoped (not inside "hardware") for convenience(less typing):
///"CPU" in macro name because fastest unsigned int is related to CPU.
typedef unsigned TU_Bln361095CPUdef(FaststUint);
typedef unsigned int TU_Bln361095CPUdef(faststUint);
typedef int TU_Bln361095CPUdef(FaststInt);

TU_Bln361095CPUnmSpcEnd

TU_Bln361095hardwareCPUnmSpcBgn

///more precisely (inside "hardware") scoped:
typedef unsigned TU_Bln361095hardwareCPUdef(FaststUint);
typedef int TU_Bln361095hardwareCPUdef(FaststInt);

TU_Bln361095hardwareCPUnmSpcEnd

#endif///include guard
