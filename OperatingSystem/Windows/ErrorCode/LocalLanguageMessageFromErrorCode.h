#pragma once

#include <string> //class std::string
//#include "global.h" //for DWORD
#include <windef.h> //for DWORD

std::string LocalLanguageMessageFromErrorCodeA(DWORD dwErrorCode) ;
std::string LocalLanguageMessageAndErrorCodeA(DWORD dwErrorCode) ;

std::string PossibleSolution(DWORD dwErrorCode) ;
