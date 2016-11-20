#pragma once

/** from https://github.com/genodelabs/genode/issues/692 */
/** http://en.wikipedia.org/wiki/Memory_barrier#Out-of-order_execution_versus_compiler_reordering_optimizations:
 *  "Memory barrier instructions address reordering effects only at the
 *  hardware level" */
static inline void memory_barrier() {
#ifdef __GNUC__
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
#else //ifdef(_WIN32)
  MemoryBarrier
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
