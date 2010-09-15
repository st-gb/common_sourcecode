/*
 * GetNumberOfLogicalCPUs.h
 *
 *  Created on: 30.08.2010
 *      Author: sgebauer
 */

#ifndef GETNUMBEROFLOGICALCPUS_H_
#define GETNUMBEROFLOGICALCPUS_H_
//This include file is only needed once for each Windows, Linux etc.
//implementation/ definition.

//#ifdef _WINDOWS
//  #include <Windows/GetNumberOfLogicalCPUs.h> //GetNumLogicalCPUs()
//#endif
//#ifdef __LINUX__
//  #include <Linux/GetNumberOfLogicalCPUs.h> //GetNumLogicalCPUs()
//#endif

//Implementation/ definition of this function should be in a source file within
//the appropriate folder ( "[...]/Windows[...]" / "[...]/Linux[...]" etc.)
WORD GetNumberOfLogicalCPUcores() ;

#endif /* GETNUMBEROFLOGICALCPUS_H_ */
