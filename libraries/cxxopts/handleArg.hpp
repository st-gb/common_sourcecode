#pragma once///Include guard.
///class cxxopts::ParseResult, cxxopts::OptionException
#include<cxxopts.hpp>///https://github.com/jarro2783/cxxopts/blob/master/INSTALL

namespace cxxopts{
/**@brief provides comfort of easily delivering an error message if data type
 *  mismatch. So this function can be used without needing to define an extra
 *  exception handling for a use of cxxopts.
 * @return character string for error */
template <typename cmdLneArgType> std::string handleArg(
  cxxopts::ParseResult & cmdLineOptsParseRslt,
  const char cmdLneOptName [],
  cmdLneArgType & cmdLneArgVal)
{
  std::string stdstrErrorMsg;
  const size_t numCmdLneArgsWithSpcfdName = cmdLineOptsParseRslt.count(
    cmdLneOptName);
  if(numCmdLneArgsWithSpcfdName > 0)
  {
    try{
      const cxxopts::OptionValue & optVal = cmdLineOptsParseRslt
        /**cxxopts::ParseResult::operator [] throws cxxopts::
         * option_not_present_exception */
        [cmdLneOptName];
      cmdLneArgVal = optVal.
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
    catch(cxxopts::option_has_no_value_exception & e){
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
}///namespace end
