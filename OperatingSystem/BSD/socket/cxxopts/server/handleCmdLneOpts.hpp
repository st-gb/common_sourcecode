#pragma once///Include guard.

///Stefan Gebauer's "common_sourcecode" repository files:
#include "../handleCmdLineOpts.hpp"

namespace cxxopts{namespace server{
	
//TODO only for server because only port number?
///@brief defines and parses command line options
inline int HandleCmdLineOpts(const int cmdLneArgCnt, char * cmdLneArgs[],
  std::string & errorMsg)
{
  cxxopts::Options cmdLineOpts(cmdLneArgs[0]);
  cxxopts::clientAndServer::initCmdLineOpts(cmdLineOpts, "listen");
  cxxopts::clientAndServer::portDataType portNo = cxxopts::clientAndServer::
    defaultPort;
  cxxopts::clientAndServer::procCmdLineArgs(cmdLneArgCnt, cmdLneArgs,
    cmdLineOpts, portNo, errorMsg);
  return portNo;
}

}}///namespaces end
