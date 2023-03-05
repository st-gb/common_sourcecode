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
 ! defined TU_Bln361095OpSys_Windows_hardware_dataCarrier_SMART_getIdentity_h
   #define TU_Bln361095OpSys_Windows_hardware_dataCarrier_SMART_getIdentity_h

///Microsoft Windows operating system header files:
#include <ntdddisk.h>///IDEREGS

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
/**TU_Bln361095OpSysDataCarrierSMART_Def,
 * TU_Bln361095OpSysDataCarrierSMART_NmSpc
 * TU_Bln361095OpSysDataCarrierSMART_NmSpcBgn
 * TU_Bln361095OpSysDataCarrierSMART_NmSpcEnd,
 * TU_Bln361095hardwareDataCarrierSMART_Use */
#include <hardware/dataCarrier/SMART/SMART_ID_prefix.h>
#include <compiler/force_inline.h>///TU_Bln361095frcInln

#ifdef __cplusplus
/**Def=definition: http://www.abbreviations.com/abbreviation/definition
 * Put definition between "[...]NmSpcBgn" and "[...]NmSpcEnd" #define'd below.*/
  #define TU_Bln361095hardwareDataCarrierSMART_getIdentityDef(suffix) suffix
/**Nm=name: http://www.abbreviations.com/abbreviation/name
 * Spc=space: http://www.abbreviations.com/abbreviation/Space */
  #define TU_Bln361095hardwareDataCarrierSMART_getIdentityNmSpc\
    TU_Bln361095hardwareDataCarrierSMART_NmSpc :: getIdentity
///Bgn=BeGiN :http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095hardwareDataCarrierSMART_getIdentityNmSpcBgn
    TU_Bln361095hardwareDataCarrierSMART_NmSpcBgn namespace getIdentity{
  #define TU_Bln361095hardwareDataCarrierSMART_getIdentityNmSpcEnd
    TU_Bln361095hardwareDataCarrierSMART_NmSpcEnd }
  #define TU_Bln361095hardwareDataCarrierSMART_getIdentityUse(suffix)\
    TU_Bln361095hardwareDataCarrierSMART_Use( getIdentity :: suffix)
#else
/**http://gcc.gnu.org/onlinedocs/cpp/Concatenation.html#Concatenation :"The ‘##’
 * preprocessing operator performs token pasting. When a macro is expanded, the
 * two tokens on either side of each ‘##’ operator are combined into a single
 * token, which then replaces the ‘##’ and the two original tokens in the macro
 * expansion."*/
