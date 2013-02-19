/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany
 * ("Trilobyte SE") 2010-at least 2012.
 * You are allowed to modify and use the source code from Trilobyte SE for free
 * if you are not making profit directly or indirectly with it or its adaption.
 * Else you may contact Trilobyte SE. */
/*
 * binary_search.cpp
 *
 *  Created on: Jun 17, 2010
 *      Author: Stefan
 */
#pragma once //include guard
#include <preprocessor_macros/logging_preprocessor_macros.h>
#include <limits.h> //UINT_MAX

/*#define MANUFACTURER_ID_NAMESPACE_BEGIN namespace de { namespace Berlin { \
// namespace Trilobyte_SE { */
#define MANUFACTURER_ID_NAMESPACE de::Trilobyte_SE
#define MANUFACTURER_ID_NAMESPACE_BEGIN namespace de { namespace Trilobyte_SE {
#define MANUFACTURER_ID_NAMESPACE_END } /* namespace de */ } /*namespace Trilobyte_SE*/

typedef unsigned short WORD ;
#ifndef MAXWORD
  #define MAXWORD 65535
#endif //#ifndef MAXWORD

/**
 * ar_fFloatArray needs to be an array that is sorted in ascending order.
 */
inline WORD GetArrayIndexForClosestLessOrEqual(
  //TODO use template type
  float ar_fFloatArray [] ,
  WORD wArraySize ,
  float fReferredValue //,
//  WORD & r_wArrayIndex
  )
{
//  float fValueLessOrEqual = 0.0 ;
//  float fMultiplierGreaterOrEqual = 0.0 ;
  float fCurrentValue ;
  WORD wLeftBound = 0 ;
  WORD wRightBound = wArraySize - 1 ;
  WORD wIndex = 0 ;
  WORD r_wArrayIndex = MAXWORD ;
  //for( WORD wIndex = 0 ; wIndex < wArraySize ; //++ wIndex )
  //Do a binary search because the array is sorted.
  do
  {
    //TODO from http://en.wikipedia.org/wiki/Binary_search_algorithm#Iterative:
    //l + ( r - l) / 2 = 2*l/2 + (r-l)/2 = ( 2*l + r - l) / 2 = (l + r) / 2
    wIndex = wLeftBound + (wRightBound - wLeftBound) / 2 ;
    fCurrentValue = ar_fFloatArray[ wIndex] ;
    //The array is sorted: lowest index = lowest value.
    if( fCurrentValue <= fReferredValue )
    {
//      fValueLessOrEqual = fCurrentMultiplier ;
      r_wArrayIndex = wIndex ;

      //01234 -> 01234
      //l i r      l r   l= left bound,  r= right bound   i=index

      //problem: if right-left= 0 or 1,  the left bound does not change:
      //e.g. left=7, right =8: index=7+(8-7)/2= 7+1/2=7+0=7,  left^=index->7
//      if( wRightBound - wIndex < 2 )
        wLeftBound = wIndex + 1;
//      else
//        wLeftBound = wIndex ;
    }
    else //fCurrentValue > fReferredValue
    {
        //01234 -> 01234
        //l i r    l r     l= left bound,  r= right bound   i=index

        //3   4 -> 3     4
        //l,i r    l,r,i

        //1 2 3 -> 1 2   3
        //l i r    l r,i

        if( wIndex )
          //for the break condition
          wRightBound = wIndex - 1 ;
        else // wIndex == 0 -> wRightBound would overflow and get 65535
          break ;
//      else // fCurrentMultiplier == fCalculatedMultiplier
//      {
//        fMultiplierLessOrEqual = fCurrentMultiplier ;
//        break ;
//      }
    }
  }while( // left == right must be allowed, else
      wLeftBound <= wRightBound) ;
  return r_wArrayIndex ;
}

/**
 * ar_fFloatArray needs to be an array that is sorted in ascending order.
 */
