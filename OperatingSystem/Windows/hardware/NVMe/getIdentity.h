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
 ! defined TU_Bln361095OpSys_Windows_hardware_NVMe_getIdentity_h
   #define TU_Bln361095OpSys_Windows_hardware_NVMe_getIdentity_h

///Standard C(++) library header files:
#include <stdint.h>///uint8_t

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
///TU_Bln361095hardwareDataCarrierNVMeUse
#include "NVMe_ID_prefix.h"
#include <compiler/force_inline.h>///TU_Bln361095frcInln
 /**TU_Bln361095hardwareSMARTnumModelBytes, TU_Bln361095hardwareSMARTnumSNbytes,
  * TU_Bln361095hardwareSMARTnumFWbytes */
#include <hardware/dataCarrier/ATA3Std.h>

//TODO What is the minimal Microsoft compiler version needed to compile?
#if _MSC_VER > 1920
  ///STORAGE_PROTOCOL_NVME_DATA_TYPE etc. in <winioctl.h> included by <Windows.h>
  #include <Windows.h>
  #include <Ntddstor.h>///_STORAGE_PROTOCOL_SPECIFIC_DATA
/**If installing the Visual Studio (Community Edition) (oonfirmed for version
 * 2022), <nvme.h> may be in a path like
 * "C:\Program Files (x86)\Windows Kits\10\Include\10.0.22000.0\shared"?
 */
  #include <nvme.h>
#endif
//TODO What is the minimal GNU C compiler version needed to compile?
#if __GNUC__ >= 10
///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
/**To build with TDM-GCC (confirmed with version 10.3.0-2 64 bit), the following
 * enums and structs must be defined and included additionally to TDM-GCC's
 * header files.*/
 ///in _recent_ Visual Studio's <winioctl.h> :
  #include <OperatingSystem/Windows/hardware/_STORAGE_PROTOCOL_DATA_DESCRIPTOR.h>
  #include <OperatingSystem/Windows/hardware/_STORAGE_PROPERTY_ID_fromVal9.h>
  #include <OperatingSystem/Windows/hardware/NVMe/_STORAGE_PROTOCOL_NVME_DATA_TYPE.h>

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
 ///in _recent_ Visual Studio's <ntddstor.h>:
  /**see
http://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntddstor/ns-ntddstor-_storage_protocol_specific_data
   * : "include Ntddstor.h"*/
  #include <OperatingSystem/Windows/hardware/_STORAGE_PROTOCOL_SPECIFIC_DATA.h>

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
 ///in _recent_ Visual Studio's <nvme.h>:
  /**https://learn.microsoft.com/en-us/windows/win32/api/nvme/ne-nvme-nvme_identify_cns_codes
   * "Header nvme.h"
   * for NVME_IDENTIFY_CNS_CONTROLLER */
  #include <OperatingSystem/Windows/hardware/NVMe/NVME_IDENTIFY_CNS_CODES.h>
/**http://learn.microsoft.com/en-us/windows/win32/api/nvme/ns-nvme-nvme_identify_controller_data
 * : "Header nvme.h" */
  #include <OperatingSystem/Windows/hardware/NVMe/NVME_IDENTIFY_CONTROLLER_DATA.h>
///http://social.msdn.microsoft.com/Forums/aspnet/en-US/24f6bf24-7545-4863-858b-3c8876109b53/where-is-nvmeh-include-file-on-windows-10-kit?forum=windowsgeneraldevelopmentissues
  #define NVME_MAX_LOG_SIZE 0x1000
#endif

#ifdef __cplusplus
/**Def=definition: http://www.abbreviations.com/abbreviation/definition
 * Put definition between "[...]NmSpcBgn" and "[...]NmSpcEnd" #define'd below.*/
  #define TU_Bln361095hardwareDataCarrierNVMeGetIdentityDef(suffix) suffix
/**Nm=name: http://www.abbreviations.com/abbreviation/name
 * Spc=space: http://www.abbreviations.com/abbreviation/Space */
  #define TU_Bln361095hardwareDataCarrierNVMeGetIdentityNmSpc\
    TU_Bln361095hardwareDataCarrierNVMeNmSpc GetIdentity ::
