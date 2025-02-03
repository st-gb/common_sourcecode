/**(c)from 2024 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
 * @author Stefan Gebauer(TU Berlin matriculation number 361095)*/

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
/**Bln=BerLiN: http://www.acronymfinder.com/Berlin-(Bln).html
 * Typ=TYPe: 
 * Uint=Unsigned INTeger */\
 !defined TU_Bln361095OpSys__Win__HW__NVMe__Tests__ReadSMARTattrVals__getDataCarrierViaCxxopts_h
  #define TU_Bln361095OpSys__Win__HW__NVMe__Tests__ReadSMARTattrVals__getDataCarrierViaCxxopts_h

///From/see https://github.com/jarro2783/cxxopts/
 #include <cxxopts.hpp>///cxxopts::Options, cxxopts::exceptions::exception

///Stefan Gebauer's(TU Berlin matric. number 361095) ~"cmnSrc" repository files:
 #include <hardware/CPU/fastest_data_type.h>///TU_Bln361095::CPU::faststUint

namespace //TU_Bln361095::hardware::NVMe::
  cxxopts{

inline TU_Bln361095::CPU::faststUint getDataCarrierID/*fromCxxopts*/(
  const int cmdLneArgCnt,
  const char* const cmdLneArgArr[],
  char dataCarrierID[2],
  //cxxopts::exceptions::exception & cxxoptsExc
  std::string & cxxoptsExcMsg,
  cxxopts::Options & cxxoptions
  )
{
  TU_Bln361095::CPU::faststUint exitVal =
    TU_Bln361095OpSysProcessCmdLneArgsParseUse(ArgsUnset);
  ///see http://github.com/jarro2783/cxxopts/blob/master/README.md#basics
//  cxxopts::Options options("getNVMeSMARTattrVals",
//    "Get NVMe S.M.A.R.T. attibute values"/**one-line program description*/);

  cxxoptions.add_options()
    ("d,dataCarrier", "set data carrier", cxxopts::value<std::string>())
    ;
  auto parseCxxOptionsRslt = cxxoptions.parse(cmdLneArgCnt, cmdLneArgArr);
  std::string strDataCarrier;
  try {
    strDataCarrier = parseCxxOptionsRslt["dataCarrier"].as<std::string>();
    exitVal = TU_Bln361095OpSysProcessCmdLneArgsParseUse(Sccss);
  }
  ///http://github.com/jarro2783/cxxopts/blob/master/README.md#exceptions
  catch(cxxopts::exceptions::exception & cxxoptsExc)
  {
    strDataCarrier = "0";
    //options.show_positional_help();
    const std::string cmdLneOptsHelp = cxxoptions.help();
    exitVal = TU_Bln361095OpSysProcessCmdLneArgsParseUse(Error);
  }
  //int dataCarrierNum = parseCxxOptionsRslt["dataCarrier"].as<int>();
  strcpy(dataCarrierID, strDataCarrier.c_str() );
  return exitVal;
}
}///Namespace end

#endif///Include guard