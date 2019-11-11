#pragma once //include guard

#include <winnt.h> //for ULONG etc.
//from (Windows/ Microsoft) Platform SDK
#include <winioctl.h> //CTL_CODE

//Anfang von: Typdefinitionen für:
//BOOL GetDisksProperty(HANDLE hDevice, PSTORAGE_DEVICE_DESCRIPTOR pDevDesc)
//und BOOL IsUSBStickDrive(const CString & strFullPathOfDir)

//// The following structures all can find at MSDN.
// enumeration type specifies the various types of storage buses
// this enum is NOT declared in cygwins include/w32api/winioctl.h header file,
// but in the Windows Platform SDK 
//  (e.g. >>Platform SDK dir<<\Windows\6.1\Include/WinIoCtl.h)
typedef enum _STORAGE_BUS_TYPE {
    BusTypeUnknown = 0x00,
    BusTypeScsi,
    BusTypeAtapi,
    BusTypeAta,
    BusType1394,
    BusTypeSsa,
    BusTypeFibre,
    BusTypeUsb,
    BusTypeRAID,
    BusTypeMaxReserved = 0x7F
} STORAGE_BUS_TYPE, *PSTORAGE_BUS_TYPE;

#define DO_NOT_USE_WINIOCTL_H
//Do not include winioctl.h (from the Platform SDK): define it ourself.
#ifdef DO_NOT_USE_WINIOCTL_H
// retrieve the storage device descriptor data for a device. 
typedef struct _STORAGE_DEVICE_DESCRIPTOR {
  ULONG  Version;
  ULONG  Size;
  UCHAR  DeviceType;
  UCHAR  DeviceTypeModifier;
  BOOLEAN  RemovableMedia;
  BOOLEAN  CommandQueueing;
  ULONG  VendorIdOffset;
  ULONG  ProductIdOffset;
  ULONG  ProductRevisionOffset;
  ULONG  SerialNumberOffset;
  STORAGE_BUS_TYPE  BusType;
  ULONG  RawPropertiesLength;
  UCHAR  RawDeviceProperties[1];

} STORAGE_DEVICE_DESCRIPTOR, *PSTORAGE_DEVICE_DESCRIPTOR;

// retrieve the properties of a storage device or adapter. 
typedef enum _STORAGE_QUERY_TYPE {
  PropertyStandardQuery = 0,
  PropertyExistsQuery,
  PropertyMaskQuery,
  PropertyQueryMaxDefined

} STORAGE_QUERY_TYPE, *PSTORAGE_QUERY_TYPE;

// retrieve the properties of a storage device or adapter. 
typedef enum _STORAGE_PROPERTY_ID {
  StorageDeviceProperty = 0,
  StorageAdapterProperty,
  StorageDeviceIdProperty

} STORAGE_PROPERTY_ID, *PSTORAGE_PROPERTY_ID;

// retrieve the properties of a storage device or adapter. 
typedef struct _STORAGE_PROPERTY_QUERY {
  STORAGE_PROPERTY_ID  PropertyId;
  STORAGE_QUERY_TYPE  QueryType;
  UCHAR  AdditionalParameters[1];

} STORAGE_PROPERTY_QUERY, *PSTORAGE_PROPERTY_QUERY;
#endif //#ifdef DO_NOT_USE_WINIOCTL_H

// IOCTL control code
#define IOCTL_STORAGE_QUERY_PROPERTY   CTL_CODE(\
IOCTL_STORAGE_BASE, 0x0500, METHOD_BUFFERED, FILE_ANY_ACCESS)
//Ende von: Typdefinitionen f�r:
//BOOL GetDisksProperty(HANDLE hDevice, PSTORAGE_DEVICE_DESCRIPTOR pDevDesc)
//und BOOL IsUSBStickDrive(const CString & strFullPathOfDir)
