/*
 * NodeTrie.hpp
 *
 *  Created on: Nov 22, 2010
 *      Author: Stefan
 */
#ifndef NODETRIE_HPP
#define NODETRIE_HPP

#include <preprocessor_macros/logging_preprocessor_macros.h> //DEBUGN(...)
#include <assert.h>

#include "NodeTrieNode.hpp"

//#include "SimpleLinkedList.hpp"

typedef unsigned short WORD;
#ifndef NULL
  #define NULL 0
#endif

//this is the base class of node trie classes:
//subclasses usually add a member with additional info if this node is the
//string end.

//template <typename NodeTrieNode>
template<typename member_type>
  class NodeTrie
  {
  public:
    typedef
      //fast because data type has byte size as CPU register.
      unsigned int
      size_type;
  private:
    bool bExists;
    char ch;
    WORD m_wNodeSizeInByte;
    //#ifdef _DEBUG
    unsigned long m_dwNumberOfNodes;
    //#endif
    unsigned char byValue;
    unsigned short m_wNumberOfNodesPerHierarchyLevel;
    unsigned short m_wIndex;
    unsigned short wSize;

#ifdef _DEBUG
//    SimpleLinkedList<unsigned char> m_simple_linked_list_byte;
#endif
    NodeTrieNode<member_type> ** m_ar_nodetrienodeRoot;
    NodeTrieNode<member_type> m_nodetrienodeRoot;
    NodeTrieNode<member_type> ** m_ar_nodetrienodeCurrent;
    NodeTrieNode<member_type> * m_p_nodetrienodeCurrent;
  public:
    NodeTrie() :
      m_dwNumberOfNodes(0)
    {
      //m_nodetrienodeRoot.m_arp_nodetrienode1LowerLevel = NULL;
      m_nodetrienodeRoot.m_member = NULL;
    }
    void
    Create(unsigned short wNumberOfNodes)
    {
      m_nodetrienodeRoot.Create(wNumberOfNodes);
      m_wNumberOfNodesPerHierarchyLevel = wNumberOfNodes;
      //    m_ar_nodetrienodeRoot = new NodeTrieNode * [
      //      m_wNumberOfNodesPerHierarchyLevel ] ;
      m_wNodeSizeInByte = sizeof(NodeTrieNode<member_type> )
          + sizeof(NodeTrieNode<member_type> *) * wNumberOfNodes
          + sizeof(void *);
    }
    NodeTrie(unsigned short wNumberOfNodes)
    :
          //#ifdef _DEBUG
          m_dwNumberOfNodes(0),
          //#endif
          m_wNumberOfNodesPerHierarchyLevel(wNumberOfNodes),
          m_nodetrienodeRoot(wNumberOfNodes)
    {
      //    m_ar_nodetrienodeRoot = new NodeTrieNode * [
      //      m_wNumberOfNodesPerHierarchyLevel ] ;
      m_wNodeSizeInByte = sizeof(NodeTrieNode<member_type> )
          + sizeof(NodeTrieNode<member_type> *)
              * m_wNumberOfNodesPerHierarchyLevel + sizeof(void *);
    }
    ~NodeTrie()
    {
      LOGN("destructor of data structure")
      FreeMemory();
      //m_nodetrienodeRoot.Delete();
      LOGN("end of destructor of data structure")
    }

    //  type<T> * m_ar_t ;
    //  m_ar_t = new T[arr_size] ;
    //  bool contains(std::string str )
    //  {
    //    for( )
    //      if( m_ar[ str[i] })
    //  }

    //@return pointer to the node that represents the last byte/ character.
    inline//NodeTrieNode **
    NodeTrieNode<member_type> *
    contains_inline( //void
        unsigned char * p_vBegin, //unsigned short wBytesize,
        size_type wBytesize,
        //If e.g. "# of bytes" and "# of bytes: 3": if bFullMatch == true, it
        // returns "false, else it returns "true".
        bool bFullMatch)
    {
#ifdef COMPILE_WITH_LOG
      std::stringstream strstream;
      for (unsigned short wIndex = 0; wIndex < wBytesize; ++wIndex)
        {
          strstream << p_vBegin[wIndex] << " ";
        }
      LOGN("NodeTrie::contains_inline(\"" << strstream.str() << "\")" )
#else
      LOGN("NodeTrie::contains_inline(...," << wBytesize << ")")
#endif
      bExists = false;
      if (m_nodetrienodeRoot.m_arp_nodetrienode1LowerLevel)
        {
          //unsigned char ** ar_p_byCurrent = m_ar_p_byRoot ;
          //m_ar_nodetrienodeCurrent = m_ar_nodetrienodeRoot ;
          m_p_nodetrienodeCurrent = &m_nodetrienodeRoot;
          //  LOGN("Trie::exists")
          for (m_wIndex = 0; m_wIndex < wBytesize; ++m_wIndex)
            {
              byValue = p_vBegin[m_wIndex];
              LOGN("NodeTrie::contains_inline"
                  << " index:" << m_wIndex
                  << " byValue:" << (WORD) byValue
              )
              //If pointer address is not NULL.
              if ( //m_ar_nodetrienodeCurrent[ byValue ]
              m_p_nodetrienodeCurrent->m_arp_nodetrienode1LowerLevel[byValue])
                //      ar_p_byCurrent = & ar_p_byCurrent[ byValue ] ;
                //next level: current node pointer address.
                //      * ar_p_byCurrent = ar_p_byCurrent[ byValue ] ;
                //        m_ar_nodetrienodeCurrent = (NodeTrieNode **)
                m_p_nodetrienodeCurrent =
                //Here the address of the next level is stored.
                    //m_ar_nodetrienodeCurrent[ byValue ] ;
                    m_p_nodetrienodeCurrent->m_arp_nodetrienode1LowerLevel[byValue];
              else
                {
                  break;
                }
            }
          if (bFullMatch //If p_vBegin matches exactly the trie data.
          )
            {
              //All nodes were found -> match.
              if (m_wIndex == wBytesize)
                {
                  //        bExists = true ;
                  return //m_ar_nodetrienodeCurrent ;
                  m_p_nodetrienodeCurrent;
                }
            }
        }
      //    else //allow prefix match: e.g. p_vBegin's data: "hello1", data in trie:
      //      // "hello" -> full prefix match
      //    {
      //      //If any of the Trie strings exits at least partly in the param string.
      //       //m_wIndex > 0
      //       if( IsTrieLeaf(ar_p_byCurrent)
      //           //If trie leaf AND trie is empty (m_wIndex == 0) then do _not_ return
      //           // "true".
      //           && m_wIndex > 0
      //         //if in trie: "hel" and "hello" and search for "hel" then "hel" is
      //         // not a leaf.
      //         || m_wIndex == wBytesize )
      //         bExists = true ;
      //    }
      return //bExists ;
      NULL;
    }
    //  inline bool NoOtherArrayElementsExist_Inline()
    //  {
    //  }
    inline bool
    IsTrieLeaf(NodeTrieNode<member_type> * p_nodetrienodeCurrent)
    {
      for (WORD byIndex = 0; byIndex < m_wNumberOfNodesPerHierarchyLevel; ++byIndex)
        //not NULL->assigned->not a leaf
        if (p_nodetrienodeCurrent->m_arp_nodetrienode1LowerLevel[byIndex])
          return false;
      return true;
    }
    inline //NodeTrieNode **
    //    NodeTrieNode *
    bool
    Delete_inline( //void
        unsigned char * p_vBegin, unsigned short wBytesize)
    {
      NodeTrieNode<member_type> * p_nodetrienode1LevelLower = NULL;
      NodeTrieNode<member_type> * p_nodetrienode1LevelHigher = NULL;
      bool bTrieNodeDeleted;
      bool bContainsByteArray = false;
      m_p_nodetrienodeCurrent = contains_inline(p_vBegin, wBytesize, true);
      if (m_p_nodetrienodeCurrent //byte array exists in the trie.
        &&
        //Only if the node has NO descendant we can delete it.
        IsTrieLeaf(m_p_nodetrienodeCurrent))
      {
        bContainsByteArray = true;
        do
        {
          bTrieNodeDeleted = false;
          m_p_nodetrienodeCurrent = &m_nodetrienodeRoot;
          for (m_wIndex = 0; m_wIndex < wBytesize; ++m_wIndex)
          {
            byValue = p_vBegin[m_wIndex];
            //    LOGN("Trie::exists ar_p_byCurrent:" << ar_p_byCurrent
            //      << " ar_p_byCurrent[ byValue ]:" << (DWORD) ar_p_byCurrent[ byValue ])

            p_nodetrienode1LevelLower
                = m_p_nodetrienodeCurrent-> m_arp_nodetrienode1LowerLevel[byValue];
            //If pointer address is not NULL.
            if ( //m_ar_nodetrienodeCurrent[ byValue ]
              p_nodetrienode1LevelLower)
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
                (NodeTrieNode<member_type> *) ( & m_p_nodetrienodeCurrent->
                  m_arp_nodetrienode1LowerLevel[byValue] );
//                      DEBUGN("address of of trie node 1 level higher:" <<
//                        p_nodetrienode1LevelHigher
//                        )
              m_p_nodetrienodeCurrent = p_nodetrienode1LevelLower;
            }
            else
            //Only if the node has NO descendant we can delete it.
            if (IsTrieLeaf(m_p_nodetrienodeCurrent))
            {
              //Free the memory.
              delete m_p_nodetrienodeCurrent;
              if (p_nodetrienode1LevelHigher)
              {
                //Store the value "0" at the address where the pointer points to.
                //                (NodeTrieNode *) ( * p_nodetrienode1LevelHigher ) = NULL ;
                //                * p_nodetrienode1LevelHigher = NULL ;
                NodeTrieNode<member_type> ** pp_nodetrienode =
                  (NodeTrieNode<member_type> **) p_nodetrienode1LevelHigher;
                * pp_nodetrienode = NULL;
                DEBUGN("set content for bytes at address " <<
                    p_nodetrienode1LevelHigher << " to zero:" <<
                    //                  (NodeTrieNode *) ( * p_nodetrienode1LevelHigher )
                    //                  (void *) * p_nodetrienode1LevelHigher
                    * pp_nodetrienode
                )
              }
              bTrieNodeDeleted = true;
            }
          } //"for" loop
        }
        while (bTrieNodeDeleted);
      }
      return bContainsByteArray;
    }

    //inline void OutputDeletedByteArray(std::vector<unsigned char> & stdvec_by)
    //{
    ////    DEBUG
    //  //DEBUG_COUT
    ////      ( "data structure: deleted: " )
    ////    std::cout << "data structure: deleted: " ;
    //  std::ostringstream  stdostringstream ;
    ////    stdostringstream << "data structure: deleted: " ;
    //  wSize = stdvec_by.size() ;
    //  for( WORD wIndex = 0 ; wIndex < wSize ; ++ wIndex )
    //  {
    //    ch = stdvec_by.at( wIndex ) ;
    ////      DEBUG
    //    //DEBUG_COUT
    ////        ( "\"" << ch << "\"/" << (WORD) ch << " " )
    ////      std::cout <<  "\"" << ch << "\"/" << (WORD) ch << " " ;
    //    stdostringstream << "\"" << ch << "\"/" << (WORD) ch << " " ;
    //  }
    ////    DEBUG
    //  //DEBUG_COUT
    ////      ( "\n" )
    //  DEBUG( "data structure: deleted:" << stdostringstream.str()
    //    << "# nodes: " << m_dwNumberOfNodes )
    ////    std::cout << "\n" ;
    ////      stdstrCurrent.clear() ;
    //  stdvec_by.clear() ;
    //}

    void
    DeleteWithMember()
    {
      if (m_nodetrienodeRoot.m_arp_nodetrienode1LowerLevel)
        {
          //    char ch ;
          NodeTrieNode<member_type> * p_nodetrienodeCurrent = NULL;
          //Arrays of pointers.
          NodeTrieNode<member_type> ** ar_p_nodetrienodeCurrent;
          NodeTrieNode<member_type> ** ar_p_nodetrienode1LevelAbove = NULL;
          //    WORD wSize ;
          DEBUGN("data structure: FreeMemory")

          //    DEBUGN("root node array address: %x", & m_ar_nodetrienodeRoot )

#ifdef _DEBUG
          //    std::string stdstrCurrent ;
          //std::vector<unsigned char> stdvec_by ;
#endif
          //  while( //Root is deleted and set to NULL if it has no more children.
          //      m_ar_p_byRoot )
          do
            {
              //for the case that the root node has no more children.
              ar_p_nodetrienode1LevelAbove = NULL;
              ar_p_nodetrienodeCurrent = //m_ar_nodetrienodeRoot ;
                  m_nodetrienodeRoot.m_arp_nodetrienode1LowerLevel;

              //	  DEBUGN("starting from array at root node array at address %x",
              //		  m_nodetrienodeRoot.m_arp_nodetrienode1LowerLevel)

              //This loop deleted 1 element at the leaf.
              for (WORD wIndex = 0; wIndex < m_wNumberOfNodesPerHierarchyLevel; ++wIndex)
                {
                  if ( //Array element not NULL <=> character at/ for position "wIndex" is
                  //assigned.
                  ar_p_nodetrienodeCurrent[wIndex])
                    {
                      //m_simple_linked_list_byte.AddElement();
                      p_nodetrienodeCurrent = ar_p_nodetrienodeCurrent[wIndex];

                      //			if( wIndex == 0) //"If" here because outputting a '\0' ends the output.
                      //				DEBUGN("NodeTrie:array element at addr %x (content: %x ^= value: %u (' ') ) is assigned",
                      //					ar_p_nodetrienodeCurrent + wIndex,
                      //					ar_p_nodetrienodeCurrent[ wIndex ],
                      //					wIndex)
                      //			else
                      //				DEBUGN("NodeTrie:array element at addr %x (content: %x value: %u ('%c') ) is assigned",
                      //					ar_p_nodetrienodeCurrent + wIndex,
                      //					ar_p_nodetrienodeCurrent[ wIndex ],
                      //					wIndex,
                      //					(char) wIndex
                      //					)

                      ar_p_nodetrienode1LevelAbove =
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
                          ar_p_nodetrienodeCurrent[wIndex];
                      //ar_p_nodetrieCurrent + wIndex;

                      ar_p_nodetrienodeCurrent = //& ar_p_byCurrent[ wIndex ] ;
                          (NodeTrieNode<member_type> **)
                          //Adress of level 1 lower nodetrie stored.
                          ar_p_nodetrienodeCurrent[wIndex]->m_arp_nodetrienode1LowerLevel;
                      //bNoChildNode = false ;
#ifdef _DEBUG
                      //stdvec_by.push_back( (BYTE) wIndex ) ;
#endif
                      //DEBUGN
                      ////DEBUG_COUTN
                      //  ( "entering child node at address %x", ar_p_byCurrent )

                      wIndex = 65535; //MAXWORD ;
                      //found the 1st child: go 1 level deeper.
                      continue;
                    }
                  else
                    {
                      if ( //Index for last array element.
                      wIndex == (m_wNumberOfNodesPerHierarchyLevel - 1))
                        {
                          //          DEBUG_COUTN( //"& address : " << & ar_p_byCurrent
                          //              "value at address " << ar_p_byCurrent
                          //              << ":" << *ar_p_byCurrent )
                          //If at least 2 levels (array should NOT be deleted if it points to
                          //the root node because the root node is created on stack) .
                          if (ar_p_nodetrienode1LevelAbove)
                            {
                              //no child node for current node -> delete current node
                              //				DEBUGN
                              //				//DEBUG_COUTN
                              //				  //("deleting current array at address %x", ar_p_nodetrienodeCurrent )
                              //				  ("deleting NodeTrieNode at address %x, setting value of parent's array element at address %x (*=%x) to 0",
                              //				  p_nodetrienodeCurrent, ar_p_nodetrienode1LevelAbove, * ar_p_nodetrienode1LevelAbove
                              //				  )

                              //DEBUG("Deleting member for element at: ")
                              //while(m_simple_);
                              //	DEBUG();

                              //May NOT be deleted if it points to the root node because the
                              // root node is created on stack .
                              //delete [] ar_p_byCurrent ;
                              if (p_nodetrienodeCurrent->m_member)
                                delete p_nodetrienodeCurrent->m_member;
                              delete p_nodetrienodeCurrent;
#ifdef _DEBUG
                              --m_dwNumberOfNodes;
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
                              *ar_p_nodetrienode1LevelAbove = NULL;
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
              //OutputDeletedByteArray( stdvec_by) ;
#endif
            }
          while (ar_p_nodetrienode1LevelAbove);
          m_nodetrienodeRoot.Delete();
        }
      LOGN("end of FreeMemory")
      assert( m_dwNumberOfNodes == 0);
    }

    void
    FreeMemory()
    {
      //    char ch ;
      if (m_nodetrienodeRoot.m_arp_nodetrienode1LowerLevel)
        {
          NodeTrieNode<member_type> * p_nodetrienodeCurrent = NULL;
          //Arrays of pointers.
          NodeTrieNode<member_type> ** ar_p_nodetrienodeCurrent;
          NodeTrieNode<member_type> ** ar_p_nodetrienode1LevelAbove = NULL;
          //    WORD wSize ;
          DEBUGN("data structure: FreeMemory")

          //    DEBUGN("root node array address: %x", & m_ar_nodetrienodeRoot )

#ifdef _DEBUG
          //    std::string stdstrCurrent ;
          //std::vector<unsigned char> stdvec_by ;
#endif
          //  while( //Root is deleted and set to NULL if it has no more children.
          //      m_ar_p_byRoot )
          do
            {
              //for the case that the root node has no more children.
              ar_p_nodetrienode1LevelAbove = NULL;
              ar_p_nodetrienodeCurrent = //m_ar_nodetrienodeRoot ;
                  m_nodetrienodeRoot.m_arp_nodetrienode1LowerLevel;

              //	  DEBUGN("starting from array at root node array at address %x",
              //		  m_nodetrienodeRoot.m_arp_nodetrienode1LowerLevel)

              //This loop deleted 1 element at the leaf.
              for (WORD wIndex = 0; wIndex < m_wNumberOfNodesPerHierarchyLevel; ++wIndex)
                {
                  if ( //Array element not NULL <=> character at/ for position "wIndex" is
                  //assigned.
                  ar_p_nodetrienodeCurrent[wIndex])
                    {
                      p_nodetrienodeCurrent = ar_p_nodetrienodeCurrent[wIndex];

                      //			if( wIndex == 0) //"If" here because outputting a '\0' ends the output.
                      //				DEBUGN("NodeTrie:array element at addr %x (content: %x ^= value: %u (' ') ) is assigned",
                      //					ar_p_nodetrienodeCurrent + wIndex,
                      //					ar_p_nodetrienodeCurrent[ wIndex ],
                      //					wIndex
                      //					)
                      //			else
                      //				DEBUGN("NodeTrie:array element at addr %x (content: %x value: %u ('%c') ) is assigned",
                      //					ar_p_nodetrienodeCurrent + wIndex,
                      //					ar_p_nodetrienodeCurrent[ wIndex ],
                      //					wIndex,
                      //					(char) wIndex
                      //					)
                      ar_p_nodetrienode1LevelAbove =
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
                          ar_p_nodetrienodeCurrent[wIndex];
                      //ar_p_nodetrieCurrent + wIndex;

                      ar_p_nodetrienodeCurrent = //& ar_p_byCurrent[ wIndex ] ;
                          (NodeTrieNode<member_type> **)
                          //Adress of level 1 lower nodetrie stored.
                          ar_p_nodetrienodeCurrent[wIndex]->m_arp_nodetrienode1LowerLevel;
                      //bNoChildNode = false ;
#ifdef _DEBUG
                      //stdvec_by.push_back( (BYTE) wIndex ) ;
#endif
                      //DEBUGN
                      ////DEBUG_COUTN
                      //  ( "entering child node at address %x", ar_p_byCurrent )

                      wIndex = 65535; //MAXWORD ;
                      //found the 1st child: go 1 level deeper.
                      continue;
                    }
                  else
                    {
                      if ( //Index for last array element.
                      wIndex == (m_wNumberOfNodesPerHierarchyLevel - 1))
                        {
                          //          DEBUG_COUTN( //"& address : " << & ar_p_byCurrent
                          //              "value at address " << ar_p_byCurrent
                          //              << ":" << *ar_p_byCurrent )
                          //If at least 2 levels (array should NOT be deleted if it points to
                          //the root node because the root node is created on stack) .
                          if (ar_p_nodetrienode1LevelAbove)
                            {
                              //no child node for current node -> delete current node
                              //				DEBUGN
                              //				//DEBUG_COUTN
                              //				  //("deleting current array at address %x", ar_p_nodetrienodeCurrent )
                              //				  ("deleting NodeTrieNode at address %x, setting value of parent's array element at address %x (*=%x) to 0",
                              //				  p_nodetrienodeCurrent, ar_p_nodetrienode1LevelAbove, * ar_p_nodetrienode1LevelAbove
                              //				  )
                              //May NOT be deleted if it points to the root node because the
                              // root node is created on stack .
                              //delete [] ar_p_byCurrent ;
                              delete p_nodetrienodeCurrent;
#ifdef _DEBUG
                              -- m_dwNumberOfNodes;
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
                              *ar_p_nodetrienode1LevelAbove = NULL;
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
              //OutputDeletedByteArray( stdvec_by) ;
#endif
            }
          while (ar_p_nodetrienode1LevelAbove);
          m_nodetrienodeRoot.Delete();
        }
#ifdef _DEBUG
      LOGN("end of FreeMemory: # of nodes:" << m_dwNumberOfNodes)
      assert( m_dwNumberOfNodes == 0);
#endif
    }

    //  void
    //      //LinkedList<NodeTrieNode<member_type>
    //  GetNext(
    //	  //Array of nodes that codes the path of the element whose following node is to get.
    //	  //e.g. for "Hi":
    //	  // root (address: 99)
    //	  //  |
    //	  // [0]...['H']   (array address: 100 [1st array element], address of 'H': 173, address at 'H': 400 )
    //	  //         |
    //	  //        [0] ... ['i'] (array address: 200 [1st array element], address of 'i': ca. 300, address at 'i': 500 )
    //	  // -> NodeTrieNode pointer array: [99, 400, 300]
    //	  NodeTrieNode ** & r_ar_p_nodetrienode,
    //		//SimpleLinkedList<NodeTrieNode<member_type>,
    //		unsigned & r_uNumEles
    //		)
    //  {
    //	  if( ! r_ar_p_nodetrienode)
    //		  GetFirst(r_ar_p_nodetrienode);
    //	  else
    //	  {
    ////    char ch ;
    //    //Arrays of pointers.
    //    NodeTrieNode ** ar_p_nodetrienodeCurrent ;
    //    NodeTrieNode ** ar_p_nodetrienode1LevelAbove = NULL ;
    //	NodeTrieNode ** ar_p_nodetrienode = NULL;
    //	unsigned nHierarchyLevel = 0;
    ////    WORD wSize ;
    //    DEBUGN("data structure: GetNext")
    //    DEBUGN("root node array address: " << & m_ar_nodetrienodeRoot )
    //#ifdef _DEBUG
    //  //    std::string stdstrCurrent ;
    //    //std::vector<unsigned char> stdvec_by ;
    //#endif
    //  //  while( //Root is deleted and set to NULL if it has no more children.
    //  //      m_ar_p_byRoot )
    //
    //  if( r_uNumEles > 0)
    //	  -- r_uNumEles;
    //  //Loop: start with the 2nd last NodeTrieNode element (e.g. 'H' from "Hi"), directing 1st element.
    //  //If element of its lower level array is <> NULL and its address is > address for 'i':
    //  //then this is the next node.
    //  while(r_uNumEles)
    //  {
    //    do
    //    {
    //      //for the case that the root node has no more children.
    //      ar_p_nodetrienode1LevelAbove = NULL ;
    //      ar_p_nodetrienodeCurrent = //m_ar_nodetrienodeRoot ;
    //		  //m_nodetrienodeRoot.m_arp_nodetrienode1LowerLevel;
    //		  r_ar_p_nodetrienode[ -- r_uNumEles]->m_arp_nodetrienode1LowerLevel;
    //      //This loop deleted 1 element at the leaf.
    //      for( WORD wIndex = 0 ; wIndex < m_wNumberOfNodesPerHierarchyLevel ;
    //          ++ wIndex )
    //      {
    //        if( //Array element not NULL <=> character at/ for position "wIndex" is
    //            //assigned.
    //            ar_p_nodetrienodeCurrent[ wIndex ]
    //		  )
    //		{
    //			//current element, e.g. 'i' of "Hi"
    //			if( ar_p_nodetrienodeCurrent[ wIndex ] == r_ar_p_nodetrienode[ r_uNumEles] )
    //				bCurrentElementFound = true;
    //			else
    //				if( bCurrentElementFound == true ) //address is higher than of e.g. "i"
    //				{ //ar_p_nodetrienodeCurrent[ wIndex ] > r_ar_p_nodetrienode[ r_uNumEles]
    //					do
    //					{
    //
    //					}
    //				}
    //		  )
    //        {
    //			ar_p_nodetrienode = (NodeTrieNode **) RE_ALLOC( ar_p_nodetrienode, ++ nHierarchyLevel);
    //          ar_p_by1LevelAbove =
    //            //Address of array element.
    //            &
    //            //Address of next array/ level directing leaves:
    //            //         0x10
    //            // [...]   |a|
    //            //          |
    //            //  +-------+------
    //            // 0x10   0x14 0x18 ...  <-- " & r_p_byCurrent[ wIndex ] "
    //            //[0x999|0x777|0x123| | | | | ]  <-- r_p_byCurrent[ wIndex ]
    //
    //            //         " & r_p_byCurrent[ wIndex ] " = "r_p_byCurrent + wIndex" ?
    //
    //            //Store the address of array element "ar_p_byCurrent[ wIndex ]"
    //            //because the current address will be changed to the address of
    //            //element by 1 level below (=directing leaves).
    //            ar_p_byCurrent[ wIndex ] ;
    //
    //          ar_p_byCurrent = //& ar_p_byCurrent[ wIndex ] ;
    //            (NodeTrieNode **)
    //			//Adress of level 1 lower nodetrie stored.
    //			ar_p_byCurrent[ wIndex ]->m_arp_nodetrienode1LowerLevel ;
    //          //bNoChildNode = false ;
    //#ifdef _DEBUG
    //          //stdvec_by.push_back( (BYTE) wIndex ) ;
    //#endif
    //          DEBUGN
    //          //DEBUG_COUTN
    //            ( "entering child node at address " << ar_p_byCurrent )
    //
    //          wIndex = 65535 ; //MAXWORD ;
    //          //found the 1st child: go 1 level deeper.
    //          continue ;
    //        }
    //        else
    //        {
    //          if( //Index for last array element.
    //              wIndex == ( m_wNumberOfNodesPerHierarchyLevel - 1 ) )
    //          {
    //            //If at least 2 levels (array should NOT be deleted if it points to
    //            //the root node because the root node is created on stack) .
    //            if( ar_p_by1LevelAbove )
    //            {
    //				return
    //            }
    //            else
    //            {
    //  //            DEBUGN
    //  //            //DEBUG_COUTN
    //  //              ("deleting root array at address" << m_ar_p_byRoot)
    //  //            m_ar_p_byRoot = NULL ;
    //  //            delete [] m_ar_p_byRoot ;
    //  //            -- m_dwNumberOfNodes ;
    //              DEBUGN("We are at the root node.")
    //  //            m_ar_p_byRoot = NULL ;
    //            }
    //  //          break ;
    //            //mark the end -> do no delete the 2nd time.
    //  //           & ar_p_byCurrent = NULL ;
    //            //write value NULL into the address where the array points to.
    //  //          * ar_p_byCurrent = NULL ;
    //            //
    //            //         0x10
    //            // [...]   |a|  <-delete and set to NULL because all children are NULL
    //            //          |
    //            //  +-------+------
    //            //0x10 0x14
    //            //[   |    | | | | | | ]  <-- all empty/ NULL
    //          }
    //        }
    //      }
    //#ifdef _DEBUG
    //      //OutputDeletedByteArray( stdvec_by) ;
    //#endif
    //    }
    //    while( ar_p_by1LevelAbove ) ;
    //  }

    NodeTrieNode<member_type> *
    CreateNodes(NodeTrieNode<member_type> * p_nodetrienodeCurrent,
        unsigned char * p_vBegin, unsigned short wBytesize)
    {
      BYTE byValue;
      NodeTrieNode<member_type> * p_nodetrienodeNew = NULL;
      for (WORD wIndex = 0; wIndex < wBytesize; ++wIndex)
        {
          byValue = p_vBegin[wIndex];
          //      //store address of created array at address for current byte value
          //      // (where the value is/was NULL).
          //      ar_p_byCurrent [ byValue ] = p_p_ch ;
          //
          //        p_p_nodetrienode = new NodeTrieNode *
          //          [ m_wNumberOfNodesPerHierarchyLevel ] ;

          //NodeTrieNode<member_type> * p_nodetrienode =//
          p_nodetrienodeNew = new NodeTrieNode<member_type> (
              m_wNumberOfNodesPerHierarchyLevel);
          //Allocation succeeded.
          if ( //ar_nodetrienodeCurrent
          //p_nodetrienode
          p_nodetrienodeNew)
            {
              //Importent when deleting node _and_ member: only members with value <> 0 are deleted.
              p_nodetrienodeNew->m_member = 0;
              //LOGN
              // DEBUGN("# nodes:" << m_dwNumberOfNodes << " overall size="
              //<< m_wNodeSizeInByte << "*" << m_dwNumberOfNodes << "="
              //<< m_wNodeSizeInByte * m_dwNumberOfNodes
              //<< "Address of node where to create a next level: " <<
              //& p_nodetrienodeCurrent->m_arp_nodetrienode1LowerLevel [ byValue ]
              //<< " address of created "
              //	//"array:" << //p_nodetrienode
              //	"node:"
              //	p_nodetrienodeNew
              //	)
              //Store the address of the created array at the node.
              //        ar_nodetrienodeCurrent[ byValue ] = (NodeTrieNode *) p_p_nodetrienode ;
              p_nodetrienodeCurrent->m_arp_nodetrienode1LowerLevel[byValue] =
              //p_nodetrienode ;
                  p_nodetrienodeNew;
//              if (byValue != 0)
//                DEBUGN("created new node at address %x, array address:%x for value %u ('%c') and assigned it to parent's array element %x",
//                  p_nodetrienodeNew,
//                  p_nodetrienodeNew->m_arp_nodetrienode1LowerLevel,
//                  (WORD) byValue, byValue,
//                  & p_nodetrienodeCurrent->m_arp_nodetrienode1LowerLevel[ byValue]
//                  )
//              else
//                DEBUGN("created new node at address %x, array address:%x for value %u and assigned it to parent's array element %x",
//                  p_nodetrienodeNew,
//                  p_nodetrienodeNew->m_arp_nodetrienode1LowerLevel,
//                  (WORD) byValue,
//                  & p_nodetrienodeCurrent->m_arp_nodetrienode1LowerLevel [ byValue]
//                  )

                  p_nodetrienodeCurrent = p_nodetrienodeNew;

                  //        ar_nodetrienodeCurrent = //(unsigned char **) ar_p_byCurrent[ byValue ] ;
                  //            p_p_nodetrienode ;

                  //        //Value will have "abitrary" value -> set to NULL to mark the end.
                  //        //cites from: http://www.cplusplus.com/reference/clibrary/cstring/memset/
                  //        memset( //Pointer to the block of memory to fill.
                  ////          ar_nodetrienodeCurrent,
                  //          p_nodetrienodeCurrent->m_arp_nodetrienode1LowerLevel ,
                  //          //Value to be set.
                  //          0 ,
                  //          //Number of bytes to be set to the value.
                  //          m_wNumberOfNodesPerHierarchyLevel * sizeof(NodeTrieNode *)
                  //          ) ;
                  //  #ifdef _DEBUG
                  ++m_dwNumberOfNodes;
                  //  #endif
                }
              else
                {
                  LOGN("NodeTrie::insert_inline(...)--allocating a node failed--"
                      "return NULL")
                  return //false ;
                  NULL;
                }
            }
          return p_nodetrienodeCurrent;
        }

        //NodeTrieNode **
        NodeTrieNode<member_type> *
        insert_inline( //void
            unsigned char * p_vBegin, unsigned short wBytesize)
        {
#ifdef COMPILE_WITH_LOG
          std::ostringstream strstream;
          for (unsigned short wIndex = 0; wIndex < wBytesize; ++wIndex)
            {
              strstream << (WORD) p_vBegin[wIndex] << " ";
            }
          std::string stdstr = strstream.str();
          LOGN("NodeTrie::insert_inline(\"" << stdstr << "\","
              << wBytesize << ")" )
#else
          LOGN("NodeTrie::insert_inline()" )
#endif
          //    NodeTrieNode ** ar_nodetrienodeCurrent = m_ar_nodetrienodeRoot ;
          if (m_nodetrienodeRoot.m_arp_nodetrienode1LowerLevel)
            {
              NodeTrieNode<member_type> * p_nodetrienodeCurrent =
                  &m_nodetrienodeRoot;

              //		DEBUGN("address of root node: %x, address of its array: %x",
              //			p_nodetrienodeCurrent,
              //			m_nodetrienodeRoot.m_arp_nodetrienode1LowerLevel)

              //    NodeTrieNode ** p_p_nodetrienode ;
              BYTE byValue;
              //NodeTrieNode<member_type> * p_nodetrienodeNew = NULL;
              for (WORD wIndex = 0; wIndex < wBytesize; ++wIndex)
                {
                  byValue = p_vBegin[wIndex];
                  LOGN("address of level: " << p_nodetrienodeCurrent
                      << "node address: " << (DWORD) p_nodetrienodeCurrent->
                      m_arp_nodetrienode1LowerLevel[ byValue ]
                      << " index:" << wIndex
                      << " character:" << p_vBegin[wIndex]
                  )
                  if ( //ar_nodetrienodeCurrent[ byValue ]
                  p_nodetrienodeCurrent->m_arp_nodetrienode1LowerLevel[byValue])
                    //        ar_nodetrienodeCurrent = (NodeTrieNode **) ar_nodetrienodeCurrent[
                    //          byValue ] ;
                    p_nodetrienodeCurrent
                        = p_nodetrienodeCurrent-> m_arp_nodetrienode1LowerLevel[byValue];
                  //;
                  else // value array element is NULL -> end of string
                    {
                      //The child node of all following nodes are NULL because they are
                      //created So execute the creation in another loop to avoid the unneeded test
                      // "if(p_nodetrienodeCurrent->m_arp_nodetrienode1LowerLevel[ byValue ] )".
                      return CreateNodes(p_nodetrienodeCurrent, p_vBegin
                          + wIndex, wBytesize - wIndex);
                    }
                  //p_nodetrienodeCurrent = p_nodetrienodeCurrent->m_arp_nodetrienode1LowerLevel[ byValue ];
                } //"for" loop
              LOGN("NodeTrie::insert_inline(...)--return " << p_nodetrienodeCurrent )
              return //true ;
              //ar_nodetrienodeCurrent ;
              p_nodetrienodeCurrent;
            }
          else
            return NULL;
        }
        NodeTrieNode<member_type> *
        insert_inline(
            //void
            unsigned char * p_vBegin, unsigned short wBytesize,
            member_type member_value)
        {
          NodeTrieNode<member_type> * p = insert_inline( //void
              p_vBegin, wBytesize);
          if (p)
            p->m_member = member_value;
          return p;
        }
      };

#endif //#ifndef NODETRIE_HPP
