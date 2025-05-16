/**Created on: Nov 26, 2010
 * @author: Stefan Gebauer(TU Berlin matriculation number 361095) */

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
 * cmn=CoMmoN: http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe: http://www.abbreviations.com/abbreviation/Source
 * OpSys=OPerating SYStem: http://www.abbreviations.com/OpSys
 * Dvc=DeViCe: http://www.allacronyms.com/device/abbreviated */\
 ! defined TU_Bln361095cmnSrc_OpSys_Windows_hardware_GetStorageDvcInfo_h
   #define TU_Bln361095cmnSrc_OpSys_Windows_hardware_GetStorageDvcInfo_h

///Microsoft Windows operating system header files:
 /**
http://learn.microsoft.com/en-us/windows/win32/api/winioctl/ns-winioctl-storage_property_query
  * : "Header winioctl.h (include Windows.h)" */
 /**
http://learn.microsoft.com/en-us/windows/win32/api/winioctl/ns-winioctl-storage_device_descriptor
  * : "Header winioctl.h (include Windows.h)" */
#include <Windows.h>

///Stefan Gebauer's(TU Berlin mat.#361095)~"common_sourcecode" repository files:
#include <compiler/force_inline.h>///TU_Bln361095frcInln
 /**TU_Bln361095hardwareDataCarrierDef, TU_Bln361095hardwareDataCarrierNmSpcBgn,
  * TU_Bln361095hardwareDataCarrierNmSpcEnd */
#include <hardware/dataCarrier/dataCarrier_ID_prefix.h>

TU_Bln361095hardwareDataCarrierNmSpcBgn

TU_Bln361095frcInln BOOL TU_Bln361095hardwareDataCarrierDef(GetStorageDvcInfo)(
  HANDLE dvcHandle, PSTORAGE_DEVICE_DESCRIPTOR pDevDesc)
{
  STORAGE_PROPERTY_QUERY storagePropQuery;
  DWORD numBytesWrittenToOutBuffer;
  BOOL bResult;

  storagePropQuery.PropertyId = StorageDeviceProperty;
  storagePropQuery.QueryType = PropertyStandardQuery;

/**
http://learn.microsoft.com/en-us/windows/win32/api/winioctl/ns-winioctl-storage_device_descriptor :
 :"An application can determine the required buffer size by issuing a 
  IOCTL_STORAGE_QUERY_PROPERTY control code passing a STORAGE_DESCRIPTOR_HEADER
  structure for the output buffer, and then using the returned Size member of
  the STORAGE_DESCRIPTOR_HEADER structure to allocate a buffer of the proper
  size.*/
  //STORAGE_DESCRIPTOR_HEADER storageDescHdr;

  bResult =
/**
http://learn.microsoft.com/en-us/windows/win32/api/ioapiset/nf-ioapiset-deviceiocontrol
 : "If the operation completes successfully, the return value is nonzero (TRUE).
  If the operation fails or is pending, the return value is zero.To get extended
  error information, call GetLastError." */
   DeviceIoControl(
    dvcHandle,
    IOCTL_STORAGE_QUERY_PROPERTY,
	  ///input buffer
    & storagePropQuery,
    sizeof(STORAGE_PROPERTY_QUERY),
	 ///output buffer
    pDevDesc,
    //&storageDescHdr,
	  ///output buffer size
    sizeof(STORAGE_DEVICE_DESCRIPTOR),
    & numBytesWrittenToOutBuffer,
    (LPOVERLAPPED) NULL
    );
  return bResult;
}

TU_Bln361095hardwareDataCarrierNmSpcEnd

#endif///include guard
