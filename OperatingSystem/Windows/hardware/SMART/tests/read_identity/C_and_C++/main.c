/**(c) from 2023 by Stefan Gebauer(Computer Science Master from TU Berlin)
 * @author Stefan Gebauer(TU Berlin matriculation number 361095)*/

///C standard header files:
#include <stdio.h>///printf(...)

///Microsoft Windows operating system header files:
#include <windows.h>///ULONG in ntddstor.h included by <ntdddisk.h>

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
/**TU_Bln361095hardwareDataCarrierSMART_Use(getDataCarrierPath),
 * TU_Bln361095hardwareDataCarrierSMART_Use(openDataCarrier)*/
#include <OperatingSystem/Windows/hardware/SMART/openDataCarrier.h>
#include <OperatingSystem/Windows/hardware/SMART/getIdentity.h>

enum progRtrnCodes{success = 0, openingDataCarrierFaild,
  gettingSMARTidentityFaild};

int main()
{
  ///TCHAR ->"char"(ANSI) or ->"wchar_t"(Unicode)
  TCHAR dataCarrierPath[MAX_PATH];
  TU_Bln361095hardwareDataCarrierSMART_Use(getDataCarrierPath)(_T("0"),
    dataCarrierPath);
  HANDLE dataCarrierHandle = TU_Bln361095hardwareDataCarrierSMART_Use(
    openDataCarrier)(dataCarrierPath);

  printf("data carrier handle:%d\n", dataCarrierHandle);
  if(dataCarrierHandle == INVALID_HANDLE_VALUE)
  {
    _tprintf(_T("Opening data carrier \"%s\" failed. Operating system error "
      "code:%d\n"), dataCarrierPath, GetLastError() );
    return openingDataCarrierFaild;
  }
  else
    _tprintf(_T("Opening data carrier \"%s\" succeeded.\n"), dataCarrierPath);

  enum TU_Bln361095hardwareDataCarrierSMART_getIdentityUse(Rslt)
    SMARTgetIdentityRslt = TU_Bln361095hardwareDataCarrierSMART_Use(getIdentity)
      (dataCarrierHandle);
  if(SMARTgetIdentityRslt ==
    TU_Bln361095hardwareDataCarrierSMART_getIdentityUse(Faild) )
  {
    _tprintf(_T("Getting SMART identity for data carrier \"%s\" failed. "
      "Operating system error code:%d \n"), dataCarrierPath, GetLastError() );
    return gettingSMARTidentityFaild;
  }
  else
    _tprintf(_T("Getting SMART identity for data carrier \"%s\" succeeded.\n"),
      dataCarrierPath);
  return success;
}