///Def=definition: http://www.abbreviations.com/abbreviation/definition
  #define TU_Bln361095hardwareDataCarrierSMART_getIdentityDef(suffix)\
    TU_Bln361095hardwareDataCarrierSMART_Def(getIdentity ## suffix)
/**Nm=name: http://www.abbreviations.com/abbreviation/name
 * Spc=space: http://www.abbreviations.com/abbreviation/Space */
///"C" language has no namespaces->Replace with empty character string.
  #define TU_Bln361095hardwareDataCarrierSMART_getIdentityNmSpc /** ->empty*/
///Bgn=BeGiN :http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095hardwareDataCarrierSMART_getIdentityNmSpcBgn /** ->empty*/
  #define TU_Bln361095hardwareDataCarrierSMART_getIdentityNmSpcEnd /** ->empty*/
  #define TU_Bln361095hardwareDataCarrierSMART_getIdentityUse(suffix)\
    TU_Bln361095hardwareDataCarrierSMART_getIdentityDef(suffix)
#endif

///To scope enum elements in "getIdentity" namespace.
TU_Bln361095hardwareDataCarrierSMART_getIdentityNmSpcBgn

enum TU_Bln361095hardwareDataCarrierSMART_getIdentityDef(Rslt){
  TU_Bln361095hardwareDataCarrierSMART_getIdentityDef(Sccss),///SuCCeSS
  TU_Bln361095hardwareDataCarrierSMART_getIdentityDef(Faild)///FAILeD
};

TU_Bln361095hardwareDataCarrierSMART_getIdentityNmSpcEnd

TU_Bln361095hardwareDataCarrierSMART_NmSpcBgn

///Make function inline to avoid multiple definitions of it.
TU_Bln361095frcInln
 enum TU_Bln361095hardwareDataCarrierSMART_getIdentityUse(Rslt)
  TU_Bln361095hardwareDataCarrierSMART_Def(getIdentity)(
  const HANDLE dataCarrierHandle)
{
  DWORD bytesReturned;

  IDEREGS iDEREGS;
/**http://learn.microsoft.com/en-us/windows-hardwar<e/drivers/ddi/ntdddisk/ns-ntdddisk-_sendcmdinparams
 * "The irDriveRegs.bCommandReg member specifies ID_CMD when identify data is
 * requested"*/
  iDEREGS.bCommandReg = ID_CMD;
/**http://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntdddisk/ns-ntdddisk-_sendcmdinparams
 * "The irDriveRegs.bFeaturesReg member must specify a SMART subcommand."*/
  iDEREGS.bFeaturesReg = READ_ATTRIBUTES;//0;//;

/**http://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntdddisk/ns-ntdddisk-_sendcmdinparams
 * "The SENDCMDINPARAMS structure is used with the SMART_SEND_DRIVE_COMMAND and
 * SMART_RCV_DRIVE_DATA I/O control code requests." */
  SENDCMDINPARAMS sENDCMDINPARAMS = {
/**http://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntdddisk/ns-ntdddisk-_sendcmdinparams
 * "Contains the buffer size, in bytes."*/
    0/*512*/,
    iDEREGS
/**http://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntdddisk/ns-ntdddisk-_sendcmdinparams
    *"This member is opaque. Do not use it. The operating system ignores this
    * member, because the physical drive that receives the request depends on
    * the handle that the caller uses when making the request."*/
  ///UCHAR   bDriveNumber;
/**http://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntdddisk/ns-ntdddisk-_sendcmdinparams
 * "Pointer to the input buffer."*/
  ///UCHAR bBuffer[1]
  };

  DRIVERSTATUS dRIVERSTATUS;
  memset(&dRIVERSTATUS, 0, sizeof(dRIVERSTATUS));
//  UCHAR buf[IDENTIFY_BUFFER_SIZE];
  SENDCMDOUTPARAMS sENDCMDOUTPARAMS = { IDENTIFY_BUFFER_SIZE, dRIVERSTATUS };
  BYTE outBuffer[sizeof(SENDCMDOUTPARAMS) + IDENTIFY_BUFFER_SIZE];
  memset(outBuffer, 0, sizeof(outBuffer));
  memcpy(outBuffer, & sENDCMDOUTPARAMS, sizeof(SENDCMDOUTPARAMS));
  
  ///https://learn.microsoft.com/en-us/windows/win32/api/ioapiset/nf-ioapiset-deviceiocontrol
  const WINBOOL dvcIoCtrlRslt = DeviceIoControl(
///see https://learn.microsoft.com/en-us/windows/win32/devio/calling-deviceiocontrol
    dataCarrierHandle,///[in] HANDLE hDevice,
/**http://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntdddisk/ns-ntdddisk-_sendcmdinparams
 * :"The SMART_RCV_DRIVE_DATA control code returns the ATA-2 identify data [...]
 *  for the device." */
    SMART_RCV_DRIVE_DATA,///[in] DWORD dwIoControlCode,
    (LPVOID) & sENDCMDINPARAMS,///[in, optional]      LPVOID       lpInBuffer,
/** http://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntdddisk/ns-ntdddisk-_sendcmdinparams
 * : "Parameters.DeviceIoControl.InputBufferLength specifies the size, in bytes,
 * of the input buffer, which must be >= (sizeof(SENDCMDINPARAMS) - 1)."*/
    sizeof(sENDCMDINPARAMS),///[in] DWORD nInBufferSize,
    (LPVOID) & outBuffer,///[out, optional] LPVOID lpOutBuffer,
    sizeof(outBuffer),///[in] DWORD nOutBufferSize,
    & bytesReturned,///[out, optional]     LPDWORD      lpBytesReturned,
    NULL///[in, out, optional] LPOVERLAPPED lpOverlapped
    );
  return dvcIoCtrlRslt == FALSE ?
    TU_Bln361095hardwareDataCarrierSMART_getIdentityUse(Faild) : 
	TU_Bln361095hardwareDataCarrierSMART_getIdentityUse(Sccss);
}

TU_Bln361095hardwareDataCarrierSMART_NmSpcEnd

#endif///Include guard