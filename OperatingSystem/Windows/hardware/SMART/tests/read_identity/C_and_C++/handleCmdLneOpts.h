/**File name "handleCmdLneOpts" comes from:
 *  Cmd=CoMmanD: http://www.abbreviations.com/abbreviation/Command
 *  Opt=OPTion: http://www.abbreviations.com/abbreviation/option */

///(c) Stefan Gebauer(Computer Science Master from TU Berlin)
///@author Stefan Gebauer(TU Berlin matriculation number 361095)

///Include guard,see http://en.wikipedia.org/wiki/Include_guard :

/**Bln=BerLiN:http://www.acronymfinder.com/Berlin-(Bln).html
 * Prgm=PRaGMa
 * Incl=INCLude:http://www.abbreviations.com/abbreviation/include
 * Grd=GuaRD:http://www.abbreviations.com/abbreviation/guard */
#ifdef TU_Bln361095usePrgmInclGrd
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
  #pragma once
#endif
#if defined TU_Bln361095usePrgmInclGrd ||\
/**Include guard supported by (nearly) all industry compilers:*/\
/**Bln=Berlin:http://www.acronymfinder.com/Berlin-(Bln).html
 * OpSys=Operating System: http://www.abbreviations.com/OPSYS
 * Win=Microsoft Windows:
 *  http://www.abbreviations.com/abbreviation/Microsoft%20Windows
 * HW=HardWare: http://www.abbreviations.com/abbreviation/hardware
 * ID=IDentity: http://www.abbreviations.com/abbreviation/identity
 * Cpp=C++
 * Cmd=CoMmanD: http://www.abbreviations.com/abbreviation/COMMAND
 * Ln=LiNe: http://www.abbreviations.com/abbreviation/line
 * Opts=OPTionS: http://www.abbreviations.com/abbreviation/option */\
 ! defined TU_Bln361095OpSysWinHW_SMARTtestsReadID_C_CppHandleCmdLnOpts_hpp
   #define TU_Bln361095OpSysWinHW_SMARTtestsReadID_C_CppHandleCmdLnOpts_hpp

#ifdef __cplusplus
 ///TU_Bln361095hardwareDataCarrierNmSpc::cxxopts::handleCmdLineOpts(...)
 #include <hardware/dataCarrier/cxxopts/handleCmdLineOpts.hpp>
  using namespace TU_Bln361095cmnSrcNmSpc::cxxopts;
#else
inline /*int*/ void handleCmdLineOpts(int argCount, char * args[],
  char dataCarrierPath[])
{
  if(argCount > 1)
    dataCarrierPath = args[0];
  else
    printf("Usage:Put number for data carrier path (after \"%s\") as 1st "
      "command line argument.\n",
      TU_Bln361095OpsSysMS_WinDataCarrierPathPrefixA);
}
#endif

#endif///include guard
