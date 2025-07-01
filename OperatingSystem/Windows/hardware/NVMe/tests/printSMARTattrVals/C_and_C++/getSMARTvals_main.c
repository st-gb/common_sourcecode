/**(c)from 2023 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
 * @author Stefan Gebauer(TU Berlin matriculation number 361095)
 * builds with:
 * -Apache NetBeans IDE 16 with TDM-GCC 10.3.0-2 64 bit
 * -Microsoft Visual Studio Community 17.5.3 64 bit from year 2022 */

///C standard library header files:
 #include <stdint.h>///uint64_t
 #include <stdio.h>///printf([...])
 #include <tchar.h>///_T(...)

///Stefan Gebauer's(TU Berlin matric. number 361095) ~"cmnSrc" repository files:
 ///TU_Bln361095castToCharPtr
 #include <compiler/GCC/avoid_write_strings_warning.h>
 ///TU_Bln361095_16B_uIntWriteAsDecNumToCharStr(...)
 #include <dataType/bigUint/useMultiprecisionFromBoostOrGNU.h>
 ///TU_Bln361095hardwareDataCarrierNVMeUse(GetSMARTvals),
 // struct NVME_HEALTH_INFO_LOG
 #include "../../../getSMARTvals.h"
 #include <hardware/CPU/fastest_data_type.h>///TU_Bln361095CPUfaststUint
 ///TU_Bln361095dataCarrierNVMeSMARTattrUse(GetTempInDegC)
 #include <hardware/dataCarrier/NVMe/NVMe_SMART_attr.h>
 ///TU_Bln361095OpSysProcessCmdLneArgsParseUse(ArgsUnset)
 #include <OperatingSystem/Process/CmdLneArgs/parseCmdLneArgs.h>
 /**TU_Bln361095hardwareDataCarrierUse(GetPath)<=>
  * TU_Bln361095hardwareDataCarrierGetPath(...),
  * TU_Bln361095::hardware::DataCarrier::GetPath(...) */
 #include <OperatingSystem/Windows/hardware/dataCarrier/getDataCarrierPath.h>
 /**TU_Bln361095hardwareDataCarrierUse(Open)(...)<=>
  * TU_Bln361095hardwareDataCarrierOpen(...),
  * TU_Bln361095::hardware::DataCarrier::Open(...) */
 #include <OperatingSystem/Windows/hardware/dataCarrier/openDataCarrier.h>
 ///struct NVME_HEALTH_INFO_LOG
 #include <OperatingSystem/Windows/hardware/NVMe/NVME_HEALTH_INFO_LOG.h>

/** Cast to number to not print as character */
#define castToNumber (TU_Bln361095CPUuse(faststUint) ) 

enum TU_Bln361095progRtrnCodes{sccss = 0, opnDataCarrierFaild,
  getSMARTvalsFaild
  };

static char * TU_Bln361095enProgExitMsgs///ENglish PROGram EXIT MeSsageS
  [] = {
  TU_Bln361095castToCharPtr "success",
  TU_Bln361095castToCharPtr "opening data carrier failed",
  TU_Bln361095castToCharPtr "getting S.M.A.R.T. values failed"
  };

/**Get data carrier ID from CoMmanD LiNE ARGuments.
 * @param cmdLneArgCnt CoMmanD LiNE ARGument CouNT(=number)
 * @param cmdLneArgArr coMmanD LiNE ARGument ARRay
 * @param dataCarrierID filled either:
 *  - from command line arguments to this program
 *  - with 1st possible data carrier ID as default value in case of error in
 *    processing the command line arguments passed to this function */
static inline TU_Bln361095CPUuse(faststUint) getDataCarrierIDfromCmdLneArgs(
  const int cmdLneArgCnt,
  const char * const cmdLneArgArr[],
  char dataCarrierID[2]
  )
{
#ifdef cxxoptsDir
  #pragma message("\"cxxoptsDir\" set as preprocessor macro.")
  //return getDataCarrierIDfromCxxopts(cmdLneArgCnt, cmdLneArgArr, dataCarrierID);
  //cxxopts::exceptions::exception cxxoptsExc;
  std::string cxxoptsExcMsg;

  std::string usageProgName(cmdLneArgArr[
    TU_Bln361095::OpSys::Process:: CmdLneArgs::ProgPathIdx]);
  cxxopts::Options cxxoptions("printNVMeSMARTattrVals",
    "Print NVMe S.M.A.R.T. attibute values"/**one-line program description*/);
  TU_Bln361095::CPU::faststUint getDataCarrierIDfromCxxoptsRslt =
    /*TU_Bln361095::hardware::NVMe::*/cxxopts::getDataCarrierID(cmdLneArgCnt,
      cmdLneArgArr, dataCarrierID, /*cxxoptsExc*/ cxxoptsExcMsg, cxxoptions);
  if (getDataCarrierIDfromCxxoptsRslt ==
    TU_Bln361095::OpSys::Process::CmdLneArgs::Parse::Error)
  {
    printf("Getting command line option for \"dataCarrier\" failed:%s\n"
      "->using default value \"%s\" for it.\n", //cxxoptsExc.what()
      cxxoptsExcMsg.c_str(), dataCarrierID);
    const std::string stdstrCxxOptionsHelp = cxxoptions.help();
    printf("Here is the help/are the possible options for this application:\n"
      "\n%s\n",
      stdstrCxxOptionsHelp.c_str() );
  }
  return getDataCarrierIDfromCxxoptsRslt;
#else
  #pragma message("\"cxxOptsDir\" NOT set as preprocessor macro.")
#endif
  return TU_Bln361095OpSysProcessCmdLneArgsParseUse(ArgsUnset);
}