inline WORD GetArrayIndexForClosestGreaterOrEqual(
  float ar_fFloatArray [] ,
  WORD wArraySize ,
  float fReferredValue //,
//  WORD & r_wArrayIndex
  )
{
//  float fValueGreaterOrEqual = 0.0 ;
//  float fMultiplierGreaterOrEqual = 0.0 ;
  float fCurrentValue ;
  WORD wLeftBound = 0 ;
  WORD wRightBound = wArraySize - 1 ;
  WORD wIndex = 0 ;
  WORD r_wArrayIndex = MAXWORD ;
  //for( WORD wIndex = 0 ; wIndex < wArraySize ; //++ wIndex )
  //Do a binary search because the array is sorted.
  do
  {
    //TODO from http://en.wikipedia.org/wiki/Binary_search_algorithm#Iterative:
    //l + ( r - l) / 2 = 2*l/2 + (r-l)/2 = ( 2*l + r - l) / 2 = (l + r) / 2
    wIndex = wLeftBound + (wRightBound - wLeftBound) / 2 ;
    fCurrentValue = ar_fFloatArray[ wIndex] ;
    //The array is sorted: lowest index = lowest value.
    if( fCurrentValue >= fReferredValue )
    {
//      fValueGreaterOrEqual = fCurrentValue ;
      r_wArrayIndex = wIndex ;

      //01234 -> 01234
      //l i r      l r   l= left bound,  r= right bound   i=index

      //problem: if right-left= 0 or 1,  the left bound does not change:
      //e.g. left=7, right =8: index=7+(8-7)/2= 7+1/2=7+0=7,  left^=index->7
//      if( wRightBound - wIndex < 2 )
      if( wIndex )
        wRightBound = wIndex - 1;
      else // wIndex == 0 -> wRightBound would overflow and get 65535
        break ;
//      else
//        wLeftBound = wIndex ;
    }
    else //fCurrentValue < fReferredValue
    {
        //01234 -> 01234
        //l i r    l r     l= left bound,  r= right bound   i=index

        //3   4 -> 3     4
        //l,i r    l,r,i

        //1 2 3 -> 1 2   3
        //l i r    l r,i

          //for the break condition
          wLeftBound = wIndex + 1 ;
//      else // fCurrentMultiplier == fCalculatedMultiplier
//      {
//        fMultiplierLessOrEqual = fCurrentMultiplier ;
//        break ;
//      }
    }
  }while( // left == right must be allowed, else
      wLeftBound <= wRightBound) ;
  return r_wArrayIndex ;
}

/**
 * ar_fFloatArray needs to be an array that is sorted in ascending order.
 */
inline WORD GetArrayIndexForClosestValue(
  float ar_fFloatArray [] ,
  WORD wArraySize ,
  float fReferredValue //,
//  WORD & r_wArrayIndex
  )
{
//  WORD wArrayIndex = MAXWORD ;
  WORD wArrayIndexForClosestLessOrEqual = GetArrayIndexForClosestLessOrEqual(
    ar_fFloatArray ,
    wArraySize ,
    fReferredValue //,
    ) ;
  WORD wArrayIndexForClosestGreaterOrEqual// =
//    GetArrayIndexForClosestGreaterOrEqual(
//    ar_fFloatArray ,
//    wArraySize ,
//    fReferredValue //,
//    ) ;
    = MAXWORD;
  //If no value from sorted array ar_fFloatArray is <= fReferredValue...
  if( wArrayIndexForClosestLessOrEqual == MAXWORD )
    //...so the 1st array element must be > fReferredValue
    wArrayIndexForClosestGreaterOrEqual = 0;
  else
  {
    if(ar_fFloatArray[wArrayIndexForClosestLessOrEqual] >= fReferredValue )
    {
      wArrayIndexForClosestGreaterOrEqual = wArrayIndexForClosestLessOrEqual;
    }
    else
      if( wArrayIndexForClosestLessOrEqual < wArraySize - 1 )
      {
        wArrayIndexForClosestGreaterOrEqual = wArrayIndexForClosestLessOrEqual + 1;
    //    if( ar_fFloatArray[wArrayIndexForClosestGreaterOrEqual] >=
    //        fReferredValue )
    //      if( ar_fFloatArray[wArrayIndexForClosestLessOrEqual] >=
      }
      else
        wArrayIndexForClosestGreaterOrEqual = MAXWORD;
  }
  //If any value from sorted array ar_fFloatArray is <= fReferredValue...
  if( wArrayIndexForClosestLessOrEqual == MAXWORD )
  {
    //If a value from sorted array ar_fFloatArray is >= fReferredValue...
    if( wArrayIndexForClosestGreaterOrEqual != MAXWORD )
    {
      return wArrayIndexForClosestGreaterOrEqual ;
    }
  }
  else//Array ele at index wArrayIndexForClosestLessOrEqual <= fReferredValue
  { //If no value from sorted array ar_fFloatArray is >= fReferredValue...
    if( wArrayIndexForClosestGreaterOrEqual == MAXWORD )
    {
      return wArrayIndexForClosestLessOrEqual ;
    }
    else //both >= and <=
    {
      float fMultiLessOrEqual = ar_fFloatArray[
        wArrayIndexForClosestLessOrEqual ] ;
      float fMultiGreaterOrEqual = ar_fFloatArray[
        wArrayIndexForClosestGreaterOrEqual ] ;
      if( fReferredValue - fMultiLessOrEqual <
          fMultiGreaterOrEqual - fReferredValue )
        return wArrayIndexForClosestLessOrEqual ;
      else
        return wArrayIndexForClosestGreaterOrEqual ;
    }
  }
  return MAXWORD ;
}

