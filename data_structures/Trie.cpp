/*
 * Trie.cpp
 *
 *  Created on: Jul 28, 2010
 *      Author: Stefan
 */
#include <preprocessor_macros/logging_preprocessor_macros.h>
#include <vector>
#include <windef.h> //BYTE etc.

#include "Trie.hpp"

Trie::~Trie()
{
  unsigned char ** ar_p_byCurrent ;
  unsigned char ** ar_p_by1LevelAbove = NULL ;
//    std::string stdstrCurrent ;
  std::vector<unsigned char> stdvec_by ;
  LOG("destructor of data structure")
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
      if( ar_p_byCurrent[ wIndex ] )
      {
        ar_p_by1LevelAbove = & ar_p_byCurrent[ wIndex ] ;
        ar_p_byCurrent = //& ar_p_byCurrent[ wIndex ] ;
        (unsigned char **) ar_p_byCurrent[ wIndex ] ;
        //bNoChildNode = false ;
        stdvec_by.push_back( (BYTE) wIndex ) ;
        DEBUG_COUTN( "entering child node at address " << ar_p_byCurrent )

        wIndex = 65535 ; //MAXWORD ;
        //found the 1st child: go 1 level deeper.
        continue ;
      }
      else
      {
        if( wIndex == ( DIFFERENT_VALUES_PER_LEVEL - 1 ) )
        {
//          DEBUG_COUTN( //"& address : " << & ar_p_byCurrent
//              "value at address " << ar_p_byCurrent
//              << ":" << *ar_p_byCurrent )
          //no child node for current node -> delete current node
          delete [] ar_p_byCurrent ;
          if( ar_p_by1LevelAbove )
            * ar_p_by1LevelAbove = NULL ;
          else
//            m_ar_p_byRoot = NULL ;
            delete [] m_ar_p_byRoot ;
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
    DEBUG_COUT( "data structure: deleted: " )
//    std::cout << "data structure: deleted: " ;
    char ch ;
    WORD wSize = stdvec_by.size() ;
    for( WORD wIndex = 0 ; wIndex < wSize ; ++ wIndex )
    {
      ch = stdvec_by.at( wIndex ) ;
      DEBUG_COUT( "\"" << ch << "\"/" << (WORD) ch << " " )
//      std::cout <<  "\"" << ch << "\"/" << (WORD) ch << " " ;
    }
    DEBUG_COUT( "\n" )
//    std::cout << "\n" ;
//      stdstrCurrent.clear() ;
    stdvec_by.clear() ;
  }
  while( ar_p_by1LevelAbove ) ;
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

      }
      else
        return false ;
    }
  }
  return true ;
}
