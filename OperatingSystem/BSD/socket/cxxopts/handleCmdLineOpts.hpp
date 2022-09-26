///(c)from 2020:Stefan Gebauer,Computer Science Master(TU Berlin,matric.#361095)
///Created ca.07May2020 by Stefan Gebauer(TU Berlin matriculation number 361095)

///Include guard,see http://en.wikipedia.org/wiki/Include_guard
/**Bln=BerLiN
 * Prgm=PRaGMa
 * Incl=INCLude:http://www.abbreviations.com/abbreviation/include
 * Grd=GuaRD:http://www.abbreviations.com/abbreviation/Guard*/
#ifdef TU_Bln361095usePrgmInclGrd
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
  #pragma once
#else
///Include guard supported by (nearly) all industry compilers:
  #ifndef TU_Bln361095cmnSrcBSDskt_cxxopts_handleCmdLineOpts_hpp
  #define TU_Bln361095cmnSrcBSDskt_cxxopts_handleCmdLineOpts_hpp
#endif

///Standard C(++) header files:
#include <iostream>///std::cout

#ifndef _GLIBCXX_USE_C99_CTYPE_TR1///Avoid "already defined" compiler warning
/**For isblank(int) to be in namespace "std" in file <c++/cctype> (at least
 * in MinGW). This is needed for cxxopts.hpp */
  #define _GLIBCXX_USE_C99_CTYPE_TR1
#endif

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
#include <preprocessor_macros/stringize.h>///stringize(...)

/**C++ needs to be >= 201103L for std::isblank in <c++/cctype> (for example 
 * MinGW32 9.2.0) */
#pragma message "__cplusplus:" stringize(__cplusplus)

///Needs header file from https://github.com/jarro2783/cxxopts
///For steps see https://github.com/jarro2783/cxxopts/blob/master/README.md
#include <cxxopts.hpp>///class cxxopts::Options from Jarryd Beck

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
///cxxopts::incorrArgTypeExc,cxxopts::mostGenericExc
#include <libraries/cxxopts/excTypes.hpp>
#include <libraries/cxxopts/handleArg.hpp>///cxxopts::handleArg(...)
#include <libraries/cxxopts/addOptions.hpp>///cxxopts::addOptions(...)

///Used by both the client and server. The common between them is the port.
namespace cxxopts{namespace clientAndServer{
typedef int portDataType;
/** http://en.wikipedia.org/wiki/List_of_TCP_and_UDP_port_numbers :
 *  Well-known ports 0 to 1023
 *  Registered ports : 1024 to 49151
 *  -> Use server port number >= 49152 */
const portDataType defaultPort = 50000;

/**@brief executes steps that are common for both client and server:
 * 1. parses command line arguments
 * 2. tries to get port number option value.*/
cxxopts::ParseResult procCmdLineArgs(
  const int cmdLneArgCnt,
  char * cmdLneArgs[],
  cxxopts::Options & cmdLineOpts,
  portDataType & port,
  std::string & errorMsg)
{
  if( cmdLneArgCnt == 1)
    //TODO change to iostream pointer (if pointer == 0: do not output)?
    std::cout << cmdLineOpts.help() << std::endl;
  cxxopts::ParseResult cmdLineOptsParseRslt;
  try
  {
    cmdLineOptsParseRslt = cmdLineOpts.parse(cmdLneArgCnt, cmdLneArgs);
    errorMsg = handleArg(cmdLineOptsParseRslt, "port", port);
  /**These following exceptions are (indirectly) thrown from 
   * cxxopts::Options::parse(...) */
  /** E.g. when parsing a character string as integer with letter "k" inside.*/
  }catch(TU_Bln361095::cxxopts::incorrArgTypeExc & exc){
    std::ostringstream oss;
    oss << "Error:at least 1 command line option has incorrect type:" <<
      /**what() delivers the concerning command line option.*/exc.what();
    errorMsg = oss.str();
  }
  catch(/**The most generic "cxxopts" exception?*/
    TU_Bln361095::cxxopts::mostGenericExc & exc)
  {
    std::ostringstream oss;
    /**Add own message because the "cxxopts" exception message does not state
     * that these are _command line_ options.*/
    oss << "Error parsing command line options:" << exc.what();
    errorMsg = oss.str();
  }
  return cmdLineOptsParseRslt;
}

///@param portAction : either "listen" (for servers) or "connect" (for clients).
void initCmdLineOpts(cxxopts::Options & cmdLineOpts, const char portAction[]){
  std::string optionAction = std::string("port number to ") + portAction + " to";
  addOptions<portDataType>(
    cmdLineOpts,
    "p,port",
    optionAction.c_str() );
}

}}///namespaces end
#ifndef TU_Bln361095usePrgmInclGrd
#endif///#ifndef TU_Bln361095cmnSrcBSDskt_cxxopts_handleCmdLineOpts_hpp
#endif