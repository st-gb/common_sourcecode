#include "EnglishMessageFromErrorCode.h"
#include <string.h> //for strerror()
#include <errno.h>

std::string EnglishMessageFromErrorCode(int nErrorCode)
{
    std::string stdstrMessage ;

    char * pch = strerror(nErrorCode);

    stdstrMessage = std::string( pch) ;

    return stdstrMessage ;
}

//"A" means "ANSI" version (-> std::string)
std::string GetErrorMessageFromLastErrorCodeA()
{
  return EnglishMessageFromErrorCode(errno) ;
}

std::string GetErrorMessageFromErrorCodeA( //DWORD
  unsigned long dwErrorCode )
{
//  std::string strErrorMessage ;
  return EnglishMessageFromErrorCode(
    dwErrorCode
    ) ;
}

std::string PossibleSolution(//DWORD
  unsigned long dwErrorCode)
{
  std::string strSol = "Possible solution(s):\n" ;

  switch( dwErrorCode )
  {
  }
  return strSol ;
}
