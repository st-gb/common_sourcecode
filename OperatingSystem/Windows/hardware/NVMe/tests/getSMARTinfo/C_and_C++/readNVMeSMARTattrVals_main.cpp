/**(c)from 2023 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
 * @author Stefan Gebauer(TU Berlin matriculation number 361095) */

///Microsoft Windows Operating System runtime header files:
 ///Include this file to avoid MSVC compiler warning like "ULONG"
 //#include <windows.h>

///Stefan Gebauer's(TU Berlin matric. number 361095) ~"cmnSrc" repository files:
 /**TU_Bln361095OpSysProcessCmdLneArgsParseUse(ArgsUnset),
  * TU_Bln361095OpSysProcessCmdLneArgsParseUse(Error),
  * TU_Bln361095OpSysProcessCmdLneArgsParseUse(Sccss) */
 #include <OperatingSystem/Process/CmdLneArgs/parseCmdLneArgs.h>

#ifdef cxxoptsDir///&& defined(__cplusplus)
 ///TU_Bln361095::hardware::NVMe::cxxopts::getDataCarrierID(...)
 #include "getDataCarrierIDviaCxxopts.h"
#endif

#include "getSMARTvals_main.c"///compiles source codes as C++ code