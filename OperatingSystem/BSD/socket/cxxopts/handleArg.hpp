#pragma once///Include guard.

namespace cxxopts{
template <typename argType> void handleArg(
  cxxopts::ParseResult & cmdLineOptsParseRslt, 
  const char argName [], argType & argVal)
{
  try{
  const size_t numArgsWithName = cmdLineOptsParseRslt.count(argName);
  if(numArgsWithName > 0)
  {
    argVal = cmdLineOptsParseRslt[argName].as<argType>();
    std::cout << "Should use " << argName << " " << argVal << std::endl;
  }
  else
    std::cout << argName << " not set. Using default:" << argVal << std::endl;
  }catch(cxxopts::OptionException & e){}
}
}
