#pragma once///Include guard.

///Stefan Gebauer's "common_sourcecode" repository files:
#include "../handleCmdLineOpts.hpp"///procCmdLineArgs(...),initCmdLineOpts(...)
#include <libraries/cxxopts/addOptions.hpp>///cxxopts::addOptions(...)

namespace client{
int procCmdLineArgs(
  const int argCount,
  char * cmdLneArgs[],
  cxxopts::Options & cmdLineOpts,
  cxxopts::clientAndServer::portDataType & port,
  std::string & host,
  std::string & errorMsg)
{
  ///Parses command line arguments and tries to get port number option value.
  cxxopts::ParseResult cmdLineOptsParseRslt = cxxopts::clientAndServer::
    procCmdLineArgs(argCount, cmdLneArgs,
      cmdLineOpts, port, errorMsg);
  if(errorMsg == "")
    errorMsg = cxxopts::handleArg(cmdLineOptsParseRslt, "host", host);
  return errorMsg == "";
}

inline int HandleCmdLineOpts(
  const int cmdLneArgCnt,
  char * cmdLneArgs[],
  int & port,
  std::string & host,
  std::string & errorMsg)
{
  cxxopts::Options cmdLineOpts(cmdLneArgs[0]);
  ///Adds port number as command line argument.
  cxxopts::clientAndServer::initCmdLineOpts(cmdLineOpts, "connect");
  cxxopts::addOptions<std::string>(cmdLineOpts, "h,host", "host to connect to");
  return procCmdLineArgs(cmdLneArgCnt, cmdLneArgs, cmdLineOpts, port, host,
    errorMsg);
}
}///End namespace
