/**(c) from 2023 by Stefan Gebauer(Computer Science Master from TU Berlin)
 * @author Stefan Gebauer(TU Berlin matriculation number 361095)*/

///C standard library header files:
 #include <stdio.h>///printf(...)

///Microsoft Windows operating system header files:
 /**MAX_PATH, HANDLE, CreateFile, FILE_SHARE_READ, FILE_SHARE_WRITE,
  * OPEN_EXISTING etc.*/
 #include <windows.h>///ULONG in ntddstor.h included by <ntdddisk.h>

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
 /**TU_Bln361095hardwareSMARTnumModelBytes, TU_Bln361095hardwareSMARTnumSNbytes,
  * TU_Bln361095hardwareSMARTnumFWbytes */
 #include <hardware/dataCarrier/ATA3Std.h>
 ///TU_Bln361095hardwareDataCarrierUse(GetPath),
 #include <OperatingSystem/Windows/hardware/dataCarrier/getDataCarrierPath.h>
 ///TU_Bln361095hardwareDataCarrierUse(GetIdentity)
 #include <OperatingSystem/Windows/hardware/dataCarrier/getIdentity.h>
 ///TU_Bln361095hardwareDataCarrierUse(Open)
 #include <OperatingSystem/Windows/hardware/dataCarrier/openDataCarrier.h>
 #include <CstdLib/strcmpRtrnCds.h>///TU_Bln361095CstdLibStrcmpUse(EqlStrs)

///_This_ repository's files:
 #include "handleCmdLneOpts.h"///C(++) handleCmdLneOpts(...)

enum progRtrnCodes{success = 0, openingDataCarrierFaild,
  gettingSMARTidentityFaild, getStorageDvcInfoFaild};

///from https://stackoverflow.com/questions/69479818/nvme-s-m-a-r-t-data-retrieval :
//https://learn.microsoft.com/en-us/windows/win32/fileio/working-with-nvme-devices#temperature-queries

void printIdentityToStdOut(
  const uint8_t manufacturer[],
  const uint8_t firmWare[],
  const uint8_t serNo[]
  )
{
//  char identityFmtStr[];
//  sprintf(identityFmtStr, "serial number:%ds", numSMART_SNbytes);
//    "serial number:%20s\n"), identifyControllerData->SN);
  printf("manufacturer:\"%.*s\"\n", TU_Bln361095hardwareSMARTnumModelBytes,
    manufacturer);
  printf("serial number:\"%.*s\"\n", TU_Bln361095hardwareSMARTnumSNbytes,
    serNo);
  printf("firmware:\"%.*s\"\n", TU_Bln361095hardwareSMARTnumFWbytes, firmWare);
}

const char * const getDataCarrierPath(
  char fullDataCarrierPath[], const char dataCarrierPath[])
{
  const char * p_fullDataCarrierPath;
  if(strcmp(dataCarrierPath, "") == TU_Bln361095CstdLibStrcmpUse(EqlStrs) )
  {
    TU_Bln361095hardwareDataCarrierUse(GetPathA)("0",
      fullDataCarrierPath);
    p_fullDataCarrierPath = fullDataCarrierPath;
  }
  else if(strncmp(dataCarrierPath,
    TU_Bln361095OpsSysMS_WinDataCarrierPathPrefixA, 
    sizeof(TU_Bln361095OpsSysMS_WinDataCarrierPathPrefixA) - 1) !=
    TU_Bln361095CstdLibStrcmpUse(EqlStrs) )
  {
    char *endPtr;
    strtol(dataCarrierPath, &endPtr, 10);
    if(endPtr != NULL)///only a number
      TU_Bln361095hardwareDataCarrierUse(GetPathA)(dataCarrierPath,
        fullDataCarrierPath);
    p_fullDataCarrierPath = fullDataCarrierPath;
  }
  else
    p_fullDataCarrierPath = dataCarrierPath;
  return p_fullDataCarrierPath;
}

int main(int prgArgCnt, char ** progArgs)
{
  ///TCHAR ->"char"(ANSI) or ->"wchar_t"(Unicode)
  char dataCarrierPath[MAX_PATH] = "";
  char fullDataCarrierPath[MAX_PATH] = "";
  printf("Program for showing data carrier identity(model, serial number, "
    "firmware revision) information.\n");
#ifdef __cplusplus
  TU_Bln361095cmnSrcNmSpc::cxxopts::handleCmdLineOpts(prgArgCnt, progArgs,
    dataCarrierPath);
#else
  handleCmdLineOpts(prgArgCnt, progArgs, dataCarrierPath);
#endif
  const char * p_fullDataCarrierPath = getDataCarrierPath(
    fullDataCarrierPath, dataCarrierPath);

  const HANDLE dataCarrierHandle = TU_Bln361095hardwareDataCarrierUse(
    Open)(p_fullDataCarrierPath);

  printf("data carrier handle:%p\n", dataCarrierHandle);
  if(dataCarrierHandle == INVALID_HANDLE_VALUE)
  {
    printf("Opening data carrier \"%s\" failed. Operating system error "
      "code:%d\n", fullDataCarrierPath, GetLastError() );
    return openingDataCarrierFaild;
  }
  else
    printf("Opening data carrier \"%s\" succeeded.\n", fullDataCarrierPath);
  
  uint8_t manufacturer[TU_Bln361095hardwareSMARTnumModelBytes];
  uint8_t serNo[TU_Bln361095hardwareSMARTnumSNbytes];
  uint8_t firmWare[TU_Bln361095hardwareSMARTnumFWbytes];

  enum TU_Bln361095hardwareDataCarrierGetIdentityUse(Rslt)
    getdataCarrierIdentityRslt = TU_Bln361095hardwareDataCarrierUse(
      GetIdentity)(
        dataCarrierHandle,
        manufacturer,
        serNo,
        firmWare);
  CloseHandle(dataCarrierHandle);
  if(getdataCarrierIdentityRslt ==
    TU_Bln361095hardwareDataCarrierGetIdentityUse(Sccss) )
      printIdentityToStdOut(manufacturer, firmWare, serNo);
  else
    printf("Getting identity (manufacturer/model, serial number [...]) failed "
      "for data carrier \"%s\":%s\n", fullDataCarrierPath,
      TU_Bln361095hardwareDataCarrierGetIdentityEnRsltMsgs[
        getdataCarrierIdentityRslt]);
  return success;
}
