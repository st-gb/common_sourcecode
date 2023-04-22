/**(c)from 2023 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
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
/**Include guard supported by (nearly) all industry compilers:*/\
/**Bln=BerLiN:http://www.acronymfinder.com/Berlin-(Bln).html
 * cmn=CoMmoN:http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe:http://www.abbreviations.com/abbreviation/Source
 * OpSys=OPerating SYStem: http://www.abbreviations.com/OpSys */\
 ! defined TU_Bln361095cmnSrc_OpSys_Win_hardware_busType_h
   #define TU_Bln361095cmnSrc_OpSys_Win_hardware_busType_h

///Microsoft Windows header files:
 /**
http://learn.microsoft.com/en-us/windows/win32/api/winioctl/ne-winioctl-storage_bus_type
 * "Header 	winioctl.h (include Windows.h)" */
#include <Windows.h>///enum STORAGE_BUS_TYPE

///Stefan Gebauer's(TU Berlin matr.#361095)~"common_sourcecode"repository files:
#include <compiler/force_inline.h>///TU_Bln361095frcInln
 /**enum TU_Bln361095hardwareBusUse(Type), TU_Bln361095hardwareBusUse(NVMe),
  * TU_Bln361095hardwareBusUse(SATA), TU_Bln361095hardwareBusUse(USB) */
#include <hardware/bus/busType.h>
 /**enum TU_Bln361095hardwareBusUse, TU_Bln361095hardwareBusNmSpcBgn,
  * TU_Bln361095hardwareBusNmSpcEnd, TU_Bln361095hardwareBusDef */
#include <hardware/bus/hardwareBus_ID_prefix.h>

TU_Bln361095hardwareBusNmSpcBgn

/**Translates from Microsoft Windows-specific bus type to unified (operating
 * system-unpecific) bus type. */
TU_Bln361095frcInln enum TU_Bln361095hardwareBusUse(Type)
 TU_Bln361095hardwareBusDef(UnifyType)(
  STORAGE_BUS_TYPE storageBusType)
{
  switch(storageBusType)
  {
    ///Was "NVMe" for a HP laptop with internal SSD attached via PCI Express.
  case BusTypeNvme:
    return TU_Bln361095hardwareBusUse(NVMe);
  case BusTypeSata:
    return TU_Bln361095hardwareBusUse(SATA);
    ///Was "USB" when M2 SSD connected via USB to the JMicron? SATA adaptor.
  case BusTypeUsb:
    return TU_Bln361095hardwareBusUse(USB);
  }
  return TU_Bln361095hardwareBusUse(Unset);
}

TU_Bln361095hardwareBusNmSpcEnd

#endif///include guard
