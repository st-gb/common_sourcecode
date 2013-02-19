/*
 * expand_and_stringify.h
 *
 *  Created on: Jan 30, 2013
 *      Author: sgebauer
 */

#ifndef EXPAND_AND_STRINGIFY_H_
#define EXPAND_AND_STRINGIFY_H_

#define EXPAND_AND_STRINGIFY(str) STRINGIFY(str)
//#define EXPAND_AND_STRINGIFY_2(str1,str2) STRINGIFY_2(str2)

#define STRINGIFY(str) #str

#endif /* EXPAND_AND_STRINGIFY_H_ */
