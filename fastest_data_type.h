#ifndef FASTEST_DATA_TYPE_H
#define FASTEST_DATA_TYPE_H //include guard

/** "unsigned" has same bit width as CPU architecture a program is compiled 
 * for. -> this is maximum speed according to U. Pohl because aligned to a CPU 
 * arch.*/
typedef unsigned fastestUnsignedDataType;
typedef signed int fastestSignedDataType;

#endif //#ifndef FASTEST_DATA_TYPE_H