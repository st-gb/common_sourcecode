//#include "stdafx.h" //if not included: fatal error C1010 with MSVC++

//If not using MS Visual C++
#ifndef _MSC_VER //_MFC_VER
//  #include "global.h" //for TRACE
//  #include <winerror.h> //for ERROR_BUFFER_OVERFLOW etc.
//  #pragma comment(lib, "IPHLPAPI.lib")
#endif

#include <windef.h> //for Iphlpapi.h
#include <windows.h> //for (indirectly declaring) "OVERLAPPED" etc.
#include <Iphlpapi.h>//for GetAdaptersInfo(...)
#include <Network/IPv4/IPv4.h> //::IsPrivateIPv4Address(...)
#include <preprocessor_macros/trace.h> //TRACE(...)
#include <preprocessor_macros/logging_preprocessor_macros.h>//DEBUG_COUTN(...)

bool InternetConnectionExists()
{
  bool bInternetConnectionExists = false;
  char * strAdaptersToSkip[] = {
    "SSH Virtual Network Adapter (sshvnic)",
    "TAP-Win32 Adapter V8",
    "Bluetooth LAN Access Server Driver - Paketplaner-Miniport",
    //"Broadcom NetXtreme Gigabit Ethernet - Paketplaner-Miniport",
    "VMware Virtual Ethernet Adapter for VMnet1" };
  WORD wNumAdaptersToSkip = 4;
  PIP_ADAPTER_INFO p_ip_adapter_info;
  PIP_ADAPTER_INFO p_ip_adapter_infoCurrent = NULL;
  IP_ADAPTER_INFO ip_adapter_info ;
  DWORD dwRetVal = 0;

//    pAdapterInfo = (IP_ADAPTER_INFO *) malloc( sizeof(IP_ADAPTER_INFO) );
  ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);

  //http://msdn.microsoft.com/en-us/library/aa365917(VS.85).aspx:
  //" Make an initial call to GetAdaptersInfo to get
  // the necessary size into the ulOutBufLen variable"
  if ( ::GetAdaptersInfo( //pAdapterInfo
       & ip_adapter_info , & ulOutBufLen ) == ERROR_BUFFER_OVERFLOW
     )
  {
//      free(pAdapterInfo);
    p_ip_adapter_info = (IP_ADAPTER_INFO *) malloc (ulOutBufLen);
  }
  if( p_ip_adapter_info && (dwRetVal = ::GetAdaptersInfo( //pAdapterInfo
//          & ip_adapter_info
        p_ip_adapter_info , & ulOutBufLen )
      ) == NO_ERROR
    )
  {
    bool bNoAdaptersToSkipFound;
//      BYTE byNulls[] = {0,0,0,0};
    p_ip_adapter_infoCurrent = p_ip_adapter_info;
    while (p_ip_adapter_infoCurrent)
    {
      bNoAdaptersToSkipFound = true;
      for( WORD wRun = 0 ; wRun < wNumAdaptersToSkip ; ++ wRun )
        //If identical
        if( strcmp( p_ip_adapter_infoCurrent->Description,
              strAdaptersToSkip[wRun] ) == 0
          )
        {
          bNoAdaptersToSkipFound=false;
          break;
        }
      TRACE("\tAdapter Addr: \t%ld\n", p_ip_adapter_infoCurrent->Address);
      if( bNoAdaptersToSkipFound )// &&
        if(
          //IP address<>0: the adapter has an assigned IP address->may be
          //memcmp(pAdapter->Address,byNulls,4)
          strcmp( p_ip_adapter_infoCurrent->IpAddressList.IpAddress.String,
            "0.0.0.0") !=
            //0 = buf1 identical to buf2
            0
          )
        {
          //If it is an IP address of a private network, ...
          if(//Synchronize::IsPrivateIPAddress
            ::IsPrivateIPv4Address(
              p_ip_adapter_infoCurrent->IpAddressList.IpAddress.String ,
              p_ip_adapter_infoCurrent->IpAddressList.IpMask.String
              ) &&
              //...it MUST have a gateway address in order to reach the
              //INTERNET WAN.
              //"strcmp(...) != 0" = If the gateway string is NOT empty.
              strcmp( p_ip_adapter_infoCurrent->GatewayList.IpAddress.String,
                "") != 0
            )
          {
            bInternetConnectionExists = true;
            break ;
          }
          //else
          //  if(::HasAssociatedDNSserver())
          //    ;
//            TRACE("Possible connection to Inet found: \n");
          DEBUG_COUTN("Possible connection to Inet found: ");
//            TRACE("\tAdapter Name: \t%s\n",
//            p_ip_adapter_infoCurrent->AdapterName);
          DEBUG_COUTN("\tAdapter Name: \t" << p_ip_adapter_infoCurrent->
            AdapterName);
//            TRACE("\tAdapter Desc: \t%s\n",
//            p_ip_adapter_infoCurrent->Description);
          DEBUG_COUTN("\tAdapter Desc: \t" << p_ip_adapter_infoCurrent->
            Description);
//            TRACE("\tIP Address: \t%s\n",
//            p_ip_adapter_infoCurrent->IpAddressList.IpAddress.String);
          DEBUG_COUTN("\tIP Address: \t" << p_ip_adapter_infoCurrent->
            IpAddressList.IpAddress.String);
//            TRACE("\tIP Mask: \t%s\n",
//            p_ip_adapter_infoCurrent->IpAddressList.IpMask.String);
          DEBUG_COUTN("\tIP Mask: \t" << p_ip_adapter_infoCurrent->
            IpAddressList.IpMask.String);

          TRACE("\tGateway: \t%s\n",
                  p_ip_adapter_infoCurrent->GatewayList.IpAddress.String);
          DEBUG_COUTN("\tGateway: \t" <<
            p_ip_adapter_infoCurrent->GatewayList.IpAddress.String);
          TRACE("\t***\n");
          DEBUG_COUTN("\t***");
          if ( p_ip_adapter_infoCurrent->DhcpEnabled )
          {
            TRACE("\tDHCP Enabled: Yes\n");
            DEBUG_COUTN("\tDHCP Enabled: Yes");
            TRACE("\t\tDHCP Server: \t%s\n",
                    p_ip_adapter_infoCurrent->DhcpServer.IpAddress.String);
            DEBUG_COUTN("\t\tDHCP Server: \t" <<
              p_ip_adapter_infoCurrent->DhcpServer.IpAddress.String);
            TRACE("\tLease Obtained: %ld\n",
                    p_ip_adapter_infoCurrent->LeaseObtained);
            DEBUG_COUTN("\tLease Obtained: " <<
              p_ip_adapter_infoCurrent->LeaseObtained);
          }
          else
//              TRACE("\tDHCP Enabled: No\n");
            DEBUG_COUTN("\tDHCP Enabled: No");

          if (p_ip_adapter_infoCurrent->HaveWins)
          {
            TRACE("\tHave Wins: Yes\n");
            TRACE("\t\tPrimary Wins Server: \t%s\n",
              p_ip_adapter_infoCurrent->PrimaryWinsServer.IpAddress.String);
            DEBUG_COUTN("\t\tPrimary Wins Server: \t" <<
              p_ip_adapter_infoCurrent->PrimaryWinsServer.IpAddress.String);
            TRACE("\t\tSecondary Wins Server: \t%s\n",
              p_ip_adapter_infoCurrent->SecondaryWinsServer.IpAddress.String);
            DEBUG_COUTN("\t\tSecondary Wins Server: \t" <<
              p_ip_adapter_infoCurrent->SecondaryWinsServer.IpAddress.String);
          }
          else
//              TRACE("\tHave Wins: No\n");
            DEBUG_COUTN("\tHave Wins: No");
        }//if(strcmp(pAdapter->IpAddressList.IpAddress.String,"0.0.0.0")!=0)
      p_ip_adapter_infoCurrent = p_ip_adapter_infoCurrent->Next;
    }
    free(p_ip_adapter_info) ;
  }
  //else {
  //  //printf("Call to GetAdaptersInfo failed.\n");
  //}
  return bInternetConnectionExists;
}

