/**(c)from 2023 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
 * @author Stefan Gebauer(TU Berlin matriculation number 361095)*/

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
/**Include guard supported by (nearly) all industry compilers:*/\
/**Bln=Berlin: http://www.acronymfinder.com/Berlin-(Bln).html 
 * OpSys=OPerating SYStem: http://www.abbreviations.com/OpSys */\
 ! defined TU_Bln361095OpSys_Windows_hardware__STORAGE_PROTOCOL_SPECIFIC_DATA_h
   #define TU_Bln361095OpSys_Windows_hardware__STORAGE_PROTOCOL_SPECIFIC_DATA_h

/**Standard Microsoft Windows header files(included in Microsoft Visual C(++),
 * MinGW,...):*/
#include <windef.h>///DWORD

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
///_STORAGE_PROTOCOL_SPECIFIC_DATA's member "ProtocolType"
#include "_STORAGE_PROTOCOL_TYPE.h"

///http://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntddstor/ns-ntddstor-_storage_protocol_specific_data
typedef struct _STORAGE_PROTOCOL_SPECIFIC_DATA {
  STORAGE_PROTOCOL_TYPE ProtocolType;
  DWORD DataType;
  DWORD ProtocolDataRequestValue;
  DWORD ProtocolDataRequestSubValue;
  DWORD ProtocolDataOffset;
  DWORD ProtocolDataLength;
  DWORD FixedProtocolReturnData;
  DWORD ProtocolDataRequestSubValue2;
  DWORD ProtocolDataRequestSubValue3;
  DWORD ProtocolDataRequestSubValue4;
} STORAGE_PROTOCOL_SPECIFIC_DATA, *PSTORAGE_PROTOCOL_SPECIFIC_DATA;

#endif///include guard