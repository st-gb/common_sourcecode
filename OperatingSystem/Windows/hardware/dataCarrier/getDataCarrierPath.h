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
/**Bln=BerLiN: http://www.acronymfinder.com/Berlin-(Bln).html
 * OpSys=OPerating SYStem: http://www.abbreviations.com/OpSys 
 * MS=MicroSoft: http://www.abbreviations.com/abbreviation/MicroSoft
 * Win=WINdows: http://www.abbreviations.com/abbreviation/Windows */\
 ! defined TU_Bln361095OpSys_MS_Win_hardware_dataCarrier_getDataCarrierPath_h
   #define TU_Bln361095OpSys_MS_Win_hardware_dataCarrier_getDataCarrierPath_h

///Standard C(++) header files:
#include <string.h>///strcpy_s(...)

///MicroSoft Windows'/Visual Studio's/MinGW's header files:
#include <tchar.h>///_tcscpy_s(...), _T([...])

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
#include <compiler/force_inline.h>///TU_Bln361095frcInln
 /**TU_Bln361095hardwareDataCarrierDef, TU_Bln361095hardwareDataCarrierNmSpcBgn
  * TU_Bln361095hardwareDataCarrierNmSpcEnd */
#include <hardware/dataCarrier/dataCarrier_ID_prefix.h>

/**http://learn.microsoft.com/en-us/windows/win32/api/ioapiset/nf-ioapiset-deviceiocontrol
 * : "To specify a device name, use the following format:
 *
 * \\.\DeviceName" */
 ///ANSI/ASCII version
#define TU_Bln361095OpsSysMS_WinDataCarrierPathPrefixA "\\\\.\\PhysicalDrive"

TU_Bln361095hardwareDataCarrierNmSpcBgn

/**@param dataCarrierID number as character string like "0". It is appended to
 *   @ref TU_Bln361095OpsSysMS_WinDataCarrierPathPrefixA
 * @param dataCarrierPath array must be allocated (on stack or heap) before
 *  calling this function. Set array size to MAX_PATH to be safe. 
 *  It is set to "\\\\.\\PhysicalDrive>>number<<". */
TU_Bln361095frcInln void TU_Bln361095hardwareDataCarrierDef(GetPath)(
  const TCHAR dataCarrierID[],
  TCHAR dataCarrierPath[])
{
//  TCHAR dataCarrierPath[/*sizeof(
//    TU_Bln361095OpsSysMS_WinDataCarrierPathPrefixA)
//    + /**string termating 0 character plus 2 digits*/ /*3*/
//    MAX_PATH];
/** "TCHAR" version of "sprintf_s(...)"
http://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/sprintf-s-sprintf-s-l-swprintf-s-swprintf-s-l?view=msvc-170
 */
//  _stprintf_s(dataCarrierPath, MAX_PATH, _T(
//    TU_Bln361095OpsSysMS_WinDataCarrierPathPrefixA) )
  _tcscpy_s(dataCarrierPath, MAX_PATH,
    _T(TU_Bln361095OpsSysMS_WinDataCarrierPathPrefixA) );
  _tcscat_s(dataCarrierPath, MAX_PATH, dataCarrierID);
}

/**@param dataCarrierID number as character string like "0"
 * @param dataCarrierPath array must be allocated (on stack or heap) before
 *  calling this function. Set array size to MAX_PATH to be safe.
 *  It is set to "\\\\.\\PhysicalDrive>>number<<". */
TU_Bln361095frcInln void TU_Bln361095hardwareDataCarrierDef(GetPathA)(
  const char dataCarrierID[],
  char dataCarrierPath[])
{
//  char dataCarrierPath[/*sizeof(
//    TU_Bln361095OpsSysMS_WinDataCarrierPathPrefixA)
//    + /**string termating 0 character plus 2 digits*/ /*3*/
//    MAX_PATH];
//  sprintf_s(dataCarrierPath, MAX_PATH,
//    TU_Bln361095OpsSysMS_WinDataCarrierPathPrefixA )
  strcpy_s(dataCarrierPath, MAX_PATH,
    TU_Bln361095OpsSysMS_WinDataCarrierPathPrefixA );
  strcat_s(dataCarrierPath, MAX_PATH, dataCarrierID);
}

TU_Bln361095hardwareDataCarrierNmSpcEnd

#endif///include guard
