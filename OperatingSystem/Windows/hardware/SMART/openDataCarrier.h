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
 * OpSys=OPerating SYStem: http://www.abbreviations.com/OpSys 
 * MS=MicroSoft: http://www.abbreviations.com/abbreviation/MicroSoft
 * Win=WINdows: http://www.abbreviations.com/abbreviation/Windows */\
 ! defined TU_Bln361095OpSys_MS_Win_hardware_dataCarrier_SMART_openDataCarrier_h
   #define TU_Bln361095OpSys_MS_Win_hardware_dataCarrier_SMART_openDataCarrier_h

///MicroSoft Windows'/Visual Studio's/MinGW's header files:
#include <tchar.h>///_tcscpy_s(...)

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
#include <compiler/force_inline.h>///TU_Bln361095frcInln
///TU_Bln361095OpSysDataCarrierSMART_Def
#include <hardware/dataCarrier/SMART/SMART_ID_prefix.h>

/**http://learn.microsoft.com/en-us/windows/win32/api/ioapiset/nf-ioapiset-deviceiocontrol
 * : "To specify a device name, use the following format:
 *
 * \\.\DeviceName" */
///ANSI/ASCII version
#define TU_Bln361095OpsSysMS_WinDataCarrierPathPrefixA "\\\\.\\PhysicalDrive"

TU_Bln361095hardwareDataCarrierSMART_NmSpcBgn

TU_Bln361095frcInln void
 TU_Bln361095hardwareDataCarrierSMART_Def(getDataCarrierPath)(
  const TCHAR dataCarrierID[],
  TCHAR dataCarrierPath[])
{
//  TCHAR dataCarrierPath[/*sizeof(
//    TU_Bln361095OpsSysMS_WinDataCarrierPathPrefixA)
//    + /**string termating 0 character plus 2 digits*/ /*3*/
//    MAX_PATH];
/** "TCHAR" version of "printf_s(...)"
 *  http://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/sprintf-s-sprintf-s-l-swprintf-s-swprintf-s-l?view=msvc-170
 * */
//  _stprintf_s(dataCarrierPath, MAX_PATH, _T(
//    TU_Bln361095OpsSysMS_WinDataCarrierPathPrefixA) )
  _tcscpy_s(dataCarrierPath, MAX_PATH,
    _T(TU_Bln361095OpsSysMS_WinDataCarrierPathPrefixA) );
  _tcscat_s(dataCarrierPath, MAX_PATH, dataCarrierID);
}

/**@param dataCarrierID is appended to @ref
 *  TU_Bln361095OpsSysMS_WinDataCarrierPathPrefixA, for example "0" */
TU_Bln361095frcInln HANDLE
 TU_Bln361095hardwareDataCarrierSMART_Def(openDataCarrier)(
  const TCHAR dataCarrierPath[])
{
/**http://learn.microsoft.com/en-us/windows/win32/api/ioapiset/nf-ioapiset-deviceiocontrol
 * : "To retrieve a handle to the device, you must call the CreateFile function
 * with either the name of a device or the name of the driver associated with a
 * device. To specify a device name, use the following format:
 *
 * \\.\DeviceName" */
  HANDLE dataCarrierHandle = CreateFile(
///http://stackoverflow.com/questions/70337027/using-deviceiocontrol-to-get-smart-info-from-usb-connected-hdd
    dataCarrierPath,///[in] LPCSTR lpFileName,
    ///[in] DWORD dwDesiredAccess
/** http://learn.microsoft.com/en-us/windows/win32/devio/calling-deviceiocontrol
 *  : "0" for "no access to the drive" */
    0,//GENERIC_READ | GENERIC_WRITE,
    ///[in] DWORD dwShareMode,
/**http://learn.microsoft.com/en-us/windows/win32/api/ioapiset/nf-ioapiset-deviceiocontrol#remarks
 * : "You should specify the FILE_SHARE_READ and FILE_SHARE_WRITE access flags
 * when calling CreateFile to open a handle to a device driver."*/
    FILE_SHARE_READ | FILE_SHARE_WRITE /*| FILE_SHARE_DELETE*/,///3,
/** http://learn.microsoft.com/en-us/windows/win32/devio/calling-deviceiocontrol
 *  : NULL for "default security attributes" */
    NULL,//[in, optional] LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    ///[in] DWORD dwCreationDisposition
/**http://learn.microsoft.com/en-us/windows/win32/api/ioapiset/nf-ioapiset-deviceiocontrol#remarks
 * : "Use the other CreateFile parameters as follows when opening a device
 *  handle: [...] The fdwCreate parameter must specify OPEN_EXISTING." */
    OPEN_EXISTING,
    ///[in] DWORD dwFlagsAndAttributes,
/** https://learn.microsoft.com/en-us/windows/win32/devio/calling-deviceiocontrol
 *  "0" */
    0,/*FILE_ATTRIBUTE_DEVICE,*///FILE_ATTRIBUTE_SYSTEM,//,//FILE_ATTRIBUTE_NORMAL,
/**http://learn.microsoft.com/en-us/windows/win32/api/ioapiset/nf-ioapiset-deviceiocontrol#remarks
 * : "Use the other CreateFile parameters as follows when opening a device handle:
 * [...] The hTemplateFile parameter must be NULL." */
    NULL///[in, optional] HANDLE hTemplateFile
    );
  return dataCarrierHandle;
}

TU_Bln361095hardwareDataCarrierSMART_NmSpcEnd

#endif///Include guard