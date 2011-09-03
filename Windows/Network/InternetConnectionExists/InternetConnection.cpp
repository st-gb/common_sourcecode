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
#include "InternetConnection.hpp" //for the connection state enum
#include <data_structures/Trie/NodeTrie/NodeTrie.hpp> //class NodeTrie
#include <Network/IPv4/IPv4.h> //::IsPrivateIPv4Address(...)
#include <preprocessor_macros/trace.h> //TRACE(...)
#include <preprocessor_macros/logging_preprocessor_macros.h>//DEBUG_COUTN(...)

void OutputDebugInfo(IP_ADAPTER_INFO * p_ip_adapter_infoCurrent)
{
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
}

bool InternetConnectionExists(
  const char * ar_p_chAdaptersToSkip [], unsigned uiNumAdaptersToSkip,
  //const
    NodeTrie<BYTE> & c_r_nodetrieIPadapterName2connectionState,
  bool & bConnectionStateForAtLeats1AdapterChanged
  )
{
  bool bInternetConnectionExists = false;
  bConnectionStateForAtLeats1AdapterChanged = false;
  BYTE byConnectionState = NotConnectedToInternet;
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
    bool bConnectedToTheInternetViaThisAdapter;
    while (p_ip_adapter_infoCurrent)
    {
      bConnectedToTheInternetViaThisAdapter = false;
      bNoAdaptersToSkipFound = true;
      for( WORD wRun = 0 ; wRun < uiNumAdaptersToSkip ; ++ wRun )
        //If identical
        if( strcmp( p_ip_adapter_infoCurrent->Description,
            ar_p_chAdaptersToSkip[wRun] ) == 0
          )
        {
          bNoAdaptersToSkipFound=false;
          break;
        }
      TRACE("\tAdapter Addr: \t%ld\n", p_ip_adapter_infoCurrent->Address);
      if( bNoAdaptersToSkipFound )// &&
      {
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
              )
            )
          {
            if(
              //...it MUST have a gateway address in order to reach the
              //INTERNET WAN out of the private IP address range.
              //"strcmp(...) != 0" = If the gateway string is NOT empty.
              strcmp( p_ip_adapter_infoCurrent->GatewayList.IpAddress.String,
                "") != 0
              )
            {
//              bInternetConnectionExists = true;
              bConnectedToTheInternetViaThisAdapter = true;
//              break ;
            }
          }
          else //public IP address (for instance this was the case for the FHTW
            //WLAN: IP adapters were directly accessable from the Internet).
//            bInternetConnectionExists = true;
            bConnectedToTheInternetViaThisAdapter = true;
          //else
          //  if(::HasAssociatedDNSserver())
          //    ;
          OutputDebugInfo(p_ip_adapter_infoCurrent);
        }//if(strcmp(pAdapter->IpAddressList.IpAddress.String,"0.0.0.0")!=0)

        NodeTrieNode<BYTE> * p_nodetrienode =
          c_r_nodetrieIPadapterName2connectionState.contains_inline(
          //The unique name, e.g.
          //"{ED53B8B9-E386-4928-9DCC-BA5B73DE451C}"
          (unsigned char *) p_ip_adapter_infoCurrent->AdapterName,
          (unsigned int) strlen(p_ip_adapter_infoCurrent->AdapterName),
          true
          );
        if( ! p_nodetrienode)
        {
          p_nodetrienode = c_r_nodetrieIPadapterName2connectionState.
            insert_inline(
            //The unique name, e.g.
            //"{ED53B8B9-E386-4928-9DCC-BA5B73DE451C}"
            (unsigned char *) p_ip_adapter_infoCurrent->AdapterName,
            (unsigned int) strlen(p_ip_adapter_infoCurrent->AdapterName),
            true
            );
          bConnectionStateForAtLeats1AdapterChanged = true;
        }
        if( p_nodetrienode)
        {
          if( //bInternetConnectionExists
              bConnectedToTheInternetViaThisAdapter)
          {
            if( p_nodetrienode->m_member == true)
//              byConnectionState = alreadyConnectedViaThisAdapter;
              ;
            else //if( byConnectionState != alreadyConnectedViaThisAdapter)
              //byConnectionState = ConnectedToInternet;
              bConnectionStateForAtLeats1AdapterChanged = true;
            bInternetConnectionExists = true;
          }
          else
          {
            if(p_nodetrienode->m_member == false)
//              byConnectionState = alreadyDisconnectedViaThisAdapter;
              ;
            else
//              byConnectionState = NotConnectedToInternet;
              bConnectionStateForAtLeats1AdapterChanged = true;
          }
          p_nodetrienode->m_member = bConnectedToTheInternetViaThisAdapter;
        }

      }
      p_ip_adapter_infoCurrent = p_ip_adapter_infoCurrent->Next;
    }//while (p_ip_adapter_infoCurrent)
    free(p_ip_adapter_info) ;
  }
  //else {
  //  //printf("Call to GetAdaptersInfo failed.\n");
  //}
  return bInternetConnectionExists;
    //byConnectionState;
}
