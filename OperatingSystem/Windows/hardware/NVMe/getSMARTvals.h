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
 !defined TU_Bln361095OpSys_MS_Win_hardware_NVMe_GetSMARTvals_h
  #define TU_Bln361095OpSys_MS_Win_hardware_NVMe_GetSMARTvals_h

//TODO What is the minimal Microsoft compiler version needed to compile?
#if _MSC_VER > 1920
///ProtocolTypeNvme, NVME_LOG_PAGE_HEALTH_INFO, PSTORAGE_PROPERTY_QUERY, 
/// PSTORAGE_PROTOCOL_DATA_DESCRIPTOR, PSTORAGE_PROTOCOL_SPECIFIC_DATA
///STORAGE_PROTOCOL_NVME_DATA_TYPE etc. in <winioctl.h> included by <Windows.h>
  #include <Windows.h>
  #include <Ntddstor.h>///_STORAGE_PROTOCOL_SPECIFIC_DATA
/**If installing the Visual Studio (Community Edition) (oonfirmed for version
 * 2022), <nvme.h> may be in a path like
 * "C:\Program Files (x86)\Windows Kits\10\Include\10.0.22000.0\shared"? */
  #include <nvme.h>///struct NVME_HEALTH_INFO_LOG
#endif
#if __GNUC__ >= 10
  ///PSTORAGE_PROPERTY_QUERYs in <winioctl.h> etc.
  #include <windows.h>
///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
/**To build with TDM-GCC (confirmed with version 10.3.0-2 64 bit), the following
 * enums and structs must be defined and included additionally to TDM-GCC's
 * header files.*/
 ///in _recent_ Visual Studio's <winioctl.h> :
  /**struct * PSTORAGE_PROTOCOL_DATA_DESCRIPTOR, struct
   * STORAGE_PROTOCOL_SPECIFIC_DATA */
  #include <OperatingSystem/Windows/hardware/_STORAGE_PROTOCOL_DATA_DESCRIPTOR.h>
  ///enum value StorageAdapterProtocolSpecificProperty
  #include <OperatingSystem/Windows/hardware/_STORAGE_PROPERTY_ID_fromVal9.h>
  ///enum value NVMeDataTypeLogPage
  #include <OperatingSystem/Windows/hardware/NVMe/_STORAGE_PROTOCOL_NVME_DATA_TYPE.h>

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
 ///in _recent_ Visual Studio's <ntddstor.h>:
  /**see
http://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntddstor/ns-ntddstor-_storage_protocol_specific_data
   * : "include Ntddstor.h"*/
  ///STORAGE_PROTOCOL_SPECIFIC_DATA, ProtocolTypeNvme
  #include <OperatingSystem/Windows/hardware/_STORAGE_PROTOCOL_SPECIFIC_DATA.h>

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
 ///in _recent_ Visual Studio's <nvme.h>:
  /**https://learn.microsoft.com/en-us/windows/win32/api/nvme/ne-nvme-nvme_identify_cns_codes
   * "Header nvme.h"
   * for NVME_IDENTIFY_CNS_CONTROLLER */
//  #include <OperatingSystem/Windows/hardware/NVMe/NVME_IDENTIFY_CNS_CODES.h>
/**http://learn.microsoft.com/en-us/windows/win32/api/nvme/ns-nvme-nvme_identify_controller_data
 * : "Header nvme.h" */
//  #include <OperatingSystem/Windows/hardware/NVMe/NVME_IDENTIFY_CONTROLLER_DATA.h>
  ///enum value NVME_LOG_PAGE_HEALTH_INFO
  #include <OperatingSystem/Windows/hardware/NVMe/NVME_LOG_PAGES.h>
  ///struct NVME_HEALTH_INFO_LOG
  #include <OperatingSystem/Windows/hardware/NVMe/NVME_HEALTH_INFO_LOG.h>

///http://social.msdn.microsoft.com/Forums/aspnet/en-US/24f6bf24-7545-4863-858b-3c8876109b53/where-is-nvmeh-include-file-on-windows-10-kit?forum=windowsgeneraldevelopmentissues
  #define NVME_MAX_LOG_SIZE 0x1000
#endif

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
#include "NVMe_ID_prefix.h"
#include <compiler/force_inline.h>///TU_Bln361095frcInln

#ifdef __cplusplus
/**Def=definition: http://www.abbreviations.com/abbreviation/definition
 * Put definition between "[...]NmSpcBgn" and "[...]NmSpcEnd" #define'd below.*/
  #define TU_Bln361095hardwareDataCarrierNVMeGetSMARTvalsDef(suffix) suffix
 /**Nm=name: http://www.abbreviations.com/abbreviation/name
  * Spc=space: http://www.abbreviations.com/abbreviation/Space */
  #define TU_Bln361095hardwareDataCarrierNVMeGetSMARTvalsNmSpc\
    TU_Bln361095hardwareDataCarrierNVMeNmSpc GetSMARTvals ::
  ///Bgn=BeGiN :http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095hardwareDataCarrierNVMeGetSMARTvalsNmSpcBgn\
    TU_Bln361095hardwareDataCarrierNVMeNmSpcBgn namespace GetSMARTvals{
  #define TU_Bln361095hardwareDataCarrierNVMeGetSMARTvalsNmSpcEnd\
    TU_Bln361095hardwareDataCarrierNVMeNmSpcEnd }
  #define TU_Bln361095hardwareDataCarrierNVMeGetSMARTvalsUse(suffix)\
    TU_Bln361095hardwareDataCarrierNVMeNmSpc suffix
