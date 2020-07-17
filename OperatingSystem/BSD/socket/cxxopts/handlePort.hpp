#pragma once///Include guard.

#include <cxxopts.hpp>//cxxopts::ParseResult
#include <libraries/cxxopts/handleArg.hpp>///cxxopts::handleArg(...)

///Can be used by client and server.
inline int handlePort(cxxopts::ParseResult & cmdLineOptsParseRslt, 
  const int defaultPort)
{
  unsigned port = defaultPort;
  handleArg(cmdLineOptsParseRslt, "port", port);
  return port;
}