//TODO Possibly replace own binary search with "bsearch"
//(see http://linux.die.net/man/3/bsearch), because this function is tested.
inline float GetClosestGreaterOrEqual(
  float ar_fFloatArray [] ,
  WORD wArraySize ,
  float fReferredValue
  )
{
  float fCurrentValue ;
  float fGreaterOrEqual = 0.0 ;
  WORD wIndex = 0 ;
  WORD wLeftBound = 0 ;
  WORD wRightBound = wArraySize - 1 ;
  //Do a binary search because the array is sorted.
  while(1)
  {
    //TODO from http://en.wikipedia.org/wiki/Binary_search_algorithm#Iterative:
    //l + ( r - l) / 2 = 2*l/2 + (r-l)/2 = ( 2*l + r - l) / 2 = (l + r) / 2
    wIndex = wLeftBound + (wRightBound - wLeftBound) / 2 ;
    fCurrentValue = ar_fFloatArray[ wIndex] ;
    //The array is sorted: lowest index = lowest value.
    if( fCurrentValue >= fReferredValue )
    {
      fGreaterOrEqual = fCurrentValue ;

      if( wLeftBound == wRightBound )
        break ;
      wRightBound = wIndex ;
    }
    else
    {
      if( wLeftBound == wRightBound )
        break ;
      if( fCurrentValue < fReferredValue)
      {
        //problem: if right-left= 0 or 1,  the left bound does not change:
        //e.g. left=7, right =8: index=7+(8-7)/2= 7+1/2=7+0=7,  left^=index->7
        if( wRightBound - wIndex < 2 )
          //0    1 2   -> 0 1     2
          //l,i  r          l,i,r       l= left bound,  r= right bound   i=index
          wLeftBound = wIndex + 1;
        else
          //01234 -> 012   3 4
          //l i r      l,i   r     l= left bound,  r= right bound   i=index
          wLeftBound = wIndex ;
      }
//      else // fCurrentMultiplier == fCalculatedMultiplier
//      {
//        fGreaterOrEqual = fCurrentValue ;
//        break ;
//      }
    }
  }
  return fGreaterOrEqual ;
}

