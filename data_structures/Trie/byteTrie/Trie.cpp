/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */
/*
 * Trie.cpp
 *
 *  Created on: Jul 28, 2010
 *      Author: Stefan
 */
#include <preprocessor_macros/logging_preprocessor_macros.h>
#include <vector>
#include <sstream> //std::ostringstream
#include <windef.h> //BYTE etc.

#include "Trie.hpp"

void Trie::FreeMemory()
{
//  char ch ;
  //Arrays of pointers.
  unsigned char ** ar_p_byCurrent ;
  unsigned char ** ar_p_by1LevelAbove = NULL ;
  //WORD wSize ;
  DEBUGN("data structure: FreeMemory")
  DEBUGN("root node array address: " << m_ar_p_byRoot )
#ifdef _DEBUG
//    std::string stdstrCurrent ;
  std::vector<unsigned char> stdvec_by ;
#endif //#ifdef _DEBUG
//  while( //Root is deleted and set to NULL if it has no more children.
//      m_ar_p_byRoot )
  do
  {
    //for the case that the root node has no more children.
    ar_p_by1LevelAbove = NULL ;
    ar_p_byCurrent = m_ar_p_byRoot ;
    //This loop deleted 1 element at the leaf.
    for( WORD wIndex = 0 ; wIndex < DIFFERENT_VALUES_PER_LEVEL ; ++ wIndex )
    {
      if( //Array element not NULL <=> character at/ for position "wIndex" is
          //assigned.
          ar_p_byCurrent[ wIndex ] )
      {
        ar_p_by1LevelAbove =
          //Address of array element.
          &
          //Address of next array/ level directing leaves:
          //         0x10
          // [...]   |a|
          //          |
          //  +-------+------
          // 0x10   0x14 0x18 ...  <-- " & r_p_byCurrent[ wIndex ] "
          //[0x999|0x777|0x123| | | | | ]  <-- r_p_byCurrent[ wIndex ]

          //         " & r_p_byCurrent[ wIndex ] " = "r_p_byCurrent + wIndex" ?

          //Store the address of array element "ar_p_byCurrent[ wIndex ]"
          //because the current address will be changed to the address of
          //element by 1 level below (=directing leaves).
          ar_p_byCurrent[ wIndex ] ;
        ar_p_byCurrent = //& ar_p_byCurrent[ wIndex ] ;
          (unsigned char **) ar_p_byCurrent[ wIndex ] ;
        //bNoChildNode = false ;
#ifdef _DEBUG
        stdvec_by.push_back( (BYTE) wIndex ) ;
#endif //#ifdef _DEBUG
        DEBUGN
        //DEBUG_COUTN
          ( "entering child node at address " << ar_p_byCurrent )

        wIndex = 65535 ; //MAXWORD ;
        //found the 1st child: go 1 level deeper.
        continue ;
      }
      else
      {
        if( //Index for last array element.
            wIndex == ( DIFFERENT_VALUES_PER_LEVEL - 1 ) )
        {
//          DEBUG_COUTN( //"& address : " << & ar_p_byCurrent
//              "value at address " << ar_p_byCurrent
//              << ":" << *ar_p_byCurrent )
          //no child node for current node -> delete current node
          DEBUGN
          //DEBUG_COUTN
            ("deleting current array at address" << ar_p_byCurrent )
          //If at least 2 levels (array should NOT be deleted if it points to
          //the root node because the root node is created on stack) .
          if( ar_p_by1LevelAbove )
          {
            //May NOT be deleted if it points to the root node because the
            // root node is created on stack .
            delete [] ar_p_byCurrent ;
            -- m_dwNumberOfNodes ;
            //         0x10
             // [...]   |a|  <-delete and set to NULL because all children are NULL
             //          |
             //  +-------+------
             //0x100  0x114
             //[0x123|    | | | | | | ]  <-- all empty/ NULL
            //
            //The array whose address was stored at e.g. address 0x10 (->
            // array address "a" ) has been deleted.
            //So set address of array element to zero to mark the end.
            * ar_p_by1LevelAbove = NULL ;
            //Now it should look like:
            //         0x10
            // [...]  |0x00|  <-set to NULL because array at "a" deleted.
            //          |
            //  +-------+------
            // 0x500 0x514
            //[0x000|     | | | | | | ]  <-- deleted array
          }
          else
          {
//            DEBUGN
//            //DEBUG_COUTN
//              ("deleting root array at address" << m_ar_p_byRoot)
//            m_ar_p_byRoot = NULL ;
//            delete [] m_ar_p_byRoot ;
//            -- m_dwNumberOfNodes ;
            DEBUGN("We are at the root node.")
//            m_ar_p_byRoot = NULL ;
          }
//          break ;
          //mark the end -> do no delete the 2nd time.
//           & ar_p_byCurrent = NULL ;
          //write value NULL into the address where the array points to.
//          * ar_p_byCurrent = NULL ;
          //
          //         0x10
          // [...]   |a|  <-delete and set to NULL because all children are NULL
          //          |
          //  +-------+------
          //0x10 0x14
          //[   |    | | | | | | ]  <-- all empty/ NULL
        }
      }
    }
#ifdef _DEBUG
    OutputDeletedByteArray_inline(stdvec_by) ;
#endif
    DEBUGN("ar_p_by1LevelAbove:" << ar_p_by1LevelAbove)
  }
  while( ar_p_by1LevelAbove ) ;
  DEBUGN("end of FreeMemory")
}

