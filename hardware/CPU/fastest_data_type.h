#ifndef FASTEST_DATA_TYPE_H
#define FASTEST_DATA_TYPE_H //include guard

//#include <stdint.h> //int_fast32_t

/** "unsigned" has same bit width as CPU architecture a program is compiled 
 * for. -> this is maximum speed according to Dr. Ullrich Pohl because aligned to a CPU 
 * archicteture. */
typedef unsigned /*int_fast32_t*/ fastestUnsignedDataType;
typedef signed int fastestSignedDataType;

#endif //#ifndef FASTEST_DATA_TYPE_H
