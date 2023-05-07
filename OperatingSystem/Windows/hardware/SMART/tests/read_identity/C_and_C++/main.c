/**(c) from 2023 by Stefan Gebauer(Computer Science Master from TU Berlin)
 * @author Stefan Gebauer(TU Berlin matriculation number 361095)*/

///C standard header files:
#include <stdio.h>///printf(...)

///Microsoft Windows operating system header files:
#include <windows.h>///ULONG in ntddstor.h included by <ntdddisk.h>

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
/**TU_Bln361095hardwareSMARTnumModelBytes, TU_Bln361095hardwareSMARTnumSNbytes,
 * TU_Bln361095hardwareSMARTnumFWbytes */
#include <hardware/dataCarrier/ATA3Std.h>
/**TU_Bln361095hardwareDataCarrierUse(GetPath),
 * TU_Bln361095hardwareDataCarrierUse(Open)*/
#include <OperatingSystem/Windows/hardware/dataCarrier/openDataCarrier.h>
///TU_Bln361095hardwareDataCarrierUse(GetIdentity)
#include <OperatingSystem/Windows/hardware/dataCarrier/getIdentity.h>

enum progRtrnCodes{success = 0, openingDataCarrierFaild,
  gettingSMARTidentityFaild, getStorageDvcInfoFaild};

void printIdentityToStdOut(
  uint8_t manufacturer[],
  uint8_t firmWare[],
  uint8_t serNo[]
  )
{
//  char identityFmtStr[];
//  sprintf(identityFmtStr, "serial number:%ds", numSMART_SNbytes);
//    "serial number:%20s\n"), identifyControllerData->SN);
  printf("manufacturer:%.*s\n", TU_Bln361095hardwareSMARTnumModelBytes,
    manufacturer);
  printf("serial number:%.*s\n", TU_Bln361095hardwareSMARTnumSNbytes,
    serNo);
  printf("firmware:%.*s\n", TU_Bln361095hardwareSMARTnumFWbytes, firmWare);
}

int main()
{
  ///TCHAR ->"char"(ANSI) or ->"wchar_t"(Unicode)
  TCHAR dataCarrierPath[MAX_PATH];
  TU_Bln361095hardwareDataCarrierUse(GetPath)(_T("0"),
    dataCarrierPath);
  HANDLE dataCarrierHandle = TU_Bln361095hardwareDataCarrierUse(
    Open)(dataCarrierPath);

  printf("data carrier handle:%p\n", dataCarrierHandle);
  if(dataCarrierHandle == INVALID_HANDLE_VALUE)
  {
    _tprintf(_T("Opening data carrier \"%s\" failed. Operating system error "
      "code:%d\n"), dataCarrierPath, GetLastError() );
    return openingDataCarrierFaild;
  }
  else
    _tprintf(_T("Opening data carrier \"%s\" succeeded.\n"), dataCarrierPath);
  
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
    _tprintf(_T("Getting identity (manufacturer/model, serial number [...]) "
      "failed for data carrier \"%s\":%s\n"), dataCarrierPath,
      TU_Bln361095hardwareDataCarrierGetIdentityEnRsltMsgs[
        getdataCarrierIdentityRslt]);
  return success;
}
