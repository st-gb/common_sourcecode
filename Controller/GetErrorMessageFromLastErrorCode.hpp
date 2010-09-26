/*
 * GetErrorMessageFromLastErrorCode.h
 *
 *  Created on: Sep 9, 2010
 *      Author: Stefan
 */

#ifndef GETERRORMESSAGEFROMLASTERRORCODE_H_
#define GETERRORMESSAGEFROMLASTERRORCODE_H_

//Implementation/ definition of these functions should be in a file in the
//appropriate folder ("Windows" / "Linux" ).

std::string GetErrorMessageFromLastErrorCodeA() ;
std::string GetErrorMessageFromErrorCodeA(DWORD dwErrorCode) ;

#endif /* GETERRORMESSAGEFROMLASTERRORCODE_H_ */
