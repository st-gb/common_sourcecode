#pragma once///Include guard.
#include "../handleCmdLineOpts.hpp"///procCmdLineArgs(...),initCmdLineOpts(...)

namespace client{
void procCmdLineArgs(const int argCount, char * args[],
  cxxopts::Options & cmdLineOpts, int & port, std::string & host)
{
  try{
    cxxopts::ParseResult cmdLineOptsParseRslt = cxxopts::clientAndServer::
      procCmdLineArgs(argCount, args,cmdLineOpts, port);
    handleArg(cmdLineOptsParseRslt, "host", host);
  }catch(cxxopts::OptionException & e){std::cerr << e.what() << std::endl;}
}

inline int HandleCmdLineOpts(const int argCount, char * args[], int & port,
  std::string & host){
  cxxopts::Options cmdLineOpts(args[0]);
  cxxopts::clientAndServer::initCmdLineOpts(cmdLineOpts);
  cmdLineOpts.add_options()
    ("h,host", "host to connect to", cxxopts::value<std::string>());
  procCmdLineArgs(argCount, args, cmdLineOpts, port, host);
}
}
