/*
 * operating_system_name.h
 *
 *  Created on: Jan 30, 2013
 *      Author: sgebauer
 */

#ifndef OPERATING_SYSTEM_NAME_H_
#define OPERATING_SYSTEM_NAME_H_

#ifdef __linux__
  #define OS_NAME "Linux"
#endif
#ifdef _WIN32
  #define OS_NAME "Windows"
#endif

#endif /* OPERATING_SYSTEM_NAME_H_ */