MANUFACTURER_ID_NAMESPACE_BEGIN
/*template <typename datatype>*/ namespace BinarySearch
{
  typedef UINT arrayIndexType;
  const arrayIndexType no_element = UINT_MAX;
//  inline WORD GetClosestLess(
//    float ar_fFloatArray [] ,
//    WORD wArraySize ,
//    float fReferredValue
//    )
//  {
//  //  float fLess = 0.0 ;
//    float fCurrent ;
//    WORD wArrayIndex = 0 ;
//    WORD wArrayIndexOfCloestLessValue = MAXWORD ;
//    WORD wLeftBound = 0 ;
//    WORD wRightBound = wArraySize - 1 ;
//    //for( WORD wIndex = 0 ; wIndex < wArraySize ; //++ wIndex )
//    //Do a binary search because the array is sorted.
//  //  while(1)
//    do
//    {
//      //TODO from http://en.wikipedia.org/wiki/Binary_search_algorithm#Iterative:
//      //l + ( r - l) / 2 = 2*l/2 + (r-l)/2 = ( 2*l + r - l) / 2 = (l + r) / 2
//      wArrayIndex = wLeftBound + (wRightBound - wLeftBound) / 2 ;
//      fCurrent = ar_fFloatArray[ wArrayIndex] ;
//  //    LOGN("GetClosestLess--"
//  //      << "array index:" << wArrayIndex
//  //      << "value at array index:" << fCurrent )
//      //The array is sorted: lowest index = lowest value.
//      if( fCurrent < fReferredValue )
//      {
//  //      fLess = fCurrent ;
//        wArrayIndexOfCloestLessValue = wArrayIndex ;
//
//  //      if( wLeftBound == wRightBound )
//  //        break ;
//        //01234 -> 01234
//        //l i r      l r   l= left bound,  r= right bound   i=index
//
//        //problem: if right-left= 0 or 1,  the left bound does not change:
//        //e.g. left=7, right =8: index=7+(8-7)/2= 7+1/2=7+0=7,  left^=index->7
//  //      if( wRightBound - wIndex < 2 )
//          wLeftBound = wArrayIndex + 1;
//  //      else
//  //        wLeftBound = wIndex ;
//      }
//      else //current value >= referred value
//      {
//  //      if( wLeftBound == wRightBound )
//  //        break ;
//  //      if( fCurrent >= fReferredValue)
//  //      {
//          //01234 -> 01234
//          //l i r    l r     l= left bound,  r= right bound   i=index
//
//          //3   4 -> 3     4
//          //l,i r    l,r,i
//
//          //1 2 3 -> 1 2   3
//          //l i r    l r,i
//
//          wRightBound = wArrayIndex - 1 ;
//          //if right bound = 0 it gets 65535
//          if( wRightBound == MAXWORD )
//            break ;
//  //      }
//  //      else // fCurrentMultiplier == fCalculatedMultiplier
//  //      {
//  ////        fLess = fCurrent ;
//  //        break ;
//  //      }
//      }
//    }
//    // "<=" because: If left bound = 0, index = 1
//    //  and value at index 1 >= referred value:
//    //   right bound ^= index-1 = left bound
//    while( wLeftBound <= wRightBound ) ;
//  //  return fLess ;
//    return wArrayIndexOfCloestLessValue ;
//  }
  template <typename datatype> inline UINT GetClosestLess(
    datatype array [] ,
    WORD wArraySize ,
    datatype fReferredValue
    )
  {
  //  float fLess = 0.0 ;
    float fCurrent ;
    arrayIndexType wArrayIndex = 0 ;
    arrayIndexType wArrayIndexOfClosestLessValue = /*UINT_MAX*/ no_element;
    arrayIndexType wLeftBound = 0 ;
    arrayIndexType wRightBound = wArraySize - 1 ;
    //for( WORD wIndex = 0 ; wIndex < wArraySize ; //++ wIndex )
    //Do a binary search because the array is sorted.
  //  while(1)
    do
    {
      //TODO from http://en.wikipedia.org/wiki/Binary_search_algorithm#Iterative:
      //l + ( r - l) / 2 = 2*l/2 + (r-l)/2 = ( 2*l + r - l) / 2 = (l + r) / 2
      wArrayIndex = wLeftBound + (wRightBound - wLeftBound) / 2 ;
      fCurrent = array[ wArrayIndex] ;
  //    LOGN("GetClosestLess--"
  //      << "array index:" << wArrayIndex
  //      << "value at array index:" << fCurrent )
      //The array is sorted: lowest index = lowest value.
      if( fCurrent < fReferredValue )
      {
  //      fLess = fCurrent ;
        wArrayIndexOfClosestLessValue = wArrayIndex ;

  //      if( wLeftBound == wRightBound )
  //        break ;
        //01234 -> 01234
        //l i r      l r   l= left bound,  r= right bound   i=index

        //problem: if right-left= 0 or 1,  the left bound does not change:
        //e.g. left=7, right =8: index=7+(8-7)/2= 7+1/2=7+0=7,  left^=index->7
  //      if( wRightBound - wIndex < 2 )
          wLeftBound = wArrayIndex + 1;
  //      else
  //        wLeftBound = wIndex ;
      }
      else //current value >= referred value
      {
  //      if( wLeftBound == wRightBound )
  //        break ;
  //      if( fCurrent >= fReferredValue)
  //      {
          //01234 -> 01234
          //l i r    l r     l= left bound,  r= right bound   i=index

          //3   4 -> 3     4
          //l,i r    l,r,i

          //1 2 3 -> 1 2   3
          //l i r    l r,i

          if( wArrayIndex == 0UL)
            break;
          wRightBound = wArrayIndex - 1 ;
//          //if right bound = 0 it gets no_element (max value of data type)
//          if( wRightBound == no_element )
//            break ;
  //      }
  //      else // fCurrentMultiplier == fCalculatedMultiplier
  //      {
  ////        fLess = fCurrent ;
  //        break ;
  //      }
      }
    }
    // "<=" because: If left bound = 0, index = 1
    //  and value at index 1 >= referred value:
    //   right bound ^= index-1 = left bound
    while( wLeftBound <= wRightBound ) ;
  //  return fLess ;
    return wArrayIndexOfClosestLessValue ;
  }
}
MANUFACTURER_ID_NAMESPACE_END

