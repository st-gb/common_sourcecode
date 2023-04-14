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
 * cmn=CoMmoN: http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe: http://www.abbreviations.com/abbreviation/Source
 * OpSys=OPerating SYStem: http://www.abbreviations.com/OpSys */\
 ! defined TU_Bln361095cmnSrc_OpSys_Windows_hardware_dataCarrier_getIdentity_h
   #define TU_Bln361095cmnSrc_OpSys_Windows_hardware_dataCarrier_getIdentity_h

///Stefan Gebauer's(TU Berlin mat.#361095)~"common_sourcecode" repository files:
 /**TU_Bln361095hardwareDataCarrierDef, TU_Bln361095hardwareDataCarrierNmSpc,
  * TU_Bln361095hardwareDataCarrierNmSpcBgn,
  * TU_Bln361095hardwareDataCarrierNmSpcEnd */
#include <hardware/dataCarrier/dataCarrier_ID_prefix.h>
 ///TU_Bln361095hardwareDataCarrierUse(GetStorageDvcInfo)
#include <OperatingSystem/Windows/hardware/dataCarrier/getStorageDvcInfo.h>
 /**TU_Bln361095hardwareDataCarrierNVMeUse(GetIdentity),
  * TU_Bln361095hardwareDataCarrierNVMeGetIdentityUse(Rslt),
  * TU_Bln361095hardwareDataCarrierNVMeGetIdentityUse(Sccss) */
#include <OperatingSystem/Windows/hardware/NVMe/getIdentity.h>
 /**TU_Bln361095hardwareDataCarrierSMART_Use(getIdentity),
  * TU_Bln361095hardwareDataCarrierSMART_getIdentityUse(Rslt),
  * TU_Bln361095hardwareDataCarrierSMART_getIdentityUse(Sccss) */
#include <OperatingSystem/Windows/hardware/SMART/getIdentity.h>

/**Use these preprocessor macros in source code for example to enable both C and
 * C++.*/
#ifdef __cplusplus
/**Def=definition: http://www.abbreviations.com/abbreviation/definition
 * Put definition between "[...]NmSpcBgn" and "[...]NmSpcEnd" #define'd below.*/
  #define TU_Bln361095hardwareDataCarrierGetIdentityDef(suffix) suffix
/**Nm=name: http://www.abbreviations.com/abbreviation/name
 * Spc=space: http://www.abbreviations.com/abbreviation/Space
 * Do not append "::" right of the rightmost namespace name to enable
 * "using namespace [...]GetIdentityNmSpc" */
  #define TU_Bln361095hardwareDataCarrierGetIdentityNmSpc \
    TU_Bln361095hardwareDataCarrierNmSpc :: GetIdentity
///Bgn=BeGiN :http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095hardwareDataCarrierGetIdentityNmSpcBgn \
    TU_Bln361095hardwareDataCarrierNmSpcBgn namespace GetIdentity{
  #define TU_Bln361095hardwareDataCarrierGetIdentityNmSpcEnd \
    TU_Bln361095hardwareDataCarrierNmSpcEnd }
  #define TU_Bln361095hardwareDataCarrierGetIdentityUse(suffix)\
    TU_Bln361095hardwareDataCarrierGetIdentityNmSpc :: suffix
