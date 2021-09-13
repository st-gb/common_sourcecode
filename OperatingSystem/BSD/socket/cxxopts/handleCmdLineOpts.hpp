#pragma once///Include guard.

///Needs header file from https://github.com/jarro2783/cxxopts
///For steps see https://github.com/jarro2783/cxxopts/blob/master/README.md
#include <cxxopts.hpp>///class cxxopts::Options from Jarryd Beck
#include "../../../../libraries/cxxopts/handleArg.hpp"///handleArg(...)

///Used by both the client and server. The common between them is the port.
namespace cxxopts{namespace clientAndServer{

cxxopts::ParseResult procCmdLineArgs(int argCount, char * args[],
  cxxopts::Options & cmdLineOpts, int & port)
{
  if( argCount == 1)
    std::cout << cmdLineOpts.help() << std::endl;
  cxxopts::ParseResult cmdLineOptsParseRslt = cmdLineOpts.parse(argCount, args);
  port = 2000;
  handleArg(cmdLineOptsParseRslt, "port", port);
  return cmdLineOptsParseRslt;
}

void initCmdLineOpts(cxxopts::Options & cmdLineOpts){
  cmdLineOpts.add_options()
    ("p,port", "port number to listen to", cxxopts::value<unsigned>());
}

inline int HandleCmdLineOpts(int argCount, char * args[]){
  cxxopts::Options cmdLineOpts(args[0]);
  initCmdLineOpts(cmdLineOpts);
  int portNo = 2000;
  try{
    procCmdLineArgs(argCount,args,cmdLineOpts,portNo);
  }catch(cxxopts::OptionException & e){}
  return portNo;
}
}}///namespaces end
