/*
 * NodeTrie.hpp
 *
 *  Created on: Nov 22, 2010
 *      Author: Stefan
 */
#ifndef NODETRIE_HPP
  #define NODETRIE_HPP

#include <preprocessor_macros/logging_preprocessor_macros.h> //DEBUGN(...)

class NodeTrieNode
{
//private:
public:
  NodeTrieNode(unsigned short wNumberOfNodesPerHierarchyLevel)
    :
//    m_arp_nodetrienode1LowerLevel(NULL)
    m_pv(NULL)
  {
    m_arp_nodetrienode1LowerLevel = new NodeTrieNode * [
      wNumberOfNodesPerHierarchyLevel] ;
  }
  ~NodeTrieNode()
  {
    delete [] m_arp_nodetrienode1LowerLevel ;
    m_arp_nodetrienode1LowerLevel = NULL ;
  }
  NodeTrieNode ** m_arp_nodetrienode1LowerLevel ;
  //pointer to spectific attributes
  void * m_pv ;
};

//this is the base class of node trie classes:
//subclasses usually add a member with additional info if this node is the
//string end.

//template <typename NodeTrieNode>
class NodeTrie
{
  bool bExists ;
  char ch ;
#ifdef _DEBUG
  unsigned long m_dwNumberOfNodes ;
#endif
  unsigned char byValue ;
  unsigned short m_wNumberOfNodesPerHierarchyLevel ;
  unsigned short wIndex ;
  unsigned short wSize ;
  NodeTrieNode ** m_ar_nodetrienodeRoot ;
  NodeTrieNode m_nodetrienodeRoot ;
  NodeTrieNode ** m_ar_nodetrienodeCurrent ;
  NodeTrieNode * m_p_nodetrienodeCurrent ;
public:
  NodeTrie( unsigned short wNumberOfNodes )
    :
#ifdef _DEBUG
    m_dwNumberOfNodes(0) ,
#endif
    m_wNumberOfNodesPerHierarchyLevel( wNumberOfNodes )
    , m_nodetrienodeRoot(wNumberOfNodes)
  {
//    m_ar_nodetrienodeRoot = new NodeTrieNode * [
//      m_wNumberOfNodesPerHierarchyLevel ] ;
  }
  ~NodeTrie()
  {
    LOG("destructor of data structure")
    FreeMemory() ;
    LOG("end of destructor of data structure")
  }

//  type<T> * m_ar_t ;
//  m_ar_t = new T[arr_size] ;
//  bool contains(std::string str )
//  {
//    for( )
//      if( m_ar[ str[i] })
//  }

  //@return pointer to the node that represents the last byte/ character.
  inline //NodeTrieNode **
    NodeTrieNode *
    contains_inline( //void
    unsigned char * p_vBegin,
    unsigned short wBytesize,
    //If e.g. "# of bytes" and "# of bytes: 3": if bFullMatch == true, it
    // returns "false, else it returns "true".
    bool bFullMatch
    )
  {
    LOGN("NodeTrie::contains_inline(...," << wBytesize << ")")
    bExists = false ;
    //unsigned char ** ar_p_byCurrent = m_ar_p_byRoot ;
    //m_ar_nodetrienodeCurrent = m_ar_nodetrienodeRoot ;
    m_p_nodetrienodeCurrent = & m_nodetrienodeRoot ;
  //  LOGN("Trie::exists")
    for( wIndex = 0 ; wIndex < wBytesize ; ++ wIndex )
    {
      byValue = p_vBegin[wIndex] ;
      LOGN("NodeTrie::contains_inline"
        << " index:" << wIndex
        << " byValue:" << (WORD) byValue
        )
      //If pointer address is not NULL.
      if( //m_ar_nodetrienodeCurrent[ byValue ]
          m_p_nodetrienodeCurrent->m_arp_nodetrienode1LowerLevel[ byValue ]
        )
  //      ar_p_byCurrent = & ar_p_byCurrent[ byValue ] ;
        //next level: current node pointer address.
  //      * ar_p_byCurrent = ar_p_byCurrent[ byValue ] ;
//        m_ar_nodetrienodeCurrent = (NodeTrieNode **)
        m_p_nodetrienodeCurrent =
          //Here the address of the next level is stored.
          //m_ar_nodetrienodeCurrent[ byValue ] ;
          m_p_nodetrienodeCurrent->m_arp_nodetrienode1LowerLevel[ byValue ] ;
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
//        bExists = true ;
        return //m_ar_nodetrienodeCurrent ;
          m_p_nodetrienodeCurrent ;
      }
    }
//    else //allow prefix match: e.g. p_vBegin's data: "hello1", data in trie:
//      // "hello" -> full prefix match
//    {
//      //If any of the Trie strings exits at least partly in the param string.
//       //wIndex > 0
//       if( IsTrieLeaf(ar_p_byCurrent)
//           //If trie leaf AND trie is empty (wIndex == 0) then do _not_ return
//           // "true".
//           && wIndex > 0
//         //if in trie: "hel" and "hello" and search for "hel" then "hel" is
//         // not a leaf.
//         || wIndex == wBytesize )
//         bExists = true ;
//    }
    return //bExists ;
      NULL ;
  }
