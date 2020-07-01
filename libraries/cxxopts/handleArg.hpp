#pragma once///Include guard.
///class cxxopts::ParseResult, cxxopts::OptionException
#include<cxxopts.hpp>///https://github.com/jarro2783/cxxopts/blob/master/INSTALL

namespace cxxopts{
template <typename argType> std::string /*void*/ handleArg(
  cxxopts::ParseResult & cmdLineOptsParseRslt, 
  const char argName [], argType & argVal)
{
  std::string stdstr;
  try{
  const size_t numArgsWithName = cmdLineOptsParseRslt.count(argName);
  if(numArgsWithName > 0)
  {
    //TODO may crash here (cxxopts::OptionValues::as<int>)
    argVal = cmdLineOptsParseRslt[argName].as<argType>();
    //stdoss << "Should use " << argName << " " << argVal << std::endl;
  }
  //else
  //  stdoss << argName << " not set. Using default:" << argVal << std::endl;
  }catch(cxxopts::OptionException & e){
//    std::cerr << "e" << std::endl;
    stdstr = e.what();
  }
//  catch(std::terminate & exc)///
//  stdstr = stdoss.str();
  return stdstr;
}
}///namespace end