///Bgn=BeGiN :http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095hardwareDataCarrierNVMeGetIdentityNmSpcBgn\
    TU_Bln361095hardwareDataCarrierNVMeNmSpcBgn namespace GetIdentity{
  #define TU_Bln361095hardwareDataCarrierNVMeGetIdentityNmSpcEnd\
    TU_Bln361095hardwareDataCarrierNVMeNmSpcEnd }
  #define TU_Bln361095hardwareDataCarrierNVMeGetIdentityUse(suffix)\
    TU_Bln361095hardwareDataCarrierNVMeGetIdentityDef(suffix)
#else
/**http://gcc.gnu.org/onlinedocs/cpp/Concatenation.html#Concatenation :"The ‘##’
 * preprocessing operator performs token pasting. When a macro is expanded, the
 * two tokens on either side of each ‘##’ operator are combined into a single
 * token, which then replaces the ‘##’ and the two original tokens in the macro
 * expansion."*/
///Def=definition: http://www.abbreviations.com/abbreviation/definition
  #define TU_Bln361095hardwareDataCarrierNVMeGetIdentityDef(suffix)\
    TU_Bln361095hardwareDataCarrierNVMeDef(GetIdentity ## suffix)
/**Nm=name: http://www.abbreviations.com/abbreviation/name
 * Spc=space: http://www.abbreviations.com/abbreviation/Space */
///"C" language has no namespaces->Replace with empty character string.
  #define TU_Bln361095hardwareDataCarrierNVMeGetIdentityNmSpc
///Bgn=BeGiN :http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095hardwareDataCarrierNVMeGetIdentityNmSpcBgn
  #define TU_Bln361095hardwareDataCarrierNVMeGetIdentityNmSpcEnd
  #define TU_Bln361095hardwareDataCarrierNVMeGetIdentityUse(suffix)\
    TU_Bln361095hardwareDataCarrierNVMeGetIdentityDef(suffix)
#endif

TU_Bln361095hardwareDataCarrierNVMeGetIdentityNmSpcBgn

enum TU_Bln361095hardwareDataCarrierNVMeGetIdentityDef(Rslt){
  TU_Bln361095hardwareDataCarrierNVMeGetIdentityDef(Sccss),
  TU_Bln361095hardwareDataCarrierNVMeGetIdentityDef(AllocBufFaild),
  TU_Bln361095hardwareDataCarrierNVMeGetIdentityDef(IOctlFaild),
  TU_Bln361095hardwareDataCarrierNVMeGetIdentityDef(HeaderInvalid),
  TU_Bln361095hardwareDataCarrierNVMeGetIdentityDef(OffsetInvalid),
  TU_Bln361095hardwareDataCarrierNVMeGetIdentityDef(IDinvalid),
  TU_Bln361095hardwareDataCarrierNVMeGetIdentityDef(OtherError)
};

TU_Bln361095hardwareDataCarrierNVMeGetIdentityNmSpcEnd

TU_Bln361095hardwareDataCarrierNVMeNmSpcBgn

/**@param  deviceHandle Handle to the data carrier to get identity information
 *  for. Should have been successfully opened before.
 * @param manufacturer array with >=
 *   TU_Bln361095hardwareSMARTnumModelBytes bytes
 * @param serNo array with >= TU_Bln361095hardwareSMARTnumSNbytes bytes
 * @param firmWare array with >= TU_Bln361095hardwareSMARTnumFWbytes bytes*/
TU_Bln361095frcInln enum TU_Bln361095hardwareDataCarrierNVMeGetIdentityUse(Rslt)
 TU_Bln361095hardwareDataCarrierNVMeDef(GetIdentity)(
  HANDLE deviceHandle,
  //void ** ppBuf
  uint8_t manufacturer[],
  uint8_t serNo[],
  uint8_t firmWare[]
  )
{
/**The following source code is adapted from:
http://learn.microsoft.com/en-us/windows/win32/fileio/working-with-nvme-devices
 * #example-nvme-identify-query */
  BOOL dvcIOctrlRslt;
  PVOID pBuf = NULL;
  DWORD bufSizInB = 0;
  DWORD outBufSizInB = 0;

  PSTORAGE_PROPERTY_QUERY p_storagePropQuery = NULL;
  PSTORAGE_PROTOCOL_SPECIFIC_DATA p_protocolData = NULL;
  PSTORAGE_PROTOCOL_DATA_DESCRIPTOR p_protocolDataDescr = NULL;

  ///Allocate buffer for use.
  bufSizInB = FIELD_OFFSET(STORAGE_PROPERTY_QUERY, AdditionalParameters) +
    sizeof(STORAGE_PROTOCOL_SPECIFIC_DATA) + NVME_MAX_LOG_SIZE;
  pBuf = malloc(bufSizInB);

  if(pBuf == NULL)
    return TU_Bln361095hardwareDataCarrierNVMeGetIdentityUse(AllocBufFaild);

  ///Initialize query data structure to get Identify Controller Data.
  ZeroMemory(pBuf, bufSizInB);

  p_storagePropQuery = (PSTORAGE_PROPERTY_QUERY)pBuf;
  p_protocolDataDescr = (PSTORAGE_PROTOCOL_DATA_DESCRIPTOR)pBuf;
  p_protocolData = (PSTORAGE_PROTOCOL_SPECIFIC_DATA)p_storagePropQuery->
    AdditionalParameters;

  p_storagePropQuery->PropertyId = StorageAdapterProtocolSpecificProperty;
  p_storagePropQuery->QueryType = PropertyStandardQuery;

  p_protocolData->ProtocolType = ProtocolTypeNvme;
  p_protocolData->DataType = NVMeDataTypeIdentify;
  p_protocolData->ProtocolDataRequestValue = NVME_IDENTIFY_CNS_CONTROLLER;
  p_protocolData->ProtocolDataRequestSubValue = 0;
  p_protocolData->ProtocolDataOffset = sizeof(STORAGE_PROTOCOL_SPECIFIC_DATA);
  p_protocolData->ProtocolDataLength = NVME_MAX_LOG_SIZE;

  ///Send request down.
  dvcIOctrlRslt = DeviceIoControl(
    deviceHandle,
    IOCTL_STORAGE_QUERY_PROPERTY,
    pBuf,
    bufSizInB,
    pBuf,
    bufSizInB,
    &outBufSizInB,
    NULL
    );
  if(dvcIOctrlRslt == FALSE)
    return TU_Bln361095hardwareDataCarrierNVMeGetIdentityUse(IOctlFaild);

  // Validate the returned data.
  if( (p_protocolDataDescr->Version != sizeof(STORAGE_PROTOCOL_DATA_DESCRIPTOR))
    || (p_protocolDataDescr->Size != sizeof(STORAGE_PROTOCOL_DATA_DESCRIPTOR)) )
  ///data descriptor header not valid
    return TU_Bln361095hardwareDataCarrierNVMeGetIdentityUse(HeaderInvalid);

  p_protocolData = &p_protocolDataDescr->ProtocolSpecificData;

  if( (p_protocolData->ProtocolDataOffset <
        sizeof(STORAGE_PROTOCOL_SPECIFIC_DATA)) ||
      (p_protocolData->ProtocolDataLength < NVME_MAX_LOG_SIZE)
    )///ProtocolData Offset/Length not valid
    return TU_Bln361095hardwareDataCarrierNVMeGetIdentityUse(OffsetInvalid);

  // Identify Controller Data 
  PNVME_IDENTIFY_CONTROLLER_DATA pNMVeIdentifyCtrllrData =
    (PNVME_IDENTIFY_CONTROLLER_DATA)(
    (PCHAR)p_protocolData + p_protocolData->ProtocolDataOffset);

  if( (pNMVeIdentifyCtrllrData->VID == 0) ||
      (pNMVeIdentifyCtrllrData->NN == 0) )
    return TU_Bln361095hardwareDataCarrierNVMeGetIdentityUse(IDinvalid);
  memcpy(manufacturer, &pNMVeIdentifyCtrllrData->MN,
    TU_Bln361095hardwareSMARTnumModelBytes);
  memcpy(serNo, &pNMVeIdentifyCtrllrData->SN,
    TU_Bln361095hardwareSMARTnumSNbytes);
  memcpy(firmWare, &pNMVeIdentifyCtrllrData->FR,
    TU_Bln361095hardwareSMARTnumFWbytes);
  
  free(pBuf);
  return TU_Bln361095hardwareDataCarrierNVMeGetIdentityUse(Sccss);
}

TU_Bln361095hardwareDataCarrierNVMeNmSpcEnd

#endif///include guard