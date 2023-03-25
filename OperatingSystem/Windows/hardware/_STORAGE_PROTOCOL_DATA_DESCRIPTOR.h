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
 ! defined TU_Bln361095OpSys_Windows_hardware__STORAGE_PROTOCOL_DATA_DESCRIPTOR_h
   #define TU_Bln361095OpSys_Windows_hardware__STORAGE_PROTOCOL_DATA_DESCRIPTOR_h

/**Standard Microsoft Windows header files(included in Microsoft Visual C(++),
 * MinGW,...):*/
/**http://learn.microsoft.com/en-us/windows/win32/winprog/windows-data-types :
 * "DWORD" "Header BaseTsd.h; WinDef.h; WinNT.h"*/
#include <WinDef.h>///DWORD

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
///_STORAGE_PROTOCOL_DATA_DESCRIPTOR's member "ProtocolSpecificData"
#include "_STORAGE_PROTOCOL_SPECIFIC_DATA.h"

/** from_
http://learn.microsoft.com/en-us/windows/win32/api/winioctl/ns-winioctl-storage_protocol_data_descriptor
*/
typedef struct _STORAGE_PROTOCOL_DATA_DESCRIPTOR {
  DWORD Version;
  DWORD Size;
  STORAGE_PROTOCOL_SPECIFIC_DATA ProtocolSpecificData;
} STORAGE_PROTOCOL_DATA_DESCRIPTOR, *PSTORAGE_PROTOCOL_DATA_DESCRIPTOR;

#endif///include guard