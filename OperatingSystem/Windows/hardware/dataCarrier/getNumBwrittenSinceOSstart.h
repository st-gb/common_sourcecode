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
 * Win=WINdows: http://www.abbreviations.com/abbreviation/Windows
 * Num=NUMber: http://www.abbreviations.com/abbreviation/number
 * B=Byte: http://www.abbreviations.com/abbreviation/byte
 * OS=Operating System: http://www.abbreviations.com/OS */\
 ! defined TU_Bln361095OpSys_Win_hardware_dataCarrier_getNumWrittenBsinceOSstart_h
   #define TU_Bln361095OpSys_Win_hardware_dataCarrier_getNumWrittenBsinceOSstart_h

///C(++) standard library header files:
#include <stdint.h>///uint64_t

///MicroSoft Windows operating system header files:
 /**DeviceIoControl
http://learn.microsoft.com/en-us/windows/win32/api/ioapiset/nf-ioapiset-deviceiocontrol
  * "Header  ioapiset.h (include Windows.h)" */
#include <Windows.h>

///Stefan Gebauer's(TU Berlin matr.#361095)~"common_sourcecode"repository files:
#include <compiler/force_inline.h>///TU_Bln361095frcInln
 /**TU_Bln361095OpSysDataCarrierDef, TU_Bln361095OpSysDataCarrierNmSpcBgn, 
  * TU_Bln361095OpSysDataCarrierNmSpcEnd */
#include <OperatingSystem/hardware/dataCarrier/OpSysDataCarrier_ID_prefix.h>
 ///TU_Bln361095hardwareDataCarrierUse(OpenA)
#include <OperatingSystem/Windows/hardware/dataCarrier/openDataCarrier.h>
 ///enum TU_Bln361095dataCarrierGetNumBwrittenSinceOSstartUse(Rslt)
#include <OperatingSystem/hardware/dataCarrier/getNumBwrittenSinceOSstart.h>

/**Put in "operating system" namespace because the function works with
 * data retrieved from operating system.*/
TU_Bln361095OpSysDataCarrierNmSpcBgn

TU_Bln361095frcInln enum
 TU_Bln361095OpSysDataCarrierGetNumWrittenBsinceOSstartUse(Rslt)
  TU_Bln361095OpSysDataCarrierDef(GetNumWrittenBsinceOSstart)(
    const char dataCarrierPath[],
    uint64_t * pNumBytesWrittenSinceOSstart
  )
{
  HANDLE deviceHandle = TU_Bln361095hardwareDataCarrierUse(OpenA)(dataCarrierPath);
  if(deviceHandle == INVALID_HANDLE_VALUE)
    return TU_Bln361095OpSysDataCarrierGetNumWrittenBsinceOSstartUse(
      OpenDataCarrierFaild);
/**
http://learn.microsoft.com/en-us/windows/win32/api/winioctl/ni-winioctl-ioctl_disk_performance
*/
  DISK_PERFORMANCE disk_performance;
  DWORD bytesReturned;
/**
http://learn.microsoft.com/en-us/windows/win32/api/ioapiset/nf-ioapiset-deviceiocontrol
 * section "Return value": "If the operation completes successfully, the return
 * value is nonzero (TRUE)." */
  BOOL dvcIOctlRslt = DeviceIoControl(
    deviceHandle,
    IOCTL_DISK_PERFORMANCE,///dwIoControlCode
    NULL,///lpInBuffer
    0,///nInBufferSize
    &disk_performance,///(LPVOID)lpOutBuffer
    sizeof(DISK_PERFORMANCE),///(DWORD)nOutBufferSize
    &bytesReturned,///number of bytes written to buffer
    NULL///(LPOVERLAPPED)lpOverlapped
    );
  CloseHandle(deviceHandle);
  if(dvcIOctlRslt == FALSE)
    return TU_Bln361095OpSysDataCarrierGetNumWrittenBsinceOSstartUse(Error);
  *pNumBytesWrittenSinceOSstart = disk_performance.BytesWritten.QuadPart;
  return TU_Bln361095OpSysDataCarrierGetNumWrittenBsinceOSstartUse(Success);
}

TU_Bln361095OpSysDataCarrierNmSpcEnd

#endif///include guard
