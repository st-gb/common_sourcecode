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
#include <limits> //std::numeric_limits

/*#define MANUFACTURER_ID_NAMESPACE_BEGIN namespace de { namespace Berlin { \
// namespace Trilobyte_SE { */
#define MANUFACTURER_ID_NAMESPACE de::Trilobyte_SE
#define MANUFACTURER_ID_NAMESPACE_BEGIN namespace de { namespace Trilobyte_SE {
#define MANUFACTURER_ID_NAMESPACE_END } /* namespace de */ } /*namespace Trilobyte_SE*/

typedef unsigned short WORD ;
#ifndef MAXWORD
  #define MAXWORD 65535
#endif //#ifndef MAXWORD

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
  /** int is fastest data type */
  typedef UINT arrayIndexType;
  //const arrayIndexType no_element = UINT_MAX;
  const arrayIndexType no_element = std::numeric_limits<arrayIndexType>::max();

  #include "GetArrayIndexForClosestLessOrEqual.hpp"

  /**
   * @param ascendingSortedArray needs to be an array that is sorted in
   *   ascending order.
   */
  template <typename datatype/*, typename array_index_type*/>
    inline arrayIndexType GetArrayIndexForClosestGreaterOrEqual(
    const datatype ascendingSortedArray [] ,
    const arrayIndexType arraySize ,
    const datatype referredValue //,
  //  WORD & r_wArrayIndex
    )
  {
  //  float fValueGreaterOrEqual = 0.0 ;
  //  float fMultiplierGreaterOrEqual = 0.0 ;
    datatype currentValue ;
    arrayIndexType leftBound = 0 ;
    arrayIndexType rightBound = arraySize - 1 ;
    arrayIndexType currentIndex = 0 ;
    arrayIndexType arrayIndex = no_element ;
    //for( WORD currentIndex = 0 ; currentIndex < arraySize ; //++ currentIndex )
    //Do a binary search because the array is sorted.
    do
    {
      //TODO from http://en.wikipedia.org/wiki/Binary_search_algorithm#Iterative:
      //l + ( r - l) / 2 = 2*l/2 + (r-l)/2 = ( 2*l + r - l) / 2 = (l + r) / 2
      currentIndex = leftBound + (rightBound - leftBound) / 2 ;
      currentValue = ascendingSortedArray[ currentIndex] ;
      //The array is sorted: lowest index = lowest value.
      if( currentValue >= referredValue )
      {
  //      fValueGreaterOrEqual = currentValue ;
        arrayIndex = currentIndex ;

        //01234 -> 01234
        //l i r      l r   l= left bound,  r= right bound   i=index

        //problem: if right-left= 0 or 1,  the left bound does not change:
        //e.g. left=7, right =8: index=7+(8-7)/2= 7+1/2=7+0=7,  left^=index->7
  //      if( rightBound - currentIndex < 2 )
        if( currentIndex )
          rightBound = currentIndex - 1;
        else // currentIndex == 0 -> rightBound would overflow and get 65535
          break ;
  //      else
  //        leftBound = currentIndex ;
      }
      else //currentValue < referredValue
      {
          //01234 -> 01234
          //l i r    l r     l= left bound,  r= right bound   i=index

          //3   4 -> 3     4
          //l,i r    l,r,i

          //1 2 3 -> 1 2   3
          //l i r    l r,i

            //for the break condition
            leftBound = currentIndex + 1 ;
  //      else // fCurrentMultiplier == fCalculatedMultiplier
  //      {
  //        fMultiplierLessOrEqual = fCurrentMultiplier ;
  //        break ;
  //      }
      }
    }while( // left == right must be allowed, else
        leftBound <= rightBound) ;
    return arrayIndex ;
  }

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

  /**
   * @param array must be sorted in ascending order.
   * @param arraySize: array size of @see ascendingSortedArray
   * @param referredValue : value to get array index for closest less or equal value for
   */
  template <typename datatype/*, typename array_index_type*/> inline arrayIndexType
    GetArrayIndexForClosestValue(
    const datatype array [] ,
    const arrayIndexType /*array_index_type*/ arraySize ,
    const datatype referredValue //,
  //  WORD & r_wArrayIndex
    )
  {
//    const array_index_type max_array_index =
//      std::numeric_limits<array_index_type>::max();
    const arrayIndexType arrayIndexForClosestLessOrEqual =
      GetArrayIndexForClosestLessOrEqual(
        array ,
        arraySize ,
        referredValue //,
        ) ;
    arrayIndexType /*array_index_type*/ arrayIndexForClosestGreaterOrEqual// =
  //    GetArrayIndexForClosestGreaterOrEqual(
  //    array ,
  //    arraySize ,
  //    referredValue //,
  //    ) ;
    //from http://stackoverflow.com/questions/1855459/maximum-value-of-int
      //= max_array_index;
      = no_element;
    //If no value from sorted array array is <= referredValue...
    if( arrayIndexForClosestLessOrEqual == no_element /*max_array_index*/ )
      //...so the 1st array element must be > referredValue
      arrayIndexForClosestGreaterOrEqual = 0;
    else
    {
      if(array[arrayIndexForClosestLessOrEqual] >= referredValue )
      {
        arrayIndexForClosestGreaterOrEqual = arrayIndexForClosestLessOrEqual;
      }
      else
        if( arrayIndexForClosestLessOrEqual < arraySize - 1 )
        {
          arrayIndexForClosestGreaterOrEqual = arrayIndexForClosestLessOrEqual + 1;
      //    if( array[arrayIndexForClosestGreaterOrEqual] >=
      //        referredValue )
      //      if( array[arrayIndexForClosestLessOrEqual] >=
        }
        else
          arrayIndexForClosestGreaterOrEqual = no_element;
    }
    //If any value from sorted array array is <= referredValue...
    if( arrayIndexForClosestLessOrEqual == no_element )
    {
      //If a value from sorted array array is >= referredValue...
      if( arrayIndexForClosestGreaterOrEqual != no_element )
      {
        return arrayIndexForClosestGreaterOrEqual ;
      }
    }
    else//Array ele at index arrayIndexForClosestLessOrEqual <= referredValue
    { //If no value from sorted array array is >= referredValue...
      if( arrayIndexForClosestGreaterOrEqual == no_element )
      {
        return arrayIndexForClosestLessOrEqual ;
      }
      else //both >= and <=
      {
        float fMultiLessOrEqual = array[
          arrayIndexForClosestLessOrEqual ] ;
        float fMultiGreaterOrEqual = array[
          arrayIndexForClosestGreaterOrEqual ] ;
        if( referredValue - fMultiLessOrEqual <
            fMultiGreaterOrEqual - referredValue )
          return arrayIndexForClosestLessOrEqual ;
        else
          return arrayIndexForClosestGreaterOrEqual ;
      }
    }
    return no_element ;
  }

  /**
   * @param array must be sorted in ascending order.
   * @param arraySize: array size of @see ascendingSortedArray
   * @param referredValue : value to get array index for closest less or equal value for
   */
  template <typename datatype> inline arrayIndexType GetClosestLess(
    const datatype array [] ,
    const arrayIndexType wArraySize ,
    const datatype referredValue
    )
  {
  //  float fLess = 0.0 ;
    datatype currentValue ;
    arrayIndexType currentArrayIndex = 0 ;
    arrayIndexType arrayIndexOfClosestLessValue = /*UINT_MAX*/ no_element;
    arrayIndexType leftBound = 0 ;
    arrayIndexType rightBound = wArraySize - 1 ;
    //for( WORD wIndex = 0 ; wIndex < wArraySize ; //++ wIndex )
    //Do a binary search because the array is sorted.
  //  while(1)
    do
    {
      //TODO from http://en.wikipedia.org/wiki/Binary_search_algorithm#Iterative:
      //l + ( r - l) / 2 = 2*l/2 + (r-l)/2 = ( 2*l + r - l) / 2 = (l + r) / 2
      currentArrayIndex = leftBound + (rightBound - leftBound) / 2 ;
      currentValue = array[ currentArrayIndex] ;
  //    LOGN("GetClosestLess--"
  //      << "array index:" << currentArrayIndex
  //      << "value at array index:" << currentValue )
      //The array is sorted: lowest index = lowest value.
      if( currentValue < referredValue )
      {
  //      fLess = currentValue ;
        arrayIndexOfClosestLessValue = currentArrayIndex ;

  //      if( leftBound == rightBound )
  //        break ;
        //01234 -> 01234
        //l i r      l r   l= left bound,  r= right bound   i=index

        //problem: if right-left= 0 or 1,  the left bound does not change:
        //e.g. left=7, right =8: index=7+(8-7)/2= 7+1/2=7+0=7,  left^=index->7
  //      if( rightBound - wIndex < 2 )
          leftBound = currentArrayIndex + 1;
  //      else
  //        leftBound = wIndex ;
      }
      else //current value >= referred value
      {
  //      if( leftBound == rightBound )
  //        break ;
  //      if( currentValue >= referredValue)
  //      {
          //01234 -> 01234
          //l i r    l r     l= left bound,  r= right bound   i=index

          //3   4 -> 3     4
          //l,i r    l,r,i

          //1 2 3 -> 1 2   3
          //l i r    l r,i

          if( currentArrayIndex == 0UL)
            break;
          rightBound = currentArrayIndex - 1 ;
//          //if right bound = 0 it gets no_element (max value of data type)
//          if( rightBound == no_element )
//            break ;
  //      }
  //      else // fCurrentMultiplier == fCalculatedMultiplier
  //      {
  ////        fLess = currentValue ;
  //        break ;
  //      }
      }
    }
    // "<=" because: If left bound = 0, index = 1
    //  and value at index 1 >= referred value:
    //   right bound ^= index-1 = left bound
    while( leftBound <= rightBound ) ;
  //  return fLess ;
    return arrayIndexOfClosestLessValue ;
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
