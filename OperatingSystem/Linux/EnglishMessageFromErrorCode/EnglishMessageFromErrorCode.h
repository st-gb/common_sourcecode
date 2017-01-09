#pragma once /** include guard */

#include <string> /** class std::string */
//#include "global.h" //for DWORD

namespace OperatingSystem
{
  std::string EnglishMessageFromErrorCode(const int nOSerrorCode);

  std::string PossibleSolution(//DWORD
    const unsigned long dwErrorCode) ;
}
