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
//  #define OperatingSystem Linux
  #include <OperatingSystem/Linux/FileSystem/GetCurrentWorkingDir/GetCurrentWorkingDir.hpp>
//  #undef OperatingSystem
#endif
#ifdef _WIN32
  //#define Windows OperatingSystem
  #include <Windows/FileSystem/GetCurrentDirectory/GetCurrentDirectory.hpp>

#endif

//namespace /*CurrentProcess*/ OperatingSystem
//{
//  inline void GetCurrentWorkingDirA_inl(std::string & r_stdstr )
//  {
//#if defined(__unix__) //Linux, Android NDK
//    Linux_::GetCurrentWorkingDirA_inl(r_stdstr);
//#endif
//#ifdef _WIN32
//	Windows::GetCurrentWorkingDirA_inl(r_stdstr);
//#endif
//  }
//}

//void SetCurrentWorkingDir(const std::string & r_stdstr ) ;

#endif /* GETCURRENTWORKINGDIR_HPP_ */
