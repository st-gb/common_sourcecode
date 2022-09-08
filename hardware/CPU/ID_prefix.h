///(c)from 2022 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
/**File:ID_prefix.h
 * Created on 23. April 2022, 22:16 */

///Include guard,see http://en.wikipedia.org/wiki/Include_guard
///Include guard supported by (nearly) all industry compilers:
#ifndef TU_Bln361095cmnSrc_hardware_CPU_IDprefix_h
#define TU_Bln361095cmnSrc_hardware_CPU_IDprefix_h

#ifdef __cplusplus
 #define TU_Bln361095CPUnmSpc TU_Bln361095::/*cmnSrc::*/hardware::CPU::
 #define TU_Bln361095hardwareCPUnmSpcBgn namespace TU_Bln361095{namespace \
hardware{namespace CPU{
 #define TU_Bln361095hardwareCPUnmSpcEnd }}}
 #define TU_Bln361095CPUdef(suffix) suffix
 #define TU_Bln361095CPUuse(suffix) TU_Bln361095CPUnmSpc suffix
 #define TU_Bln361095hardwareCPUdef(suffix) TU_Bln361095CPUdef(suffix)
 #define TU_Bln361095hardwareCPUuse(suffix) TU_Bln361095CPUuse(suffix)
#else
 #define TU_Bln361095hardwareCPUnmSpcBgn
 #define TU_Bln361095hardwareCPUnmSpcEnd
 #define TU_Bln361095CPUdef(suffix) TU_Bln361095CPU##suffix
 #define TU_Bln361095CPUuse(suffix) TU_Bln361095CPU##suffix
#endif

#endif///#ifndef TU_Bln361095cmnSrc_hardware_CPU_IDprefix_h
