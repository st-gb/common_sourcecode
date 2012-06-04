/*
 * log_file_prefix.hpp
 *
 *  Created on: 13.04.2012
 *      Author: Stefan
 */

#ifndef LOG_FILE_PREFIX_HPP_
#define LOG_FILE_PREFIX_HPP_

#ifdef _WIN32 //Built-in preprocessor macro for MSVC, MinGW (also for 64 bit)
  //Use "windows.h" for g++ because the case matters.
//#ifdef _DEBUG
//#else //#ifdef _DEBUG
//  #include <winbase.h> //for SYSTEMTIME
//#endif //#ifdef _DEBUG
  #include "Windows_log_file_prefix.hpp"
#else // ->Unix / Linux
//  #include <sys/time.h> // gettimeofday(...)
//  #include <time.h> // localtime(...)
  #include "Linux_log_file_prefix.hpp"
#endif


#endif /* LOG_FILE_PREFIX_HPP_ */
