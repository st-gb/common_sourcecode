/**(c)Stefan Gebauer(Computer Science Master from TU Berlin)
 * @author Stefan Gebauer(TU Berlin matriculation number 361095) */

///Include guard,see http://en.wikipedia.org/wiki/Include_guard :

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
/**Include guard supported by (nearly) all compilers*/\
/**Bln=BerLiN:https://www.acronymfinder.com/Berlin-(Bln).html
 * cmn=CoMmoN:http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe:http://www.abbreviations.com/abbreviation/Source */\
 ! defined TU_Bln361095cmnSrc_hardware_CPU_memory_barrier_h
   #define TU_Bln361095cmnSrc_hardware_CPU_memory_barrier_h

#ifdef _MSC_VER///Microsoft Compiler
/** http://learn.microsoft.com/en-us/windows/win32/api/winnt/nf-winnt-memorybarrier
 * "Header  winnt.h (include Windows.h)" */
  #include <Windows.h>///MemoryBarrier();
#endif

/** from https://github.com/genodelabs/genode/issues/692 */
/** http://en.wikipedia.org/wiki/Memory_barrier#Out-of-order_execution_versus_compiler_reordering_optimizations:
 *  "Memory barrier instructions address reordering effects only at the
 *  hardware level" */
static inline void memory_barrier() {
#ifdef __GNUC__///GNU Compiler
  /** http://pic.dhe.ibm.com/infocenter/compbg/v121v141/topic/com.ibm.xlcpp121.bg.doc/compiler_ref/bif_gcc_atomic_synchronize.html
  * "A full memory barrier is created when this function is invoked." */

  /** http://stackoverflow.com/questions/12183311/difference-in-mfence-and-asm-volatile-memory:
  * MFENCE is full memory barrier (a combination of SFENCE and LFENCE), it
  * "Performs a serializing operation on all load-from-memory and store-to-memory
  * instructions that were issued prior the MFENCE instruction. This serializing
  * operation guarantees that every load and store instruction that precedes
  * the MFENCE instruction in program order becomes globally visible before any
  * load or store instruction that follows the MFENCE instruction." */

  __sync_synchronize(); /** generates "lock orl" assembly code on x86. */
#endif
#ifdef _MSC_VER///Microsoft Compiler
///https://learn.microsoft.com/en-us/windows/win32/api/winnt/nf-winnt-memorybarrier
  MemoryBarrier();
#endif
}

/** http://stackoverflow.com/questions/8841738/c-memory-barriers-for-atomics :
*
* "prevents the processor from moving reads and writes across the fence."
* "asm volatile ("" : : : "memory") in GCC and _ReadWriteBarrier in MSVC only
* provide a compiler level memory fence, preventing the compiler from
* reordering memory accesses.
* That means the processor is still free to do reordering. */
static inline void hardwareFence()
{
//  MemoryBarrier
  memory_barrier();
}

#endif///include guard