#else
/**http://gcc.gnu.org/onlinedocs/cpp/Concatenation.html#Concatenation :"The �##�
 * preprocessing operator performs token pasting. When a macro is expanded, the
 * two tokens on either side of each �##� operator are combined into a single
 * token, which then replaces the �##� and the two original tokens in the macro
 * expansion."*/
 ///Def=definition: http://www.abbreviations.com/abbreviation/definition
  #define TU_Bln361095hardwareDataCarrierNVMeGetSMARTvalsDef(suffix)\
    TU_Bln361095hardwareDataCarrierNVMeUse(GetSMARTvals##suffix)
/**Nm=name: http://www.abbreviations.com/abbreviation/name
 * Spc=space: http://www.abbreviations.com/abbreviation/Space */
 /**"C" language has no namespaces->Replace with empty character string.*/
  #define TU_Bln361095hardwareDataCarrierNVMeGetSMARTvalsNmSpc
///Bgn=BeGiN :http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095hardwareDataCarrierNVMeGetSMARTvalsNmSpcBgn
  #define TU_Bln361095hardwareDataCarrierNVMeGetSMARTvalsNmSpcEnd
  #define TU_Bln361095hardwareDataCarrierNVMeGetSMARTvalsUse(suffix)\
    TU_Bln361095hardwareDataCarrierNVMeGetSMARTvalsDef(suffix)
#endif

TU_Bln361095hardwareDataCarrierNVMeGetSMARTvalsNmSpcBgn

enum TU_Bln361095hardwareDataCarrierNVMeGetSMARTvalsDef(Rslt) {
  TU_Bln361095hardwareDataCarrierNVMeGetSMARTvalsDef(Sccss) = 0,
  TU_Bln361095hardwareDataCarrierNVMeGetSMARTvalsDef(AllocBufFaild),
  TU_Bln361095hardwareDataCarrierNVMeGetSMARTvalsDef(DvcIOctlFaild),
  TU_Bln361095hardwareDataCarrierNVMeGetSMARTvalsDef(HdrInvalid),
  TU_Bln361095hardwareDataCarrierNVMeGetSMARTvalsDef(OffsetInvalid)
};

TU_Bln361095hardwareDataCarrierNVMeGetSMARTvalsNmSpcEnd

TU_Bln361095hardwareDataCarrierNVMeNmSpcBgn

/**@param deviceHandle must be open. See function 
 *  "TU_Bln361095hardwareDataCarrierUse(Open)" on how to open it.
 * @param ppDvcIOctlBuf : dereferenced parameter is allocated within this
 *  function and holds the memory for *ppNMVeHealthInfoLog. Therefore free
 *  memory of this function via "free([...])" function for this dereferenced
 *  parameter after using *ppNMVeHealthInfoLog:
 *  One can pass address of a pointer for this parameter.
 *  Sample code for calling this function and freeing the buffer:
 *   "uint8_t * pDvcIOctlBuf;
 *   [...]
 *   [...]GetSMARTvals([...]&pDvcIOctlBuf[...]);
 *   [...]
 *   free(pDvcIOctlBuf);"
 * @param ppNMVeHealthInfoLog : dereferenced parameter points to struct
 *   NVME_HEALTH_INFO_LOG
 *  One can pass address of a pointer to struct NVME_HEALTH_INFO_LOG for this
 *   parameter:
 *   "NVME_HEALTH_INFO_LOG * pNMVeHealthInfoLog;
 *   [...]GetSMARTvals([...]&pNMVeHealthInfoLog[...]);"
 * @return TU_Bln361095hardwareDataCarrierNVMeGetSMARTvalsDef(Sccss) if
 *  successful */
TU_Bln361095frcInln
 enum TU_Bln361095hardwareDataCarrierNVMeGetSMARTvalsUse(Rslt)
  TU_Bln361095hardwareDataCarrierNVMeDef(GetSMARTvals)(
   HANDLE deviceHandle,
   uint8_t ** ppDvcIOctlBuf,
   NVME_HEALTH_INFO_LOG ** ppNMVeHealthInfoLog)
{
///from http://learn.microsoft.com/en-us/windows/win32/fileio/working-with-nvme-devices#example-nvme-identify-query
  BOOL dvcIOctrlRslt;
  PVOID pDvcIOctlBuf;
  DWORD dvcIOctlBufSizInB;
  DWORD dvcIOctlNumBufBwritten;

  PSTORAGE_PROPERTY_QUERY p_storagePropQuery = NULL;
  PSTORAGE_PROTOCOL_SPECIFIC_DATA p_protoData = NULL;
  PSTORAGE_PROTOCOL_DATA_DESCRIPTOR p_protoDataDescr = NULL;

  ///Allocate buffer for use.
  dvcIOctlBufSizInB = FIELD_OFFSET(STORAGE_PROPERTY_QUERY, AdditionalParameters) +
    sizeof(STORAGE_PROTOCOL_SPECIFIC_DATA) + /*NVME_MAX_LOG_SIZE*/
    sizeof(NVME_HEALTH_INFO_LOG);
  pDvcIOctlBuf = malloc(dvcIOctlBufSizInB);

  if(pDvcIOctlBuf == NULL)
    return TU_Bln361095hardwareDataCarrierNVMeGetSMARTvalsUse(AllocBufFaild);
  
  ZeroMemory(pDvcIOctlBuf, dvcIOctlBufSizInB);
  p_storagePropQuery = (PSTORAGE_PROPERTY_QUERY)pDvcIOctlBuf;
  p_protoDataDescr = (PSTORAGE_PROTOCOL_DATA_DESCRIPTOR)pDvcIOctlBuf;
  p_protoData = (PSTORAGE_PROTOCOL_SPECIFIC_DATA)p_storagePropQuery->
    AdditionalParameters;

  p_storagePropQuery->PropertyId = //StorageDeviceProtocolSpecificProperty;
/**http://learn.microsoft.com/en-us/windows/win32/fileio/working-with-nvme-devices
 * "If ProtocolType = ProtocolTypeNvme and DataType = NVMeDataTypeLogPage,
 * callers should request 512 byte chunks of data."*/
    StorageAdapterProtocolSpecificProperty;
  p_storagePropQuery->QueryType = PropertyStandardQuery;

  p_protoData->ProtocolType = ProtocolTypeNvme;
  p_protoData->DataType = NVMeDataTypeLogPage;
  p_protoData->ProtocolDataRequestValue = NVME_LOG_PAGE_HEALTH_INFO;
  p_protoData->ProtocolDataRequestSubValue = 0;
  ///https://github.com/MicrosoftDocs/win32/blob/docs/desktop-src/FileIO/working-with-nvme-devices.md :
  p_protoData->ProtocolDataRequestSubValue2 = 0; // This will be passed as the higher 32 bit of log page offset if controller supports extended data for the Get Log Page.
  p_protoData->ProtocolDataRequestSubValue3 = 0; // This will be passed as Log Specific Identifier in CDW11.
  p_protoData->ProtocolDataRequestSubValue4 = 0; // This will map to STORAGE_PROTOCOL_DATA_SUBVALUE_GET_LOG_PAGE definition, then user can pass Retain Asynchronous Event, Log Specific Field.
  p_protoData->ProtocolDataOffset = sizeof(STORAGE_PROTOCOL_SPECIFIC_DATA);
  p_protoData->ProtocolDataLength = sizeof(NVME_HEALTH_INFO_LOG);

  // Send request down.
  dvcIOctrlRslt = DeviceIoControl(
    deviceHandle,
    IOCTL_STORAGE_QUERY_PROPERTY,
    pDvcIOctlBuf,
    dvcIOctlBufSizInB,
    pDvcIOctlBuf,
    dvcIOctlBufSizInB,
    &dvcIOctlNumBufBwritten,
    NULL
    );
  if(dvcIOctrlRslt == FALSE)
    return TU_Bln361095hardwareDataCarrierNVMeGetSMARTvalsUse(DvcIOctlFaild);
  
  // Validate the returned data.
  if( (p_protoDataDescr->Version != sizeof(STORAGE_PROTOCOL_DATA_DESCRIPTOR) ) ||
      (p_protoDataDescr->Size != sizeof(STORAGE_PROTOCOL_DATA_DESCRIPTOR)) )
    ///data descriptor header not valid
    return TU_Bln361095hardwareDataCarrierNVMeGetSMARTvalsUse(HdrInvalid);

  p_protoData = &p_protoDataDescr->ProtocolSpecificData;

  if( (p_protoData->ProtocolDataOffset <
        sizeof(STORAGE_PROTOCOL_SPECIFIC_DATA)) ||
      (p_protoData->ProtocolDataLength < sizeof(NVME_HEALTH_INFO_LOG) )
    )///ProtocolData Offset/Length not valid
    return TU_Bln361095hardwareDataCarrierNVMeGetSMARTvalsUse(OffsetInvalid);

  PCHAR pNMVeHealthInfoLogBgnAddr = (PCHAR)p_protoData + p_protoData->
    ProtocolDataOffset;
  *ppNMVeHealthInfoLog = (NVME_HEALTH_INFO_LOG *) pNMVeHealthInfoLogBgnAddr;
  //memcpy(pNMVeHealthInfoLog, pNMVeHealthInfoLogBgnAddr,
  //  sizeof(NVME_HEALTH_INFO_LOG) );
  //free(pDvcIOctlBuf);
  *ppDvcIOctlBuf = pDvcIOctlBuf;
  return TU_Bln361095hardwareDataCarrierNVMeGetSMARTvalsDef(Sccss);
}

TU_Bln361095hardwareDataCarrierNVMeNmSpcEnd

#endif///include guard