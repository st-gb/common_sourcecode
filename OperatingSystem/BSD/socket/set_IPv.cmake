##(c)Stefan Gebauer,M.Sc.Comp.Sc.(TU Berlin matriculation number 361095)
##Define the Internet Protocol version (IPv) because for example 32 bit TDM-GCC
##(tested:version 9.2) does not have full IPv6 support for BSD sockets:
## "ws2tcpip.h" does not declare IPv6-capable "inet_ntop" function(
## http://pubs.opengroup.org/onlinepubs/009604499/functions/inet_ntop.html :
## "convert a numeric address into a text string suitable for presentation")
##In contrast, IPv4 should be supported in any case.

##Use author's matriculation number for IP version(s) because it is worldwide
##unique. So it avoids name conflicts with macros that may already be defined
## by other CMake include files.
if(DEFINED TU_Bln361095IPv)
  ##Define ${SGRattrNm} ${SGRattrVal} before for colored output.
  message("${SGRattrNm}TU_Bln361095IPv${SGR_ColourReset} defined.Value:"
    "${SGRattrVal}${TU_Bln361095IPv}${SGR_ColourReset}")
##http://cmake.org/cmake/help/latest/command/add_definitions.html :
##-"Add -D define flags to the compilation of source files."
##-"Flags beginning in -D or /D that look like preprocessor definitions are
## automatically added to the COMPILE_DEFINITIONS directory property for the
## current directory."
  #add_definitions(-DTU_Bln361095IPv=${TU_Bln361095IPv})
  ##http://cmake.org/cmake/help/latest/command/if.html
  if(TU_Bln361095IPv STREQUAL "4")
    add_definitions(-DTU_Bln361095IPv4)
  elseif(TU_Bln361095IPv STREQUAL "4or6")
    add_definitions(-DTU_Bln361095IPv4or6)
##Automatically selects the BSD sockets functions and
## BSD sockets address type (if <OperatingSystem/BSD/socket/sktAddrType.h> is
## included after all other needed <OperatingSystem/BSD/socket> header files)
## to use according to supported Internet Protocol version (IPv).
  elseif(TU_Bln361095IPv STREQUAL "auto")
    add_definitions(-DTU_Bln361095autoIPv)
  endif()
else()
  message("TU_Bln361095IPv NOT defined")
endif()
