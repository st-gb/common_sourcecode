/*
 * binary_search.h
 *
 *  Created on: Jun 17, 2010
 *      Author: Stefan
 */

#ifndef BINARY_SEARCH_H_
#define BINARY_SEARCH_H_

inline WORD GetArrayIndexForClosestGreaterOrEqual(
  float ar_fFloatArray [] ,
  WORD wArraySize ,
  float fReferredValue ) ;
inline WORD GetArrayIndexForClosestLessOrEqual(
  float ar_fFloatArray [] ,
  WORD wArraySize ,
  float fReferredValue ) ;
inline WORD GetArrayIndexForClosestValue(
  float ar_fFloatArray [] ,
  WORD wArraySize ,
  float fReferredValue //,
//  WORD & r_wArrayIndex
  ) ;
inline float GetClosestGreaterOrEqual(
  float ar_fFloatArray [] ,
  WORD wArraySize ,
  float fReferredValue
  ) ;

inline float GetClosestLess(
  float ar_fFloatArray [] ,
  WORD wArraySize ,
  float fReferredValue
  ) ;

inline float GetClosestLessOrEqual(
  float ar_fFloatArray [] ,
  WORD wArraySize ,
  float fReferredValue
  ) ;

#endif /* BINARY_SEARCH_H_ */
