//File extension should be ".cpp" because this is easier for program build
//because the include pathes only need to be defined for C++ (.cpp) files and
//not additionally for C (.c) files.
#ifdef _WINDOWS
  #define __cplusplus //for "NULL"
  #include <windef.h> //for "DWORD" etc.
#endif
#include <windef.h> //BYTE, DWORD
#include <stdlib.h> //atoi(...)
#include <string.h> //strtok(...), strcmp(...)

  DWORD GetIPv4AddressAsDWORD(char * pchIPv4Address)
  {
    BYTE byIndex=0;
    //Important: init with 0 because the DWORD is built by bitwise-or operand AND
    //dwRet is surely NOT "0" if not initialized(has "random" value then).
    DWORD dwRet=0;
    char * achIPByte = strtok(pchIPv4Address,"."); // C4996
     // Note: strtok is deprecated; consider using strtok_s instead
     while( achIPByte != NULL )
     {
        dwRet |= (BYTE) atoi(achIPByte);
        //For the last number NO shifting should happen.
        if(byIndex++<3)
          //Shift bits within dwRet by 8 bits heading to Most Significant Bit.
          dwRet<<=8;
        // Get next token:
        achIPByte = strtok( NULL,"."); // C4996
     }
    return dwRet;
  }

  bool IsPrivateIPv4Address(
    char * pchIPAddress,
    char * pchNetworkMask
    )
  {
    bool bIsPrivateIPAddress=false;
    //Cites from http://en.wikipedia.org/wiki/Private_network
    // #Private_IPv4_address_spaces:
//    char * achNetworkIDOfAPrivateNetwork[] = {
//      "10.0.0.0"//"10.0.0.0 – 10.255.255.255" class "A"
//      ,"172.16.0.0", //"172.16.0.0 – 172.31.255.255" class "B"
//      "192.168.0.0"//"192.168.0.0 – 192.168.255.255" class "C"
//    };
    char * achIPv4NetworkMaskForPrivateNetwork[]={
      "255.0.0.0"//8 Bit network mask
      ,"255.240.0.0"//12 Bit network mask
      ,"255.255.255.0"//16 Bit network mask
    };
//    DWORD adwIPv4NetworkMaskForPrivateNetwork[]={
//      4278190080L,//"255.0.0.0"
//      4293918720L,//"255.240.0.0"
//      4294967040L//"255.255.255.0"
//    };
    //for naming see http://en.wikipedia.org/wiki/Private_network
    // #Private_IPv4_address_spaces: "largest CIDR block (subnet mask)"
    DWORD ar_dwIPv4LargestCIDRblockSubnetMaskForPrivateNetwork[] = {
      4278190080UL,//"255.0.0.0"
      4293918720UL,//"255.240.0.0"
      4294901760UL//"255.255.0.0"
    };
    DWORD adwNetworkIDOfAPrivateNetwork[]={
      167772160L,//"10.0.0.0"//Class "A" address range of private IPs.
      2886729728UL,//,"172.16.0.0",
      3232235520UL//"192.168.0.0"//Class "C" address range of private IPs.
    };
    for( BYTE byIndex = 0; byIndex < 3; ++ byIndex )
      //If netmask is identical.
      if( strcmp( pchNetworkMask, achIPv4NetworkMaskForPrivateNetwork[byIndex] )
          == 0
        )
      {
        //strcmp(pchIPAddress,achNetworkIDOfAPrivateNetwork[byIndex]);
        DWORD dwIPv4Address = ::GetIPv4AddressAsDWORD(pchIPAddress);
//        TRACE("dwIPv4Address&adwIPv4NetworkMaskForPrivateNetwork[byIndex]: %u\n",
//          dwIPv4Address&adwIPv4NetworkMaskForPrivateNetwork[byIndex]);
//        TRACE("adwNetworkIDOfAPrivateNetwork[byIndex]&"
//          "adwIPv4NetworkMaskForPrivateNetwork[byIndex]: %u\n",
//          adwNetworkIDOfAPrivateNetwork[byIndex]&
//          adwIPv4NetworkMaskForPrivateNetwork[byIndex]);
        //DWORD dwIPv4NetMask=::GetIPv4AddressAsDWORD(pchNetworkMask);
        if(//If both IP addresses lay/are in the same (private) network.
            ( dwIPv4Address &//dwIPv4NetMask==
//            adwIPv4NetworkMaskForPrivateNetwork[byIndex] ) ==
              ar_dwIPv4LargestCIDRblockSubnetMaskForPrivateNetwork[byIndex]
            ) ==
            ( adwNetworkIDOfAPrivateNetwork[byIndex] &//dwIPv4NetMask
//            adwIPv4NetworkMaskForPrivateNetwork[byIndex] )
              ar_dwIPv4LargestCIDRblockSubnetMaskForPrivateNetwork[byIndex]
            )
          )
        {
          bIsPrivateIPAddress = true;
          break;//for-loop
        }
      }
    return bIsPrivateIPAddress;
  }
