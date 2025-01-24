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
 ! defined TU_Bln361095OpSys_Windows_hardware_NVMe_NVME_LOG_PAGES_h
   #define TU_Bln361095OpSys_Windows_hardware_NVMe_NVME_LOG_PAGES_h

/**enum names from
http://learn.microsoft.com/en-us/windows/win32/api/nvme/ne-nvme-nvme_log_pages
, enum values from Visual Studio Community's "nvme.h" */

typedef enum {
  NVME_LOG_PAGE_ERROR_INFO = 0x01,
  NVME_LOG_PAGE_HEALTH_INFO = 0x02,
  NVME_LOG_PAGE_FIRMWARE_SLOT_INFO,
  NVME_LOG_PAGE_CHANGED_NAMESPACE_LIST,
  NVME_LOG_PAGE_COMMAND_EFFECTS,
  NVME_LOG_PAGE_DEVICE_SELF_TEST,
  NVME_LOG_PAGE_TELEMETRY_HOST_INITIATED,
  NVME_LOG_PAGE_TELEMETRY_CTLR_INITIATED,
  NVME_LOG_PAGE_ENDURANCE_GROUP_INFORMATION,
  NVME_LOG_PAGE_PREDICTABLE_LATENCY_NVM_SET,
  NVME_LOG_PAGE_PREDICTABLE_LATENCY_EVENT_AGGREGATE,
  NVME_LOG_PAGE_ASYMMETRIC_NAMESPACE_ACCESS,
  NVME_LOG_PAGE_PERSISTENT_EVENT_LOG,
  NVME_LOG_PAGE_LBA_STATUS_INFORMATION,
  NVME_LOG_PAGE_ENDURANCE_GROUP_EVENT_AGGREGATE,
  NVME_LOG_PAGE_RESERVATION_NOTIFICATION = 0x80,
  NVME_LOG_PAGE_SANITIZE_STATUS,
  NVME_LOG_PAGE_CHANGED_ZONE_LIST = 0xBF
} NVME_LOG_PAGES;

#endif///include guard