inline float GetClosestLessOrEqual(
  float ar_fFloatArray [] ,
  WORD wArraySize ,
  float fReferredValue
  )
{
  float fValueLessOrEqual = 0.0 ;
//  float fMultiplierGreaterOrEqual = 0.0 ;
  float fCurrentValue ;
  WORD wLeftBound = 0 ;
  WORD wRightBound = wArraySize - 1 ;
  WORD wIndex = 0 ;
  //for( WORD wIndex = 0 ; wIndex < wArraySize ; //++ wIndex )
  //Do a binary search because the array is sorted.
  while(1)
  {
    //TODO from http://en.wikipedia.org/wiki/Binary_search_algorithm#Iterative:
    //l + ( r - l) / 2 = 2*l/2 + (r-l)/2 = ( 2*l + r - l) / 2 = (l + r) / 2
    wIndex = wLeftBound + (wRightBound - wLeftBound) / 2 ;
    fCurrentValue = ar_fFloatArray[ wIndex] ;
    //The array is sorted: lowest index = lowest value.
    if( fCurrentValue <= fReferredValue )
    {
      fValueLessOrEqual = fCurrentValue ;

      if( wLeftBound == wRightBound )
        break ;
      //01234 -> 01234
      //l i r      l r   l= left bound,  r= right bound   i=index

      //problem: if right-left= 0 or 1,  the left bound does not change:
      //e.g. left=7, right =8: index=7+(8-7)/2= 7+1/2=7+0=7,  left^=index->7
      if( wRightBound - wIndex < 2 )
        wLeftBound = wIndex + 1;
      else
        wLeftBound = wIndex ;
    }
    else
    {
      if( wLeftBound == wRightBound )
        break ;
      if( fCurrentValue > fReferredValue)
      {
        //01234 -> 01234
        //l i r    l r     l= left bound,  r= right bound   i=index

        //3   4 -> 3     4
        //l,i r    l,r,i

        //1 2 3 -> 1 2   3
        //l i r    l r,i
        wRightBound = wIndex ;
      }
//      else // fCurrentMultiplier == fCalculatedMultiplier
//      {
//        fMultiplierLessOrEqual = fCurrentMultiplier ;
//        break ;
//      }
    }
  }
  return fValueLessOrEqual ;
}
