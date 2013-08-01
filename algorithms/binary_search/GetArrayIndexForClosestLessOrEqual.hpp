/*
 * GetArrayIndexForClosestLessOrEqual.hpp
 *
 *  Created on: 24.06.2013
 *      Author: Stefan
 */

#ifndef GETARRAYINDEXFORCLOSESTLESSOREQUAL_HPP_
#define GETARRAYINDEXFORCLOSESTLESSOREQUAL_HPP_

/**
 * @param ascendingSortedArray needs to be sorted in ascending order.
 * @param arraySize: array size of @see ascendingSortedArray
 * @param referredValue : value to get array index for closest less or equal value for
 */
template <typename datatype> inline arrayIndexType GetArrayIndexForClosestLessOrEqual(
  const datatype ascendingSortedArray [] ,
  const arrayIndexType arraySize ,
  const datatype referredValue //,
//  WORD & r_wArrayIndex
  )
{
//  float fValueLessOrEqual = 0.0 ;
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
    if( currentValue <= referredValue )
    {
//      fValueLessOrEqual = fCurrentMultiplier ;
      arrayIndex = currentIndex ;

      //01234 -> 01234
      //l i r      l r   l= left bound,  r= right bound   i=index

      //problem: if right-left= 0 or 1,  the left bound does not change:
      //e.g. left=7, right =8: index=7+(8-7)/2= 7+1/2=7+0=7,  left^=index->7
//      if( wRightBound - currentIndex < 2 )
        leftBound = currentIndex + 1;
//      else
//        leftBound = currentIndex ;
    }
    else //currentValue > referredValue
    {
        //01234 -> 01234
        //l i r    l r     l= left bound,  r= right bound   i=index

        //3   4 -> 3     4
        //l,i r    l,r,i

        //1 2 3 -> 1 2   3
        //l i r    l r,i

        if( currentIndex )
          //for the break condition
          rightBound = currentIndex - 1 ;
        else // currentIndex == 0 -> wRightBound would overflow and get 65535
          break ;
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

#endif /* GETARRAYINDEXFORCLOSESTLESSOREQUAL_HPP_ */