//To detect a change of an Internet connection.
UINT IPAddressTableChangeLoop(LPVOID pParam)
{
  //OVERLAPPED overlap;
  //DWORD ret;

  //HANDLE hand = WSACreateEvent();
  //overlap.hEvent = WSACreateEvent();

  //ret = NotifyAddrChange(&hand, &overlap);
  //if (ret != NO_ERROR)
  //{
  //  if (WSAGetLastError() != WSA_IO_PENDING)
  //  {
  //    TRACE("NotifyAddrChange error...%d\n", WSAGetLastError());
  //    return 1;
  //  }
  //}
  ////else
  //  while(true)
  //  {
  //    TRACE("before WaitForSingleObject(overlap.hEvent, INFINITE) =="
  //      "WAIT_OBJECT_0 )\n");
  //    if ( WaitForSingleObject(overlap.hEvent, INFINITE) == WAIT_OBJECT_0 )
  //      TRACE("IP Address table changed..\n");
  //    TRACE("after WaitForSingleObject(overlap.hEvent, INFINITE) =="
  //      "WAIT_OBJECT_0 )\n");
  //  }
  while(true)
  {
    //If the caller specifies NULL for the Handle and overlapped parameters,
    //the call to NotifyAddrChange blocks until an IP address change occurs.
    NotifyAddrChange(NULL, NULL);
    TRACE("IP Address table changed..\n");
    if(//Synchronize::InternetConnectionExists()
        InternetConnectionExists() )
      TRACE("Es besteht eine Internetverbindung\n");
    else
      TRACE("Es besteht keine Internetverbindung\n");
  }
  return 0;
}