Trie::~Trie()
{
  LOG("destructor of data structure")
  FreeMemory() ;
  LOG("end of destructor of data structure")
}

bool Trie::exists( //void
  unsigned char * p_vBegin, unsigned short wBytesize)
{
  return exists_inline(p_vBegin,wBytesize, true) ;
}

bool Trie::insert( //void
  unsigned char * p_vBegin, unsigned short wBytesize)
{
  unsigned char ** ar_p_byCurrent = m_ar_p_byRoot ;
  unsigned char ** p_p_ch ;
  BYTE byValue ;
  for( WORD wIndex = 0 ; wIndex < wBytesize ; ++ wIndex )
  {
    byValue = p_vBegin[wIndex] ;
    DEBUGN("address of level: " << ar_p_byCurrent
      << "node address: " << (DWORD) ar_p_byCurrent[ byValue ] )
    if( ar_p_byCurrent[ byValue ] )
      ar_p_byCurrent = (unsigned char **) ar_p_byCurrent[ byValue ] ;
    else
    {
//      p_p_ch = new unsigned char *
//        [ DIFFERENT_VALUES_PER_LEVEL ] ;
//      //store address of created array at address for current byte value
//      // (where the value is/was NULL).
//      ar_p_byCurrent [ byValue ] = p_p_ch ;
//
//      //ar_p_byCurrent = & ar_p_byCurrent [ p_vBegin[wIndex] ] ;
//
//      * ar_p_byCurrent = ar_p_byCurrent [ byValue ] ;

//      ar_p_byCurrent =
//        //get the address of the pointer element with value "NULL".
//        & ar_p_byCurrent [ byValue ] ;
      p_p_ch = new unsigned char *
        [ DIFFERENT_VALUES_PER_LEVEL ] ;
      DEBUGN("address of node where to create a next level: " <<
        & ar_p_byCurrent [ byValue ]
        << " address of created array:" << p_p_ch )
      //Store the address of the created array at the node.
//      * ar_p_byCurrent = (unsigned char *) p_p_ch ;
      ar_p_byCurrent[ byValue ] = (unsigned char *) p_p_ch ;

      ar_p_byCurrent = //(unsigned char **) ar_p_byCurrent[ byValue ] ;
          p_p_ch ;
      //Value will have "abitrary" value -> set to NULL to mark the end.
      //cites from: http://www.cplusplus.com/reference/clibrary/cstring/memset/
      memset( //Pointer to the block of memory to fill.
        ar_p_byCurrent,
        //Value to be set.
        0 ,
        //Number of bytes to be set to the value.
        DIFFERENT_VALUES_PER_LEVEL * sizeof(char*) ) ;
      if( ar_p_byCurrent ) //alloc succeeded
      {
#ifdef _DEBUG
        ++ m_dwNumberOfNodes ;
#endif
      }
      else
        return false ;
    }
  }
  return true ;
}

void Trie::OutputDeletedByteArray_inline( std::vector<unsigned char> &
  stdvec_by )
{
//    DEBUG
  //DEBUG_COUT
//      ( "data structure: deleted: " )
//    std::cout << "data structure: deleted: " ;
//  std::ostringstream  stdostringstream ;
  css::basic_stringstream<LOGGING_CHARACTER_TYPE> stdostringstream ;
//    stdostringstream << "data structure: deleted: " ;
  wSize = stdvec_by.size() ;
  for( WORD wIndex = 0 ; wIndex < wSize ; ++ wIndex )
  {
    ch = stdvec_by.at( wIndex ) ;
//      DEBUG
    //DEBUG_COUT
//        ( "\"" << ch << "\"/" << (WORD) ch << " " )
//      std::cout <<  "\"" << ch << "\"/" << (WORD) ch << " " ;
    stdostringstream << "\"" << ch << "\"/" << (WORD) ch << " " ;
  }
//    DEBUG
  //DEBUG_COUT
//      ( "\n" )
  DEBUG( "data structure: deleted:" << stdostringstream.str()
    << "# nodes: " << m_dwNumberOfNodes )
//    std::cout << "\n" ;
//      stdstrCurrent.clear() ;
  stdvec_by.clear() ;
}
