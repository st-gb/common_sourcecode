#pragma once///Include guard.

#include "handleArg.hpp"

///Can be used by client and server.
inline int handlePort(cxxopts::ParseResult & cmdLineOptsParseRslt, 
  const int defaultPort)
{
  unsigned port = defaultPort;
  handleArg(cmdLineOptsParseRslt, "port", port);
  return port;
}
