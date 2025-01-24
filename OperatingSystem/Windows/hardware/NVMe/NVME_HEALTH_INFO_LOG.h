/**(c)from 2023 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
 * @author Stefan Gebauer(TU Berlin matriculation number 361095)*/

///NVME_HEALTH_INFO_LOG is in Windows SDK, so don't define it here again.
#if ! defined _MSC_VER
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
 ! defined TU_Bln361095OpSys_Windows_hardware_NVMe_NVME_HEALTH_INFO_LOG_h
   #define TU_Bln361095OpSys_Windows_hardware_NVMe_NVME_HEALTH_INFO_LOG_h

///Standard Microsoft Windows header files:
#include <windef.h>///UCHAR,ULONG,USHORT members

/**from
http://learn.microsoft.com/en-us/windows/win32/api/nvme/ns-nvme-nvme_health_info_log
 * : "Header  nvme.h" */
typedef struct {
  union {
    struct {
      UCHAR AvailableSpaceLow : 1;
      UCHAR TemperatureThreshold : 1;
      UCHAR ReliabilityDegraded : 1;
      UCHAR ReadOnly : 1;
      UCHAR VolatileMemoryBackupDeviceFailed : 1;
      UCHAR Reserved : 3;
    } DUMMYSTRUCTNAME;
    UCHAR AsUchar;
  } CriticalWarning;
  UCHAR  Temperature[2];
  UCHAR  AvailableSpare;
  UCHAR  AvailableSpareThreshold;
  UCHAR  PercentageUsed;
  UCHAR  Reserved0[26];
  UCHAR  DataUnitRead[16];
  UCHAR  DataUnitWritten[16];
  UCHAR  HostReadCommands[16];
  UCHAR  HostWrittenCommands[16];
  UCHAR  ControllerBusyTime[16];
  UCHAR  PowerCycle[16];
  UCHAR  PowerOnHours[16];
  UCHAR  UnsafeShutdowns[16];
  UCHAR  MediaErrors[16];
  UCHAR  ErrorInfoLogEntryCount[16];
  ULONG  WarningCompositeTemperatureTime;
  ULONG  CriticalCompositeTemperatureTime;
  USHORT TemperatureSensor1;
  USHORT TemperatureSensor2;
  USHORT TemperatureSensor3;
  USHORT TemperatureSensor4;
  USHORT TemperatureSensor5;
  USHORT TemperatureSensor6;
  USHORT TemperatureSensor7;
  USHORT TemperatureSensor8;
  UCHAR  Reserved1[296];
} NVME_HEALTH_INFO_LOG, *PNVME_HEALTH_INFO_LOG;

#endif///include guard

#endif///#if ! defined _MSC_VER