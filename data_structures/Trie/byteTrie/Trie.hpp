/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */
/*
 * Trie.hpp
 *
 *  Created on: Jul 28, 2010
 *      Author: Stefan
 */

#ifndef TRIE_HPP_
#define TRIE_HPP_

//#include <preprocessor_macros/logging_preprocessor_macros.h> //DEBUGN(...)
#include <windef.h> //for BYTE etc.
#include <string.h> //memset(...)

#include <sstream> //std::ostringstream
#include <vector> //class std::vector

#define DIFFERENT_VALUES_PER_LEVEL 256

class Trie
{
  bool bExists ;
  BYTE byValue ;
  char ch ;
  //Arrays of char pointers.
  unsigned char * m_ar_p_byRoot [DIFFERENT_VALUES_PER_LEVEL] ;
  unsigned char ** ar_p_byCurrent ;
  unsigned short m_wBitsPerLevel ;
  unsigned short wSize ;
  //TODO change data type to fastestUnsignedDataType?
  WORD wIndex ;
public:
  DWORD m_dwNumberOfNodes ;
  void FreeMemory() ;
  Trie()
    : m_dwNumberOfNodes(0)
  {
    memset(m_ar_p_byRoot, 0 ,
      //Number of bytes.
      sizeof(unsigned char *) * DIFFERENT_VALUES_PER_LEVEL ) ;
//    DEBUGN("root node array address: " << m_ar_p_byRoot )
  }
  ~Trie() ;
  bool insert( //void
    unsigned char * p_vBegin, unsigned short wBytesize) ;
  bool exists( //void
    unsigned char * p_vBegin, unsigned short wBytesize) ;

  inline bool IsTrieLeaf(unsigned char ** ar_p_byCurrent)
  { //TODO change data type to fastestUnsignedDataType?
    for( WORD byIndex = 0 ; byIndex < DIFFERENT_VALUES_PER_LEVEL ; ++ byIndex )
      //not NULL->assigned->not a leaf
      if( ar_p_byCurrent[ byIndex ] )
        return false ;
    return true ;
  }
  inline void OutputDeletedByteArray_inline(std::vector<unsigned char> & stdvec_by) ;

  inline bool exists_inline(const std::vector<BYTE> & c_r_std_vec_by,
      //If e.g. "# of bytes" and "# of bytes: 3": if bFullMatch == true, it
      // returns "false, else it returns "true".
      bool bFullMatch )
  {
    bExists = false ;
    //unsigned char ** ar_p_byCurrent = m_ar_p_byRoot ;
    ar_p_byCurrent = m_ar_p_byRoot ;
  //  LOGN("Trie::exists")
    std::vector<BYTE>::const_iterator ci = c_r_std_vec_by.begin();
    for( ; ci != c_r_std_vec_by.end() ; ++ ci )
    {
      byValue = * ci ;
  //    LOGN("Trie::exists ar_p_byCurrent:" << ar_p_byCurrent
  //      << " ar_p_byCurrent[ byValue ]:" << (DWORD) ar_p_byCurrent[ byValue ])

      //If pointer address is not NULL.
      if( ar_p_byCurrent[ byValue ] )
  //      ar_p_byCurrent = & ar_p_byCurrent[ byValue ] ;
        //next level: current node pointer address.
  //      * ar_p_byCurrent = ar_p_byCurrent[ byValue ] ;
        ar_p_byCurrent = (unsigned char **) ar_p_byCurrent[ byValue ] ;
      else
      {
        break ;
      }
    }
    if( bFullMatch //If p_vBegin matches exactly the trie data.
      )
    {
      //All nodes were found -> match.
      if( ci == c_r_std_vec_by.end() )
      { //Also return true id in trie: "hello" and search for "hell"
        bExists = true ;
      }
    }
    else //allow prefix match: e.g. p_vBegin's data: "hello1", data in trie:
      // "hello" -> full prefix match
    {
      //If any of the Trie strings exits at least partly in the param string.
       //wIndex > 0
       if( //Braces around "&&" to avoid Linux g++ warning.
           ( IsTrieLeaf(ar_p_byCurrent)
           //If trie leaf AND trie is empty (wIndex == 0) then do _not_ return
           // "true".
           && ci != c_r_std_vec_by.begin() )
         //if in trie: "hel" and "hello" and search for "hel" then "hel" is
         // not a leaf.
         || ci == c_r_std_vec_by.end() )
         bExists = true ;
    }
    return bExists ;
  }

  inline bool exists_inline( //void
    unsigned char * p_vBegin, unsigned short wBytesize,
    //If e.g. "# of bytes" and "# of bytes: 3": if bFullMatch == true, it
    // returns "false, else it returns "true".
    bool bFullMatch
    )
  {
    bExists = false ;
    //unsigned char ** ar_p_byCurrent = m_ar_p_byRoot ;
    ar_p_byCurrent = m_ar_p_byRoot ;
  //  LOGN("Trie::exists")
    for( wIndex = 0 ; wIndex < wBytesize ; ++ wIndex )
    {
      byValue = p_vBegin[wIndex] ;
  //    LOGN("Trie::exists ar_p_byCurrent:" << ar_p_byCurrent
  //      << " ar_p_byCurrent[ byValue ]:" << (DWORD) ar_p_byCurrent[ byValue ])

      //If pointer address is not NULL.
      if( ar_p_byCurrent[ byValue ] )
  //      ar_p_byCurrent = & ar_p_byCurrent[ byValue ] ;
        //next level: current node pointer address.
  //      * ar_p_byCurrent = ar_p_byCurrent[ byValue ] ;
        ar_p_byCurrent = (unsigned char **) ar_p_byCurrent[ byValue ] ;
      else
      {
        break ;
      }
    }
    if( bFullMatch //If p_vBegin matches exactly the trie data.
      )
    {
      //All nodes were found -> match.
      if( wIndex == wBytesize )
      {
        bExists = true ;
      }
    }
    else //allow prefix match: e.g. p_vBegin's data: "hello1", data in trie:
      // "hello" -> full prefix match
    {
      //If any of the Trie strings exits at least partly in the param string.
       //wIndex > 0
       if( //Braces around "&&" to avoid Linux g++ warning.
           ( IsTrieLeaf(ar_p_byCurrent)
           //If trie leaf AND trie is empty (wIndex == 0) then do _not_ return
           // "true".
           && wIndex > 0 )
         //if in trie: "hel" and "hello" and search for "hel" then "hel" is
         // not a leaf.
         || wIndex == wBytesize )
         bExists = true ;
    }
    return bExists ;
  }
} ;

#endif /* TRIE_HPP_ */
