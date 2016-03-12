/*
 * GetCurrentWorkingDir.hpp
 *
 *  Created on: Dec 30, 2010
 *      Author: sgebauer
 */

#ifndef GETCURRENTWORKINGDIR_HPP_
#define GETCURRENTWORKINGDIR_HPP_

#include <string> //class std::string

#ifdef __unix__
//namespace Unixoid
//{
//	GetCurrentWorkingDir(std::string & r_stdstr ) ;
//}
#define Unixoid OperatingSystem
#endif

//namespace /*CurrentProcess*/ OperatingSystem
//{
//void GetCurrentWorkingDir(std::string & r_stdstr ) ;
//}

#if defined(__unix__) //Linux, Android NDK
  #include <Linux/FileSystem/GetCurrentWorkingDir/GetCurrentWorkingDir.hpp>
  #define OperatingSystem Linux
#endif
#ifdef _WIN32
  #define Windows OperatingSystem
  #include <Windows/FileSystem/GetCurrentDirectory/GetCurrentDirectory.hpp>
#endif


//void SetCurrentWorkingDir(const std::string & r_stdstr ) ;

#endif /* GETCURRENTWORKINGDIR_HPP_ */
