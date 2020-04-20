#pragma once///Include guard.

///Needs header file from https://github.com/jarro2783/cxxopts
///For steps see https://github.com/jarro2783/cxxopts/blob/master/README.md
#include <cxxopts.hpp>///class cxxopts::Options from Jarryd Beck
#include "../../cxxopts/handlePort.hpp"///handlePort(...)

inline int HandleCmdLineOpts(int argCount, char * args[]){
  cxxopts::Options cmdLineOpts(args[0]);
  int portNo;
  cmdLineOpts.add_options()
    ("p,port", "port number to listen to", cxxopts::value<unsigned>());
  if( argCount == 1)
    std::cout << cmdLineOpts.help() << std::endl;
  try{
    auto cmdLineOptsParseRslt = cmdLineOpts.parse(argCount, args);
    portNo = handlePort(cmdLineOptsParseRslt, 2000);
  }catch(cxxopts::OptionException & e){}
  return portNo;
}
