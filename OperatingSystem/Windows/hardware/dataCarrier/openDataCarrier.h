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
 ! defined TU_Bln361095OpSys_MS_Win_hardware_dataCarrier_openDataCarrier_h
   #define TU_Bln361095OpSys_MS_Win_hardware_dataCarrier_openDataCarrier_h

///MicroSoft Windows'/Visual Studio's/MinGW's header files:
#include <Windows.h>///CreateFile

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
#include <compiler/force_inline.h>///TU_Bln361095frcInln
 /**TU_Bln361095hardwareDataCarrierDef,
  * TU_Bln361095hardwareDataCarrierNmSpcBgn,
  * TU_Bln361095hardwareDataCarrierNmSpcEnd */
#include <hardware/dataCarrier/dataCarrier_ID_prefix.h>

typedef HANDLE TU_Bln361095hardwareDataCarrierIDtyp;

TU_Bln361095hardwareDataCarrierNmSpcBgn

typedef HANDLE TU_Bln361095hardwareDataCarrierDef(IDtyp);

///TCHAR version
TU_Bln361095frcInln HANDLE TU_Bln361095hardwareDataCarrierDef(Open)(
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

/** ANSI/ASCII ("char") version */
TU_Bln361095frcInln HANDLE TU_Bln361095hardwareDataCarrierDef(OpenA)(
  const char dataCarrierPath[])
{
  /**http://learn.microsoft.com/en-us/windows/win32/api/ioapiset/nf-ioapiset-deviceiocontrol
   * : "To retrieve a handle to the device, you must call the CreateFile function
   * with either the name of a device or the name of the driver associated with a
   * device. To specify a device name, use the following format:
   *
   * \\.\DeviceName" */
  HANDLE dataCarrierHandle = CreateFileA(
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

TU_Bln361095frcInln int TU_Bln361095hardwareDataCarrierDef(OpnFaild)(
  const HANDLE dataCarrierID)
{
  if(dataCarrierID == INVALID_HANDLE_VALUE)
   return 1;
  return 0;
}
TU_Bln361095hardwareDataCarrierNmSpcEnd

#endif///Include guard
