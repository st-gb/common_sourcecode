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
 ! defined TU_Bln361095OpSys_Windows_hardware_STORAGE_PROPERTY_ID_fromVal9_h
   #define TU_Bln361095OpSys_Windows_hardware_STORAGE_PROPERTY_ID_fromVal9_h

/**Adds enum values to TDM-GCC 10.3.0-2's _STORAGE_PROPERTY_ID (in winioctl.h ?)
 * The 1st 9 enum values aren't defined to avoid error of multiple definitions
 * because these are already defined in "_STORAGE_PROPERTY_ID" of TDM-GCC's
 * header file ("winioctl.h"?)*/

/**from 
http://learn.microsoft.com/en-us/windows/win32/api/winioctl/ne-winioctl-storage_property_id#syntax
*/
typedef enum _STORAGE_PROPERTY_ID_fromVal9 {
  StorageDeviceWriteAggregationProperty = 9,
  StorageDeviceDeviceTelemetryProperty,
  StorageDeviceLBProvisioningProperty,
  StorageDevicePowerProperty,
  StorageDeviceCopyOffloadProperty,
  StorageDeviceResiliencyProperty,
  StorageDeviceMediumProductType,
  StorageAdapterRpmbProperty,
  StorageAdapterCryptoProperty,
  StorageDeviceIoCapabilityProperty = 48,
  StorageAdapterProtocolSpecificProperty,
  StorageDeviceProtocolSpecificProperty,
  StorageAdapterTemperatureProperty,
  StorageDeviceTemperatureProperty,
  StorageAdapterPhysicalTopologyProperty,
  StorageDevicePhysicalTopologyProperty,
  StorageDeviceAttributesProperty,
  StorageDeviceManagementStatus,
  StorageAdapterSerialNumberProperty,
  StorageDeviceLocationProperty,
  StorageDeviceNumaProperty,
  StorageDeviceZonedDeviceProperty,
  StorageDeviceUnsafeShutdownCount,
  StorageDeviceEnduranceProperty,
  StorageDeviceLedStateProperty,
  StorageDeviceSelfEncryptionProperty = 64,
  StorageFruIdProperty
} STORAGE_PROPERTY_ID_fromVal9, *PSTORAGE_PROPERTY_ID_fromVal9;

#endif///include guard