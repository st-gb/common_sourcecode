/**(c)from 2023 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
 * @author Stefan Gebauer(TU Berlin matriculation number 361095)
 * builds with:
 * -Microsoft Visual Studio Community 17.5.3 64 bit from year 2022
 * -Apache NetBeans IDE 16 with TDM-GCC 10.3.0-2 64 bit
 * But only shows correct data with Microsoft Visual Studio Community.*/

///C standard library header files:
#include <stdint.h>///uint64_t
#include <stdio.h>///printf([...])

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
 ///TU_Bln361095hardwareDataCarrierNVMeUse(GetSMARTvals)
#include "../../../getSMARTvals.h"
 ///TU_Bln361095hardwareDataCarrierUse(Open)
#include <OperatingSystem/Windows/hardware/dataCarrier/openDataCarrier.h>

/**2^64-1=18.446.744.073.709.551.615=20 digits * 2 + "*(2^64)+" + character
 * string terminating \0 character */
#define maxNumCharsFor128bitDecUint 50

void get16B_decNumStr(char str[], const UCHAR val[16])
{
  uint64_t lowmost8B = *((uint64_t*)&val[0]);
  uint64_t highmost8B = *((uint64_t*)&val[8]);
  if(highmost8B == 0)
    snprintf(str, maxNumCharsFor128bitDecUint, "%llu", lowmost8B);
  else
    ///max unsigned 64 bit number = 2^64-1=18.446.744.073.709.551.616
    snprintf(str, maxNumCharsFor128bitDecUint, "%llu*(2^64)+%llu",
      highmost8B,
      lowmost8B);
}

enum TU_Bln361095progRtrnCodes{ sccss = 0, opnDataCarrierFaild,
  getSMARTvalsFaild
  };

int main()
{
  HANDLE deviceHandle;
  TCHAR dataCarrierPath[MAX_PATH];
   TU_Bln361095hardwareDataCarrierUse(GetPath)(
    _T("0"),///const TCHAR dataCarrierID[],
    dataCarrierPath);
  deviceHandle = TU_Bln361095hardwareDataCarrierUse(Open)(
    dataCarrierPath///const TCHAR dataCarrierPath[]
    );
  if(deviceHandle == INVALID_HANDLE_VALUE)
    return opnDataCarrierFaild;

  NVME_HEALTH_INFO_LOG * pNMVeHealthInfoLog;
  uint8_t* pDvcIOctlBuf;
  enum TU_Bln361095hardwareDataCarrierNVMeGetSMARTvalsUse(Rslt) 
    nVMeGetSMARTvalsRslt = TU_Bln361095hardwareDataCarrierNVMeUse(GetSMARTvals)(
      deviceHandle,
      &pDvcIOctlBuf,
      &pNMVeHealthInfoLog);
  if(nVMeGetSMARTvalsRslt !=
     TU_Bln361095hardwareDataCarrierNVMeGetSMARTvalsUse(Sccss) )
    return getSMARTvalsFaild;

  const unsigned tempInDegC = ((ULONG)pNMVeHealthInfoLog->Temperature[1] << 8 |
    pNMVeHealthInfoLog->Temperature[0])
    //*( (ULONG *)&NMVeHealthInfoLog.Temperature[0])
    ///Kelvin to °C.
    - 273;

  char mediaErrorsStr[maxNumCharsFor128bitDecUint];
  char errorInfoLogEntryCountStr[maxNumCharsFor128bitDecUint];
  char dataUnitsReadStr[maxNumCharsFor128bitDecUint];
  char dataUnitsWrittnStr[maxNumCharsFor128bitDecUint];
  get16B_decNumStr(mediaErrorsStr, pNMVeHealthInfoLog->MediaErrors);
  get16B_decNumStr(errorInfoLogEntryCountStr, pNMVeHealthInfoLog->
    ErrorInfoLogEntryCount);
  get16B_decNumStr(dataUnitsReadStr, pNMVeHealthInfoLog->DataUnitRead);
  get16B_decNumStr(dataUnitsWrittnStr, pNMVeHealthInfoLog->DataUnitWritten);

  printf("S.M.A.R.T. information for data carrier \"%s\" via NVMe:\n"
    "-temperature:%d°C\n"
    "-Available Spares:%d threshold:%d\n"
    "-percentage used:%d\n"
    "-data units read:%s\n"
    "-data units written:%s\n"
    "-media and data integrity errors:%s\n"
    "-number of error log entries:%s\n",
    dataCarrierPath,
    tempInDegC,
    (ULONG)pNMVeHealthInfoLog->AvailableSpare,
    (ULONG)pNMVeHealthInfoLog->AvailableSpareThreshold,
    (ULONG)pNMVeHealthInfoLog->PercentageUsed,
    dataUnitsReadStr,
    dataUnitsWrittnStr,
    mediaErrorsStr,
    errorInfoLogEntryCountStr
    );
  free(pDvcIOctlBuf);
  CloseHandle(deviceHandle);
  return sccss;
}