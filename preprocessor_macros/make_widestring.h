/*
 * make_widestring.h
 *
 *  Created on: Nov 8, 2012
 *      Author: sgebauer
 */

#ifndef MAKE_WIDESTRING_H_
#define MAKE_WIDESTRING_H_

//adapted from http://gcc.gnu.org/onlinedocs/cpp/Stringification.html
//#define xstr(s) str(s)
//#define str(s) s

//stringify "s" (expands "s" to a)
#define EXPAND_TO_WIDESTRING(s) WIDESTRING(s)
#define WIDESTRING(s) L ## s
//#define WIDESTRING(x) xstr(L ## x)
//#define WIDESTRING2(x) L ## x

#endif /* MAKE_WIDESTRING_H_ */
