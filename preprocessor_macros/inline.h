/*
 * inline.h
 *
 *  Created on: 13.05.2012
 *      Author: Stefan
 */

#ifndef INLINE_H_
#define INLINE_H_

#ifdef MSC_VER
  #define FORCE_INLINE __force_inline
#else
  #define FORCE_INLINE inline
#endif

#endif /* INLINE_H_ */