//  inline bool NoOtherArrayElementsExist_Inline()
//  {
//  }
  inline bool IsTrieLeaf(NodeTrieNode * p_nodetrienodeCurrent)
  {
    for( WORD byIndex = 0 ; byIndex < m_wNumberOfNodesPerHierarchyLevel ;
        ++ byIndex )
      //not NULL->assigned->not a leaf
      if( p_nodetrienodeCurrent->m_arp_nodetrienode1LowerLevel[ byIndex ] )
        return false ;
    return true ;
  }
  inline //NodeTrieNode **
//    NodeTrieNode *
    bool
    Delete_inline( //void
    unsigned char * p_vBegin,
    unsigned short wBytesize
    )
  {
    NodeTrieNode * p_nodetrienode1LevelLower = NULL ;
    NodeTrieNode * p_nodetrienode1LevelHigher = NULL ;
    bool bTrieNodeDeleted ;
    bool bContainsByteArray = false ;
    m_p_nodetrienodeCurrent = contains_inline(p_vBegin, wBytesize, true) ;
    if( m_p_nodetrienodeCurrent //byte array exists in the trie.
      &&
      //Only if the node has NO descendant we can delete it.
      IsTrieLeaf(m_p_nodetrienodeCurrent)
      )
    {
      bContainsByteArray = true ;
      do
      {
        bTrieNodeDeleted = false ;
        m_p_nodetrienodeCurrent = & m_nodetrienodeRoot ;
        for( wIndex = 0 ; wIndex < wBytesize ; ++ wIndex )
        {
          byValue = p_vBegin[wIndex] ;
      //    LOGN("Trie::exists ar_p_byCurrent:" << ar_p_byCurrent
      //      << " ar_p_byCurrent[ byValue ]:" << (DWORD) ar_p_byCurrent[ byValue ])

          p_nodetrienode1LevelLower = m_p_nodetrienodeCurrent->
            m_arp_nodetrienode1LowerLevel[ byValue ] ;
          //If pointer address is not NULL.
          if( //m_ar_nodetrienodeCurrent[ byValue ]
              p_nodetrienode1LevelLower
            )
          {
    //        if( NoOtherArrayElementsExist_Inline(byValue) )
    //        {
    //          p = m_p_nodetrienodeCurrent ;
    //          delete m_p_nodetrienodeCurrent ;
    //        }
            p_nodetrienode1LevelHigher = //m_p_nodetrienodeCurrent ;
              //The address of the array element where the address if the next
              //lower level trie node is stored:
              //e.g. for string "b":
              //
              //    root node
              //       |
              // 0x100  0x104 0x108 ... <-address of the array element
              //[0x111][0x745] ... <-address INSIDE the array element
              //->for "b": store address of the 2nd array element ("0x104")
              (NodeTrieNode *)
              ( & m_p_nodetrienodeCurrent->m_arp_nodetrienode1LowerLevel[
              byValue ] );
            DEBUGN("address of of trie node 1 level higher:" <<
              p_nodetrienode1LevelHigher )
            m_p_nodetrienodeCurrent = p_nodetrienode1LevelLower ;
          }
          else
            //Only if the node has NO descendant we can delete it.
            if( IsTrieLeaf(m_p_nodetrienodeCurrent) )
            {
              //Free the memory.
              delete m_p_nodetrienodeCurrent ;
              if( p_nodetrienode1LevelHigher )
              {
                //Store the value "0" at the address where the pointer points to.
//                (NodeTrieNode *) ( * p_nodetrienode1LevelHigher ) = NULL ;
//                * p_nodetrienode1LevelHigher = NULL ;
                NodeTrieNode ** pp_nodetrienode = (NodeTrieNode **)
                  p_nodetrienode1LevelHigher ;
                * pp_nodetrienode = NULL ;
                DEBUGN("set content for bytes at address " <<
                  p_nodetrienode1LevelHigher << " to zero:" <<
//                  (NodeTrieNode *) ( * p_nodetrienode1LevelHigher )
//                  (void *) * p_nodetrienode1LevelHigher
                  * pp_nodetrienode
                  )
              }
              bTrieNodeDeleted = true ;
            }
        }
      }
      while( bTrieNodeDeleted ) ;
    }
    return bContainsByteArray ;
  }

  inline void OutputDeletedByteArray(std::vector<unsigned char> & stdvec_by)
  {
  //    DEBUG
    //DEBUG_COUT
  //      ( "data structure: deleted: " )
  //    std::cout << "data structure: deleted: " ;
    std::ostringstream  stdostringstream ;
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

  void FreeMemory()
  {
//    char ch ;
    //Arrays of pointers.
    NodeTrieNode ** ar_p_byCurrent ;
    NodeTrieNode ** ar_p_by1LevelAbove = NULL ;
    WORD wSize ;
    DEBUGN("data structure: FreeMemory")
    DEBUGN("root node array address: " << & m_ar_nodetrienodeRoot )
#ifdef _DEBUG
  //    std::string stdstrCurrent ;
    std::vector<unsigned char> stdvec_by ;
#endif
  //  while( //Root is deleted and set to NULL if it has no more children.
  //      m_ar_p_byRoot )
    do
    {
      //for the case that the root node has no more children.
      ar_p_by1LevelAbove = NULL ;
      ar_p_byCurrent = m_ar_nodetrienodeRoot ;
      //This loop deleted 1 element at the leaf.
      for( WORD wIndex = 0 ; wIndex < m_wNumberOfNodesPerHierarchyLevel ;
          ++ wIndex )
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
            (NodeTrieNode **) ar_p_byCurrent[ wIndex ] ;
          //bNoChildNode = false ;
#ifdef _DEBUG
          stdvec_by.push_back( (BYTE) wIndex ) ;
#endif
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
              wIndex == ( m_wNumberOfNodesPerHierarchyLevel - 1 ) )
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
#ifdef _DEBUG
              -- m_dwNumberOfNodes ;
#endif //#ifdef _DEBUG
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
      OutputDeletedByteArray( stdvec_by) ;
#endif
    }
    while( ar_p_by1LevelAbove ) ;
    LOGN("end of FreeMemory")
  }

  //NodeTrieNode **
  NodeTrieNode * insert_inline( //void
    unsigned char * p_vBegin, unsigned short wBytesize)
  {
//    NodeTrieNode ** ar_nodetrienodeCurrent = m_ar_nodetrienodeRoot ;
    NodeTrieNode * p_nodetrienodeCurrent = & m_nodetrienodeRoot ;
//    NodeTrieNode ** p_p_nodetrienode ;
    BYTE byValue ;
    for( WORD wIndex = 0 ; wIndex < wBytesize ; ++ wIndex )
    {
      byValue = p_vBegin[wIndex] ;
      DEBUGN("address of level: " << p_nodetrienodeCurrent
        << "node address: " << (DWORD) p_nodetrienodeCurrent->
        m_arp_nodetrienode1LowerLevel[ byValue ] )
      if( //ar_nodetrienodeCurrent[ byValue ]
          p_nodetrienodeCurrent->m_arp_nodetrienode1LowerLevel[ byValue ]
        )
//        ar_nodetrienodeCurrent = (NodeTrieNode **) ar_nodetrienodeCurrent[
//          byValue ] ;
        p_nodetrienodeCurrent = p_nodetrienodeCurrent->
          m_arp_nodetrienode1LowerLevel[ byValue ] ;
      else // value array element is NULL -> end of string
      {
  //      //store address of created array at address for current byte value
  //      // (where the value is/was NULL).
  //      ar_p_byCurrent [ byValue ] = p_p_ch ;
  //
//        p_p_nodetrienode = new NodeTrieNode *
//          [ m_wNumberOfNodesPerHierarchyLevel ] ;

        NodeTrieNode * p_nodetrienode = new NodeTrieNode(
          m_wNumberOfNodesPerHierarchyLevel ) ;
        DEBUGN("address of node where to create a next level: " <<
          & p_nodetrienodeCurrent->m_arp_nodetrienode1LowerLevel [ byValue ]
          << " address of created array:" << p_nodetrienode )

        //Store the address of the created array at the node.
//        ar_nodetrienodeCurrent[ byValue ] = (NodeTrieNode *) p_p_nodetrienode ;
        p_nodetrienodeCurrent->m_arp_nodetrienode1LowerLevel[ byValue ] =
          p_nodetrienode ;

//        ar_nodetrienodeCurrent = //(unsigned char **) ar_p_byCurrent[ byValue ] ;
//            p_p_nodetrienode ;
        //Value will have "abitrary" value -> set to NULL to mark the end.
        //cites from: http://www.cplusplus.com/reference/clibrary/cstring/memset/
        memset( //Pointer to the block of memory to fill.
//          ar_nodetrienodeCurrent,
          p_nodetrienodeCurrent->m_arp_nodetrienode1LowerLevel ,
          //Value to be set.
          0 ,
          //Number of bytes to be set to the value.
          m_wNumberOfNodesPerHierarchyLevel * sizeof(NodeTrieNode *) ) ;
        //Allocation succeeded.
        if( //ar_nodetrienodeCurrent
            p_nodetrienode
          )
        {
  #ifdef _DEBUG
          ++ m_dwNumberOfNodes ;
  #endif
        }
        else
          return //false ;
            NULL ;
      }
    }
    return //true ;
      //ar_nodetrienodeCurrent ;
      p_nodetrienodeCurrent ;
  }
} ;

#endif //#ifndef NODETRIE_HPP
