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
 ! defined TU_Bln361095OpSys_Windows_hardware_NVMe_NVME_POWER_STATE_DESC_h
   #define TU_Bln361095OpSys_Windows_hardware_NVMe_NVME_POWER_STATE_DESC_h

///Standard Microsoft Windows header files:
#include <windef.h>///USHORT, UCHAR, ULONG members

/**from:
http://learn.microsoft.com/en-us/windows/win32/api/nvme/ns-nvme-nvme_power_state_desc
 * : "Header  nvme.h" */
typedef struct {
  USHORT MP;
  UCHAR  Reserved0;
  UCHAR  MPS : 1;
  UCHAR  NOPS : 1;
  UCHAR  Reserved1 : 6;
  ULONG  ENLAT;
  ULONG  EXLAT;
  UCHAR  RRT : 5;
  UCHAR  Reserved2 : 3;
  UCHAR  RRL : 5;
  UCHAR  Reserved3 : 3;
  UCHAR  RWT : 5;
  UCHAR  Reserved4 : 3;
  UCHAR  RWL : 5;
  UCHAR  Reserved5 : 3;
  USHORT IDLP;
  UCHAR  Reserved6 : 6;
  UCHAR  IPS : 2;
  UCHAR  Reserved7;
  USHORT ACTP;
  UCHAR  APW : 3;
  UCHAR  Reserved8 : 3;
  UCHAR  APS : 2;
  UCHAR  Reserved9[9];
} NVME_POWER_STATE_DESC, *PNVME_POWER_STATE_DESC;

#endif///include guard