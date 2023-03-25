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
 ! defined TU_Bln361095OpSys_Windows_hardware_NVMe_NVME_IDENTIFY_CNS_CODES_h
   #define TU_Bln361095OpSys_Windows_hardware_NVMe_NVME_IDENTIFY_CNS_CODES_h

///http://learn.microsoft.com/en-us/windows/win32/api/nvme/ne-nvme-nvme_identify_cns_codes
typedef enum {
  NVME_IDENTIFY_CNS_SPECIFIC_NAMESPACE,
  NVME_IDENTIFY_CNS_CONTROLLER,
  NVME_IDENTIFY_CNS_ACTIVE_NAMESPACES,
  NVME_IDENTIFY_CNS_DESCRIPTOR_NAMESPACE,
  NVME_IDENTIFY_CNS_NVM_SET,
  NVME_IDENTIFY_CNS_SPECIFIC_NAMESPACE_IO_COMMAND_SET,
  NVME_IDENTIFY_CNS_SPECIFIC_CONTROLLER_IO_COMMAND_SET,
  NVME_IDENTIFY_CNS_ACTIVE_NAMESPACE_LIST_IO_COMMAND_SET,
  NVME_IDENTIFY_CNS_ALLOCATED_NAMESPACE_LIST,
  NVME_IDENTIFY_CNS_ALLOCATED_NAMESPACE,
  NVME_IDENTIFY_CNS_CONTROLLER_LIST_OF_NSID,
  NVME_IDENTIFY_CNS_CONTROLLER_LIST_OF_NVM_SUBSYSTEM,
  NVME_IDENTIFY_CNS_PRIMARY_CONTROLLER_CAPABILITIES,
  NVME_IDENTIFY_CNS_SECONDARY_CONTROLLER_LIST,
  NVME_IDENTIFY_CNS_NAMESPACE_GRANULARITY_LIST,
  NVME_IDENTIFY_CNS_UUID_LIST,
  NVME_IDENTIFY_CNS_DOMAIN_LIST,
  NVME_IDENTIFY_CNS_ENDURANCE_GROUP_LIST,
  NVME_IDENTIFY_CNS_ALLOCATED_NAMSPACE_LIST_IO_COMMAND_SET,
  NVME_IDENTIFY_CNS_ALLOCATED_NAMESPACE_IO_COMMAND_SET,
  NVME_IDENTIFY_CNS_IO_COMMAND_SET
} NVME_IDENTIFY_CNS_CODES;

#endif///include guard