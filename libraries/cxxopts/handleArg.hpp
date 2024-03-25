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
 * cmn=CoMmoN:http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe:http://www.abbreviations.com/abbreviation/Source
 * Arg=ARGument: http://www.abbreviations.com/abbreviation/argument */\
 ! defined TU_Bln361095cmnSrc__libraries__cxxopts__handleArg_hpp
   #define TU_Bln361095cmnSrc__libraries__cxxopts__handleArg_hpp

///class cxxopts::ParseResult, cxxopts::OptionException
 #include<cxxopts.hpp>///https://github.com/jarro2783/cxxopts/blob/master/INSTALL

///Stefan Gebauer's(TU Berlin matric. number 361095) ~"cmnSrc" repository files:
 #include <ID_prefix.h>///TU_Bln361095cmnSrcNmSpcBgn,TU_Bln361095cmnSrcNmSpcEnd

TU_Bln361095cmnSrcNmSpcBgn

namespace cxxopts{

/**@brief provides comfort of easily delivering an error message if data type
 *  mismatch. So this function can be used without needing to define an extra
 *  exception handling for a use of cxxopts.
 * @param cmdLneOptVal [out] command line option value as type \p cmdLneArgType
 *   for command line option name \p cmdLneOptName
 * @return character string for error */
template <typename cmdLneArgType> std::string handleArg(
  /**Use global namespace("::") to not confuse with "TU_Bln361095"
   * namespace.*/
  ::cxxopts::ParseResult & cmdLineOptsParseRslt,
  const char cmdLneOptName[],
  cmdLneArgType & cmdLneOptVal)
{
  std::string stdstrErrorMsg;
  const size_t numCmdLneArgsWithSpcfdName = cmdLineOptsParseRslt.count(
    cmdLneOptName);
  if(numCmdLneArgsWithSpcfdName > 0)
  {
    try{
      const /**Use global namespace("::") to not confuse with "TU_Bln361095"
         * namespace.*/
        ::cxxopts::OptionValue & optVal = cmdLineOptsParseRslt
        /**cxxopts::ParseResult::operator [] throws cxxopts::
         * option_not_present_exception */
        [cmdLneOptName];
      cmdLneOptVal = optVal.
        /** Causes a std::bad_cast exception here if the data type for command
         * line option >>cmdLneArgName<< in cxxopts::OptionValue::as() differs
         * from the one specified in cxxopts::Options::add_options(). example:
         * 1. "cxxoptions.add_options()("p,port","",cxxopts::value<float>());"
         * 2. "cxxoptVal.as<int>();" */
        /** Throws a cxxopts::option_has_no_value_exception */
        as<cmdLneArgType>();///Uses "dynamic_cast"
    }/**http://en.cppreference.com/w/cpp/types/bad_cast :"An exception of this
      * type is thrown when a dynamic_cast to a reference type fails the
      * run-time check" */
    catch(std::bad_cast & e){
      std::ostringstream stdoss;
      stdoss << e.what() << ":Invalid \"dynamic_cast\" expression for value for"
        " command line option \"" << cmdLneOptName << "\".";
      stdstrErrorMsg = stdoss.str();
    }
    catch(/**Use global namespace("::") to not confuse with "TU_Bln361095"
   * namespace.*/::cxxopts::
#if CXXOPTS__VERSION_MAJOR > 2
      exceptions::option_has_no_value
#else
      option_has_no_value_exception
#endif
      & e)
    {
  //  stdoss << argName << " not set. Using default:" << argVal << std::endl;
      stdstrErrorMsg = e.what();
    }
    catch(...)
    {
      stdstrErrorMsg = "Unknown exception when converting value for command \
line option name \"";
      stdstrErrorMsg += cmdLneOptName;
      stdstrErrorMsg += "\".";
    }
  }
//  catch(std::terminate & exc)///
  return stdstrErrorMsg;
}

}///Namespace end

TU_Bln361095cmnSrcNmSpcEnd

#endif///Include guard
