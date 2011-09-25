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
#include <stdint.h> //uint32_t

//#ifdef _DEBUG
  #include <string> //class std::string
//#endif

  uint32_t GetIPv4AddressAs32bitNumber(const char * const c_p_chIPv4Address)
  {
    BYTE byIndex = 0;
    //make a copy because strtok changes the char string:
    //http://www.cplusplus.com/reference/clibrary/cstring/strtok/:
    //"This end of the token is automatically replaced by a null-character by
    // the function"
    std::string std_strIPv4Address(c_p_chIPv4Address);

    char * c_p_chIPv4AddressCopy = (char *) std_strIPv4Address.c_str();
    //Important: init with 0 because the DWORD is built by bitwise-or operand AND
    //ui32Ret is surely NOT "0" if not initialized(has "random" value then).
    uint32_t ui32Ret = 0;
    char * achIPByte = ::strtok( (char *) //c_p_chIPv4Address
      c_p_chIPv4AddressCopy, "."); // C4996
     // Note: strtok is deprecated; consider using strtok_s instead
     while( achIPByte != NULL )
     {
        ui32Ret |= (BYTE) atoi(achIPByte);
        //For the last number NO shifting should happen.
        if(byIndex ++ < 3)
          //Shift bits within ui32Ret by 8 bits heading to Most Significant Bit.
          ui32Ret <<= 8;
        // Get next token:
        achIPByte = strtok( NULL,"."); // C4996
     }
    return ui32Ret;
  }

  //TODO: does not work for:
  // IPv4 Address. . . . . . . . . . . : 10.149.50.221
  // Subnet Mask . . . . . . . . . . . : 255.255.255.252
  // Default Gateway . . . . . . . . . : 10.149.50.222
  // ?
  bool IsPrivateIPv4Address(
    const char * c_p_chIPAddress,
    const char * c_p_chNetworkMask
    )
  {
#ifdef _DEBUG
    //For debugging: Save content in string object Because the char content
    //is modified by "GetIPv4AddressAs32bitNumber(...)" ?!: c_p_chIPAddress was "10",
    //c_p_chNetworkMask was "255"
    std::string std_strIPAddress(c_p_chIPAddress);
    std::string std_strNetworkMask(c_p_chNetworkMask);
#endif
    DWORD dwNetworkMask = ::GetIPv4AddressAs32bitNumber(c_p_chNetworkMask);
    bool bIsPrivateIPAddress = false;
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
      //"255.0.0.0"
//      4278190080UL,
      0xFF000000,
      4293918720UL,//"255.240.0.0"
      //"255.255.0.0"
//      4294901760UL
      0xFFFF0000
    };
    DWORD adwNetworkIDOfAPrivateNetwork[] = {
      //"10.0.0.0"//Class "A" address range of private IPs.
      //167772160L,
      0xA000000,
      2886729728UL,//,"172.16.0.0",
      //"192.168.0.0"//Class "C" address range of private IPs.
//      3232235520UL
      0xC0A80000
    };
    DWORD dwIPv4LargestCIDRblockSubnetMaskForPrivateNetwork = 0;
    DWORD dwBitwiseAndedSubnetMasks = 0;
    DWORD dwIPv4Address = ::GetIPv4AddressAs32bitNumber(c_p_chIPAddress);
    DWORD dwIPv4AddressBitwiseAndedWithLargestCIDRblockSubnetMask = 0;
    DWORD dwNetworkIDOfAPrivateNetwork = 0;
    for( BYTE byIndex = 0; byIndex < 3; ++ byIndex )
    {
      dwIPv4LargestCIDRblockSubnetMaskForPrivateNetwork =
        ar_dwIPv4LargestCIDRblockSubnetMaskForPrivateNetwork[byIndex];
      dwBitwiseAndedSubnetMasks =
        //e.g. "255.255.255.0" & "255.255.0.0" = "255.255.0.0"
        dwNetworkMask &
        dwIPv4LargestCIDRblockSubnetMaskForPrivateNetwork;
      if( //If netmask is identical.
          //::strcmp( c_p_chNetworkMask, achIPv4NetworkMaskForPrivateNetwork[
          //  byIndex] ) == 0
          //e.g. "255.0.0.0" & "255.255.255.252" (for O2 UMTS class A network)
          //= "255.0.0.0"
          dwBitwiseAndedSubnetMasks ==
          dwIPv4LargestCIDRblockSubnetMaskForPrivateNetwork
        )
      {
        //strcmp(c_p_chIPAddress,achNetworkIDOfAPrivateNetwork[byIndex]);
//        TRACE("dwIPv4Address&adwIPv4NetworkMaskForPrivateNetwork[byIndex]: %u\n",
//          dwIPv4Address&adwIPv4NetworkMaskForPrivateNetwork[byIndex]);
//        TRACE("adwNetworkIDOfAPrivateNetwork[byIndex]&"
//          "adwIPv4NetworkMaskForPrivateNetwork[byIndex]: %u\n",
//          adwNetworkIDOfAPrivateNetwork[byIndex]&
//          adwIPv4NetworkMaskForPrivateNetwork[byIndex]);
        //DWORD dwIPv4NetMask=::GetIPv4AddressAs32bitNumber(c_p_chNetworkMask);

        dwIPv4AddressBitwiseAndedWithLargestCIDRblockSubnetMask =
          dwIPv4Address &//dwIPv4NetMask==
          //            adwIPv4NetworkMaskForPrivateNetwork[byIndex] ) ==
          dwIPv4LargestCIDRblockSubnetMaskForPrivateNetwork;

//         (  adwNetworkIDOfAPrivateNetwork[byIndex] &//dwIPv4NetMask
//        //            adwIPv4NetworkMaskForPrivateNetwork[byIndex] )
//          dwIPv4LargestCIDRblockSubnetMaskForPrivateNetwork );

        dwNetworkIDOfAPrivateNetwork = adwNetworkIDOfAPrivateNetwork[byIndex];
        if(//If both IP addresses lay/are in the same (private) network.
            dwIPv4AddressBitwiseAndedWithLargestCIDRblockSubnetMask
            == dwNetworkIDOfAPrivateNetwork
          )
        {
          bIsPrivateIPAddress = true;
          break;//for-loop
        }
      }
    }
    return bIsPrivateIPAddress;
  }