#else
///Def=definition: http://www.abbreviations.com/abbreviation/definition
  #define TU_Bln361095hardwareDataCarrierGetIdentityDef(suffix)\
    TU_Bln361095hardwareDataCarrierDef(GetIdentity##suffix)
/**Nm=name: http://www.abbreviations.com/abbreviation/name
 * Spc=space: http://www.abbreviations.com/abbreviation/Space */
///"C" language has no namespaces->Replace with empty character string.
  #define TU_Bln361095hardwareDataCarrierGetIdentityNmSpc /** ->empty */
///Bgn=BeGiN :http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095hardwareDataCarrierGetIdentityNmSpcBgn /** ->empty */
  #define TU_Bln361095hardwareDataCarrierGetIdentityNmSpcEnd /** ->empty */
  #define TU_Bln361095hardwareDataCarrierGetIdentityUse(suffix)\
    TU_Bln361095hardwareDataCarrierGetIdentityDef(suffix)
#endif

///lit=LITeral:http://www.allacronyms.com/literal/abbreviated
#define TU_Bln361095successASCIIlit "success"
#define TU_Bln361095enGetStorageDvcDescFaildASCIIlit\
  "getting storage device descriptor failed"
#define TU_Bln361095enGetATAidentityFaildASCIIlit\
  "getting identity via ATA failed"
#define TU_Bln361095enGetNVMeIdentityFaildASCIIlit\
  "getting identity via NVMe failed"
#define TU_Bln361095enBusTypeUnhandledASCIIlit "bus type not handled"

#ifdef __cplusplus
/**Must declare as extern "C" if compiling as C++, else Microsoft Visual Studio
 * gives linker errors.*/
  extern "C" {
#endif
   extern char* TU_Bln361095hardwareDataCarrierGetIdentityEnRsltMsgs[];
#ifdef __cplusplus
 }///extern "C"
#endif

TU_Bln361095hardwareDataCarrierGetIdentityNmSpcBgn

enum TU_Bln361095hardwareDataCarrierGetIdentityDef(Rslt){
  TU_Bln361095hardwareDataCarrierGetIdentityDef(Sccss) = 0,
  TU_Bln361095hardwareDataCarrierGetIdentityDef(GetStorageDvcDescFaild),
  TU_Bln361095hardwareDataCarrierGetIdentityDef(GetATAidentityFaild),
  TU_Bln361095hardwareDataCarrierGetIdentityDef(GetNVMeIdentityFaild),
  TU_Bln361095hardwareDataCarrierGetIdentityDef(BusTypeNotHandld)
};

TU_Bln361095hardwareDataCarrierGetIdentityNmSpcEnd

TU_Bln361095hardwareDataCarrierNmSpcBgn

TU_Bln361095frcInln enum TU_Bln361095hardwareDataCarrierGetIdentityUse(Rslt)
  TU_Bln361095hardwareDataCarrierDef(GetIdentity)(
  HANDLE dataCarrierHandle,
  uint8_t manufacturer[],
  uint8_t serNo[],
  uint8_t firmWare[])
{
///http://learn.microsoft.com/en-us/windows/win32/api/winioctl/ns-winioctl-storage_device_descriptor
  STORAGE_DEVICE_DESCRIPTOR storageDvcDesc;
  //TU_Bln361095hardwareDataCarrierUse(Info) dataCarrierInfoRslt =
  BOOL bDvcIOctrlRslt =
    TU_Bln361095hardwareDataCarrierUse(GetStorageDvcInfo)(dataCarrierHandle,
      &storageDvcDesc);
  if(bDvcIOctrlRslt != TRUE)
    return TU_Bln361095hardwareDataCarrierGetIdentityUse(
      GetStorageDvcDescFaild);

  switch(storageDvcDesc.BusType)
  {
    case BusTypeAta:
    case BusTypeSata:
     //LOGN_DEBUG("Bus type is ATA or SATA\n");
     {
      enum TU_Bln361095hardwareDataCarrierSMART_getIdentityUse(Rslt)
       SMARTgetIdentityRslt = TU_Bln361095hardwareDataCarrierSMART_Use(
        getIdentity)(
  	     dataCarrierHandle);
      if(SMARTgetIdentityRslt !=
         TU_Bln361095hardwareDataCarrierSMART_getIdentityUse(Sccss) )
        return TU_Bln361095hardwareDataCarrierGetIdentityUse(
          GetATAidentityFaild);
     }
      break;
    case BusTypeNvme:
    {
      //LOGN_DEBUG("Bus type is NVMe\n");
      enum TU_Bln361095hardwareDataCarrierNVMeGetIdentityUse(Rslt) getIdentityRslt =
        TU_Bln361095hardwareDataCarrierNVMeUse(GetIdentity)(
         dataCarrierHandle,
         manufacturer,
         serNo,
         firmWare);
      if(getIdentityRslt != TU_Bln361095hardwareDataCarrierNVMeGetIdentityUse(
	      Sccss) )
        return TU_Bln361095hardwareDataCarrierGetIdentityUse(
		      GetNVMeIdentityFaild);
    }
      break;
    default:
      return TU_Bln361095hardwareDataCarrierGetIdentityUse(
        BusTypeNotHandld);
  }
  return TU_Bln361095hardwareDataCarrierGetIdentityUse(Sccss);
}

TU_Bln361095hardwareDataCarrierNmSpcEnd

#endif///include guard