/**"static"=Limit the scope/visibility to this compilation for more security.*/
static /*TCHAR*/char dataCarrierPath[MAX_PATH];

static TU_Bln361095frcInln void exitProg(
  const enum TU_Bln361095progRtrnCodes rtrnCd,
  HANDLE deviceHandle)
{
  if(rtrnCd != sccss)
  printf("%s (for data carrier %s):"
    "Operating System error code="
    "%d"
    "\n",
    TU_Bln361095enProgExitMsgs[rtrnCd], dataCarrierPath,
    GetLastError() );
  if(rtrnCd != opnDataCarrierFaild)
    CloseHandle(deviceHandle);
  exit(rtrnCd);
}

static TU_Bln361095frcInln void printNVMeSMARTvals(
  NVME_HEALTH_INFO_LOG * const pNMVeHealthInfoLog,
  char dataCarrierPath[MAX_PATH]
  )
{
  const TU_Bln361095CPUuse(faststUint) tempInDegC =
    TU_Bln361095dataCarrierNVMeSMARTattrUse(GetTempInDegC)(pNMVeHealthInfoLog->
    Temperature);

  char mediaErrorsStr[TU_Bln361095_16B_UintMaxNumCharsForDecNum];
  char errorInfoLogEntryCountStr[TU_Bln361095_16B_UintMaxNumCharsForDecNum];
  char dataUnitsReadStr[TU_Bln361095_16B_UintMaxNumCharsForDecNum];
  char dataUnitsWrittnStr[TU_Bln361095_16B_UintMaxNumCharsForDecNum];
  TU_Bln361095_16B_uIntUse(WriteAsDecNumToCharStr)(pNMVeHealthInfoLog->
    MediaErrors, mediaErrorsStr);
  TU_Bln361095_16B_uIntUse(WriteAsDecNumToCharStr)(pNMVeHealthInfoLog->
    ErrorInfoLogEntryCount, errorInfoLogEntryCountStr);
  TU_Bln361095_16B_uIntUse(WriteAsDecNumToCharStr)
    (pNMVeHealthInfoLog->DataUnitRead, dataUnitsReadStr);
  TU_Bln361095_16B_uIntUse(WriteAsDecNumToCharStr)
    (pNMVeHealthInfoLog->DataUnitWritten, dataUnitsWrittnStr);

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
    castToNumber pNMVeHealthInfoLog->AvailableSpare,
    castToNumber pNMVeHealthInfoLog->AvailableSpareThreshold,
    castToNumber pNMVeHealthInfoLog->PercentageUsed,
    dataUnitsReadStr,
    dataUnitsWrittnStr,
    mediaErrorsStr,
    errorInfoLogEntryCountStr
    );
}

/** @param cmdLneArgCnt CoMmanD LiNE ARGument CouNT
 *  @param cmdLneArgs coMmanD LiNE ARGumentS */
int main(int cmdLneArgCnt, char * cmdLneArgs[])
{
  printf("Software application to show NVMe S.M.A.R.T. attribute value "
    "information.\n"
    /**Outputting the date and time of day when building to console/terminal/
     * standard output enables that the user to see which version is run(This
     * improves quality assurance).*/
    "Build date and time of day of this executable:%s %s\n\n", __DATE__,
    __TIME__);
  HANDLE deviceHandle;

  char dataCarrierID[2] = "0";
  TU_Bln361095CPUuse(faststUint) getDataCarrierIDfromCmdLneArgsRslt =
    getDataCarrierIDfromCmdLneArgs(
      cmdLneArgCnt,
      /**Cast to function parameter type to avoid (g++/GNU C++) compiler
       *  warning.*/
      (const char * const *) cmdLneArgs,
      dataCarrierID);
  TU_Bln361095hardwareDataCarrierUse(//GetPath)(_T("0"),
    GetPathA)(//"0",
      dataCarrierID,
      ///const TCHAR dataCarrierID[],
      dataCarrierPath);
  deviceHandle = TU_Bln361095hardwareDataCarrierUse(//Open)(
    OpenA)(
    dataCarrierPath///const TCHAR dataCarrierPath[]
    );
  if(//deviceHandle == INVALID_HANDLE_VALUE
    TU_Bln361095hardwareDataCarrierUse(OpnFaild)(deviceHandle)
    )
  {
    exitProg(opnDataCarrierFaild, deviceHandle);
  }

  NVME_HEALTH_INFO_LOG * pNMVeHealthInfoLog;
  uint8_t * pDvcIOctlBuf;
  enum TU_Bln361095hardwareDataCarrierNVMeGetSMARTvalsUse(Rslt) 
    nVMeGetSMARTvalsRslt = TU_Bln361095hardwareDataCarrierNVMeUse(GetSMARTvals)(
      deviceHandle,
      &pDvcIOctlBuf,
      &pNMVeHealthInfoLog);
  if(nVMeGetSMARTvalsRslt !=
     TU_Bln361095hardwareDataCarrierNVMeGetSMARTvalsUse(Sccss) )
  {
//    printf("%s\n", TU_Bln361095enProgExitMsgs[getSMARTvalsFaild]);
    if(nVMeGetSMARTvalsRslt !=
      TU_Bln361095hardwareDataCarrierNVMeGetSMARTvalsUse(AllocBufFaild) )
      free(pDvcIOctlBuf);
    //CloseHandle(deviceHandle);
    exitProg(getSMARTvalsFaild, deviceHandle);
    //return getSMARTvalsFaild;
  }

  printNVMeSMARTvals(pNMVeHealthInfoLog, dataCarrierPath);
  free(pDvcIOctlBuf);
  //CloseHandle(deviceHandle);
  exitProg(sccss, deviceHandle);
  //return sccss;
}
