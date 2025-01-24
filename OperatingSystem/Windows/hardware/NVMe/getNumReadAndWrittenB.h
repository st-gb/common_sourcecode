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
 * MS=MicroSoft: http://www.abbreviations.com/abbreviation/MicroSoft
 * Win=WINdows: http://www.abbreviations.com/abbreviation/Windows */\
 !defined TU_Bln361095OpSys_MS_Win_hardware_NVMe_GetNumReadAndWrittenB_h
  #define TU_Bln361095OpSys_MS_Win_hardware_NVMe_GetNumReadAndWrittenB_h

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
 ///TU_Bln361095hardwareDataCarrierNVMeDef
 #include <hardware/dataCarrier/NVMe/NVMe_ID_prefix.h>

TU_Bln361095hardwareDataCarrierNVMeNmSpcBgn

static TU_Bln361095frcInln enum
 TU_Bln361095hardwareDataCarrierNVMeGetSMARTvalsUse(Rslt)
 TU_Bln361095hardwareDataCarrierNVMeDef(GetNVMeNumReadAndWrittenB)(
  HANDLE deviceHandle,
  UCHAR NVMeDataUnitRead[16],
  UCHAR NVMeDataUnitWritten[16]
  )
{
  uint8_t* pDvcIOctlBuf;
  NVME_HEALTH_INFO_LOG * pNMVeHealthInfoLog;
  enum TU_Bln361095hardwareDataCarrierNVMeGetSMARTvalsUse(Rslt)
    nVMeGetSMARTvalsRslt = TU_Bln361095hardwareDataCarrierNVMeUse(GetSMARTvals)(
    deviceHandle,
    &pDvcIOctlBuf,
    &pNMVeHealthInfoLog
    );
  if(nVMeGetSMARTvalsRslt ==
     TU_Bln361095hardwareDataCarrierNVMeGetSMARTvalsUse(AllocBufFaild) )
    return nVMeGetSMARTvalsRslt;
  memcpy(NVMeDataUnitRead, pNMVeHealthInfoLog->DataUnitRead, 16);
  memcpy(NVMeDataUnitWritten, pNMVeHealthInfoLog->DataUnitWritten, 16);
  free(pDvcIOctlBuf);
  return nVMeGetSMARTvalsRslt;
}

TU_Bln361095hardwareDataCarrierNVMeNmSpcEnd

#endif///include guard