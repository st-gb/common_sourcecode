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
 * SMART=Self-Monitoring, Analysis and Reporting Technology:
http://en.wikipedia.org/wiki/Self-Monitoring,_Analysis_and_Reporting_Technology
 * ID=IDentity: http://www.abbreviations.com/abbreviation/identity
 * Cpp=C++
 * Cmd=CoMmanD: http://www.abbreviations.com/abbreviation/COMMAND
 * Ln=LiNe: http://www.abbreviations.com/abbreviation/line
 * Opts=OPTionS: http://www.abbreviations.com/abbreviation/option */\
 ! defined TU_Bln361095OpSysWinHW_SMARTtestsReadID_CppCxxoptsHandleCmdLnOpts_hpp
   #define TU_Bln361095OpSysWinHW_SMARTtestsReadID_CppCxxoptsHandleCmdLnOpts_hpp

///C(++) standard library header files:
 #include <iostream>///std::cerr
 #include <stdio.h>///strcpy(...)

///Stefan Gebauer's(TU Berlin matric. number 361095) ~"cmnSrc" repository files:
 /**TU_Bln361095hardwareDataCarrierNmSpcBgn,
  * TU_Bln361095hardwareDataCarrierNmSpcEnd */
 #include <hardware/dataCarrier/dataCarrier_ID_prefix.h>
 /**TU_Bln361095disableUseSecC_RunTimeStrFnWarn,
  * TU_Bln361095enableUseSecC_RunTimeStrFnWarn */
 #include <compiler/C,C++/useSecureC_RunTimeStrFuncsWarn.h>
 ///TU_Bln361095cmnSrcNmSpc::cxxopts::handleArg(...)
 #include <libraries/cxxopts/handleArg.hpp>
 ///TU_Bln361095OpSysProcessCmdLneArgsUse(NoProcessArgs}
 #include <OperatingSystem/Process/cmdLineArgs.h>

#define dataCarrierOptASCII "data_carrier"

TU_Bln361095hardwareDataCarrierNmSpcBgn

namespace cxxopts{
   /**@param cmdLneArgsCnt CoMmanD LiNE ARGuments CouNT
    * @param cmdLneArgs CoMmanD LiNE ARGuments*/
inline /*int*/ void handleCmdLineOpts(
  int cmdLneArgsCnt,
  char * cmdLneArgs[],
  //std::string & dataCarrierPath
  char dataCarrierPath[])
{
  ///Needs header file from https://github.com/jarro2783/cxxopts
  ///For steps see https://github.com/jarro2783/cxxopts/blob/master/README.md
  /**Use global namespace("::") to not confuse with "TU_Bln361095"
   * namespace.*/::cxxopts::Options cmdLineOpts(cmdLneArgs[0]);
  cmdLineOpts.add_options()///Indirectly calls OptionAdder::operator()
    ///->calls m_options.add_option
    ///->calls options.options.emplace_back(
    ("d," dataCarrierOptASCII, "data carrier path", ::cxxopts::value<
      std::string>() );
  if( cmdLneArgsCnt == TU_Bln361095OpSysProcessCmdLneArgsUse(NoProcessArgs) )
    std::cout << cmdLineOpts.help() << std::endl;
  else
  {
  //try{
    auto cmdLineOptsParseRslt = cmdLineOpts.parse(cmdLneArgsCnt, cmdLneArgs);
    std::string stdStrDataCarrierPath;
    const std::string errMsg = TU_Bln361095cmnSrcNmSpc::cxxopts::handleArg(
      cmdLineOptsParseRslt, dataCarrierOptASCII,
      stdStrDataCarrierPath);
    /**Disable warning because \p dataCarrierPath should have enough space(array
     * size set to "MAX_PATH").*/
    TU_Bln361095disableUseSecC_RunTimeStrFnWarn
    strcpy(dataCarrierPath, stdStrDataCarrierPath.c_str());
    TU_Bln361095enableUseSecC_RunTimeStrFnWarn
    if( ! errMsg.empty() )
      std::cerr << "Error getting data carrier path from command line:" <<
        errMsg << std::endl;
  //}catch(cxxopts::OptionException & e){}
  }
}
}///Namespace end

TU_Bln361095hardwareDataCarrierNmSpcEnd

#endif///include guard
