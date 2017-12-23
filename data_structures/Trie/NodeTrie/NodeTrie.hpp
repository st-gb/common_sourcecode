/** NodeTrie.hpp
 *  Created on: Nov 22, 2010
 *      Author: Stefan    */
#ifndef NODETRIE_HPP
#define NODETRIE_HPP

#ifdef COMPILE_NODETRIE_WITH_LOGGING
  #include <preprocessor_macros/logging_preprocessor_macros.h> //DEBUGN(...)
  #define DEBUGN_NODETRIE(str) DEBUGN(str)
  #define LOGN_NODETRIE(str) LOGN(str)
#else
//  #ifdef DEBUGN
//    #undef DEBUGN
//  #endif //#ifdef DEBUGN
  #define DEBUGN_NODETRIE(str) /* -> empty */
//  #ifdef LOGN
//    #undef LOGN
//  #endif //#ifdef LOGN
  #define LOGN_NODETRIE(str) /* -> empty */
#endif

#include <assert.h>
#include <sstream> //class std::stringstream
#include "NodeTrieNode.hpp"
#include <hardware/CPU/fastest_data_type.h>

//#include "SimpleLinkedList.hpp"

typedef unsigned short WORD;
#ifndef NULL
  #define NULL 0
#endif

#include "exceptions.hpp"

#include "NodeTrieIterator.hpp"

//this is the base class of node trie classes:
//subclasses usually add a member with additional info if this node is the
//string end.

//template <typename NodeTrieNode>
template<typename member_type>
  class NodeTrie
  {
  public:
    typedef unsigned int size_type;

    /** See https://stackoverflow.com/questions/3582608/how-to-correctly-implement-custom-iterators-and-const-iterators */
    typedef NodeTrieIterator<member_type>              iterator;
    typedef NodeTrieIterator<const member_type>        const_iterator;    
  private:
      bool bExists;
      char ch;
      WORD m_wNodeSizeInByte;
      unsigned long m_dwNumberOfNodes;
      /** # of node that have attribute data attached*/
      unsigned m_numInfoNodes;
      member_type m_defaultValue;
      unsigned char byValue;
      unsigned short m_wNumberOfNodesPerHierarchyLevel;
      unsigned short m_wIndex;
      unsigned short wSize;
      NodeTrieNode<member_type> **m_ar_nodetrienodeRoot;
      NodeTrieNode<member_type> m_nodetrienodeRoot;
      NodeTrieNode<member_type> **m_ar_nodetrienodeCurrent;
      NodeTrieNode<member_type> *m_p_nodetrienodeCurrent;
  public:
      NodeTrie()
       : m_dwNumberOfNodes(0), m_numInfoNodes(0)
      {
        m_nodetrienodeRoot.m_member = NULL;
      }

      NodeTrie(fastestUnsignedDataType numberOfNodesPerHierarchyLevel, 
              member_type defaultValue)
        : m_dwNumberOfNodes(0), 
          m_numInfoNodes(0), 
          m_defaultValue(defaultValue),
          m_wNumberOfNodesPerHierarchyLevel(numberOfNodesPerHierarchyLevel),
          m_nodetrienodeRoot(numberOfNodesPerHierarchyLevel, defaultValue)
      {
          m_wNodeSizeInByte = sizeof (NodeTrieNode<member_type>)
            + sizeof (NodeTrieNode<member_type>*) * m_wNumberOfNodesPerHierarchyLevel
            + sizeof (void*);
      }

      ~NodeTrie()
      {
        FreeMemory();
//        assert( m_dwNumberOfNodes == 0);
      }
      
//      typedef 
//
      NodeTrieNode<member_type> * traverseDirectingLeaves(
        NodeTrieIterator<member_type> & nodeTrieIterator,
        NodeTrieNode<member_type> * p_nodetrienodeCurrent) const
      {
        for(fastestUnsignedDataType arrayIndex = 0;
            arrayIndex < m_wNumberOfNodesPerHierarchyLevel; 
            ++ arrayIndex)
        {
          if(p_nodetrienodeCurrent->m_arp_nodetrienode1LowerLevel[arrayIndex])
          {
            nodeTrieIterator.addVisitedNode(
              TrieNodeArrayAndArrayIndex<member_type>(p_nodetrienodeCurrent, arrayIndex) );
            p_nodetrienodeCurrent = p_nodetrienodeCurrent->m_arp_nodetrienode1LowerLevel[arrayIndex];
            if( p_nodetrienodeCurrent->m_member != m_defaultValue )
            {
//              nodeTrieIterator.SetInfoNode();
              return p_nodetrienodeCurrent;
            }
//            p_nodetrienodeSuperordinate = p_nodetrienodeCurrent;
            arrayIndex = 0;
            continue;
          }
        }
        return NULL;
      }
      
      iterator end()
      {
        return NodeTrieIterator<member_type>(/*m_nodetrienodeRoot*/*this, NULL, NULL);
      }
      
      iterator begin()
      {
        NodeTrieNode<member_type> * p_nodetrienodeCurrent = NULL;
        NodeTrieNode<member_type> * p_nodetrienodeSuperordinate = NULL;
        if(m_nodetrienodeRoot.m_arp_nodetrienode1LowerLevel)
        {
          p_nodetrienodeCurrent = & m_nodetrienodeRoot;
          p_nodetrienodeSuperordinate = & m_nodetrienodeRoot; 
          NodeTrieIterator<member_type> nodeTrieIterator(/*m_nodetrienodeRoot,*/
            * this,
            p_nodetrienodeSuperordinate, p_nodetrienodeCurrent);
          
          traverseDirectingLeaves(nodeTrieIterator, p_nodetrienodeCurrent);
          return nodeTrieIterator;
        }
        return /*NodeTrieIterator<member_type>(*this, NULL, NULL)*/ end();
      }
      
      NodeTrieNode<member_type> * GetNextNodeAtHigherArrayIndex(
        TrieNodeArrayAndArrayIndex<member_type> & trieNodeArrayAndArrayIndex,
        NodeTrieIterator<member_type> * p_nodeTrieIterator) const
      {
        NodeTrieNode<member_type> * p_nodetrienodeCurrent = trieNodeArrayAndArrayIndex.p_NodeTrie;

        for(fastestUnsignedDataType arrayIndex = trieNodeArrayAndArrayIndex.arrayIndex + 1; 
            arrayIndex < m_wNumberOfNodesPerHierarchyLevel; arrayIndex ++)
        {
          if( p_nodetrienodeCurrent->m_arp_nodetrienode1LowerLevel[arrayIndex])
          {
            p_nodeTrieIterator->addVisitedNode(
              TrieNodeArrayAndArrayIndex<member_type>(p_nodetrienodeCurrent, arrayIndex) );
            p_nodetrienodeCurrent = p_nodetrienodeCurrent->m_arp_nodetrienode1LowerLevel[arrayIndex];
            return p_nodetrienodeCurrent;
          }
        }
        return NULL;
      }
      
      NodeTrieNode<member_type> * GetNextInfoNodeAtHigherArrayIndex(
        NodeTrieIterator<member_type> & nodeTrieIterator,
        TrieNodeArrayAndArrayIndex<member_type> & trieNodeArrayAndArrayIndex) const
      {
        do
        {
          trieNodeArrayAndArrayIndex = nodeTrieIterator.visitedNodes.top();
          /** Go 1 level directing root. */
          nodeTrieIterator.visitedNodes.pop();

          NodeTrieNode<member_type> * p_nodetrienodeCurrent = 
            GetNextNodeAtHigherArrayIndex(
            trieNodeArrayAndArrayIndex, & nodeTrieIterator);
          if( p_nodetrienodeCurrent != NULL)
          {
            if( p_nodetrienodeCurrent->m_member != m_defaultValue )
            {
  //              nodeTrieIterator.SetInfoNode();
              return p_nodetrienodeCurrent;
            }
          }
        }
        while( ! nodeTrieIterator.visitedNodes.empty() );
        return NULL;
      }
      
      iterator GetNextInfoNode(//std::stack</*NodeTrieNode<member_type> * */ 
//        TrieNodeArrayAndArrayIndex<member_type> > & visitedNodes
        NodeTrieIterator<member_type> * p_nodeTrieIterator) const
      {
        while( ! p_nodeTrieIterator->visitedNodes.empty() )
        {
          TrieNodeArrayAndArrayIndex<member_type> trieNodeArrayAndArrayIndex = 
            p_nodeTrieIterator->visitedNodes.top();
          NodeTrieNode<member_type> * p_nodetrienodeCurrent = trieNodeArrayAndArrayIndex.GetPointer();
          
          /** Go to leaf direction. */
          NodeTrieNode<member_type> * traverseDirectingLeavesResult = 
            traverseDirectingLeaves(* p_nodeTrieIterator, p_nodetrienodeCurrent);
          if( traverseDirectingLeavesResult == NULL)
          {
            p_nodetrienodeCurrent = GetNextInfoNodeAtHigherArrayIndex(
              *p_nodeTrieIterator, trieNodeArrayAndArrayIndex);
            if(p_nodetrienodeCurrent) /** Next info node found. */
              return * p_nodeTrieIterator;
            /** Go to leaf direction. */
//            traverseDirectingLeavesResult = 
//              traverseDirectingLeaves(* p_nodeTrieIterator, p_nodetrienodeCurrent);
          }
          else /** Next info node found */
            return * p_nodeTrieIterator;
        }
        /** No info node found->return an interator representing "end()" */
        return NodeTrieIterator<member_type>(/*m_nodetrienodeRoot*/ *this, NULL, NULL);
      }
      
      unsigned long getNumberOfNodes() const
      {
          return m_dwNumberOfNodes;
      }

      /** @param wNumberOfNodes: # nodes per hierarchy level
       *   "unsigned" data type: same bit width as CPU
       *    arch->fast */
      void Create(unsigned numberOfNodesPerHierarchyLevel)
      {
          m_nodetrienodeRoot.Create(numberOfNodesPerHierarchyLevel, m_defaultValue);
          m_wNumberOfNodesPerHierarchyLevel = numberOfNodesPerHierarchyLevel;
          m_wNodeSizeInByte = sizeof (NodeTrieNode<member_type>)
            + sizeof (NodeTrieNode<member_type>*) * numberOfNodesPerHierarchyLevel + sizeof (void*);
      }

      unsigned Create(const fastestUnsignedDataType numberOfNodes, 
        member_type defaultValue)
      {
        m_dwNumberOfNodes = 0, 
        m_numInfoNodes = 0, 
        m_defaultValue = defaultValue;
        m_wNumberOfNodesPerHierarchyLevel = numberOfNodes;
        m_nodetrienodeRoot(numberOfNodes, defaultValue);
        m_wNodeSizeInByte = sizeof (NodeTrieNode<member_type>)
          + sizeof (NodeTrieNode<member_type>*) * m_wNumberOfNodesPerHierarchyLevel
          + sizeof (void*);
        return m_wNodeSizeInByte;
      }
      
      inline NodeTrieNode<member_type> * contains_inline(
        unsigned char *p_vBegin, size_type wBytesize, bool bFullMatch)
      {
//          std::stringstream strstream;
//          for(unsigned short wIndex = 0;wIndex < wBytesize;++wIndex){
//              strstream << p_vBegin[wIndex] << " ";
//          }
          bExists = false;
          if(m_nodetrienodeRoot.m_arp_nodetrienode1LowerLevel){
              m_p_nodetrienodeCurrent = &m_nodetrienodeRoot;
              for(m_wIndex = 0;m_wIndex < wBytesize;++m_wIndex){
                  byValue = p_vBegin[m_wIndex];
                  if(m_p_nodetrienodeCurrent->m_arp_nodetrienode1LowerLevel[byValue])
                      m_p_nodetrienodeCurrent = m_p_nodetrienodeCurrent->m_arp_nodetrienode1LowerLevel[byValue];

                  else{
                      break;
                  }
              }

              if(bFullMatch){
                  if(m_wIndex == wBytesize && m_p_nodetrienodeCurrent->m_member != m_defaultValue){
                      return m_p_nodetrienodeCurrent;
                  }
              }
              else
                  return m_p_nodetrienodeCurrent;

          }
          return //bExists ;
        NULL;
      }

      bool IsCreated() const
      {
        return m_nodetrienodeRoot.IsCreated();
      }
      
      inline bool IsTrieLeaf(NodeTrieNode<member_type> *p_nodetrienodeCurrent)
      {
          for(WORD byIndex = 0;byIndex < m_wNumberOfNodesPerHierarchyLevel;++byIndex)
              if(p_nodetrienodeCurrent->m_arp_nodetrienode1LowerLevel[byIndex])
                  return false;


          return true;
      }
      inline bool Delete_inline(unsigned char *p_vBegin, unsigned short  wBytesize)
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
            //    LOGN_NODETRIE("Trie::exists ar_p_byCurrent:" << ar_p_byCurrent
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
//                      DEBUGN_NODETRIE("address of of trie node 1 level higher:" <<
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
                DEBUGN_NODETRIE("set content for bytes at address " <<
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

      /** Deletes the trie nodes together with the dynamically/heap allocated 
       *   member data stored at the nodes.
       * 
       *  Uses a depth-first search: if a leaf is reached this node is deleted 
       *   and the depth-frist search is started again beginning from the root
       *   node.
       */
      void DeleteWithMember()
      {
        if (m_nodetrienodeRoot.m_arp_nodetrienode1LowerLevel)
        {
          //    char ch ;
          NodeTrieNode<member_type> * p_nodetrienodeCurrent = NULL;
          //Arrays of pointers.
          NodeTrieNode<member_type> ** ar_p_nodetrienodeCurrent;
          NodeTrieNode<member_type> ** ar_p_nodetrienode1LevelAbove = NULL;
          //    WORD wSize ;
          DEBUGN_NODETRIE("data structure: FreeMemory")

          //    DEBUGN_NODETRIE("root node array address: %x", & m_ar_nodetrienodeRoot )

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

            //	  DEBUGN_NODETRIE("starting from array at root node array at address %x",
            //		  m_nodetrienodeRoot.m_arp_nodetrienode1LowerLevel)

            //This loop deleted 1 element at the leaf.
            for (WORD wIndex = 0; wIndex < m_wNumberOfNodesPerHierarchyLevel; ++wIndex)
            {
              if ( //Array element not NULL <=> character at/ for position "wIndex" is
                //assigned.
                ar_p_nodetrienodeCurrent[wIndex] )
              {
                //m_simple_linked_list_byte.AddElement();
                p_nodetrienodeCurrent = ar_p_nodetrienodeCurrent[wIndex];

                //			if( wIndex == 0) //"If" here because outputting a '\0' ends the output.
                //				DEBUGN_NODETRIE("NodeTrie:array element at addr %x (content: %x ^= value: %u (' ') ) is assigned",
                //					ar_p_nodetrienodeCurrent + wIndex,
                //					ar_p_nodetrienodeCurrent[ wIndex ],
                //					wIndex)
                //			else
                //				DEBUGN_NODETRIE("NodeTrie:array element at addr %x (content: %x value: %u ('%c') ) is assigned",
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
                //DEBUGN_NODETRIE
                ////DEBUG_COUTN
                //  ( "entering child node at address %x", ar_p_byCurrent )

                wIndex = 65535; //MAXWORD ;
                //found the 1st child: go 1 level deeper.
                continue;
              }
              else // ar_p_nodetrienodeCurrent[wIndex] == NULL
              {
                if ( //Index for last array element.
                    wIndex == (m_wNumberOfNodesPerHierarchyLevel - 1) )
                {
                  //          DEBUG_COUTN( //"& address : " << & ar_p_byCurrent
                  //              "value at address " << ar_p_byCurrent
                  //              << ":" << *ar_p_byCurrent )
                  //If at least 2 levels (array should NOT be deleted if it points to
                  //the root node because the root node is created on stack) .
                  if (ar_p_nodetrienode1LevelAbove)
                  {
                    //no child node for current node -> delete current node
                    //				DEBUGN_NODETRIE
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
                    if (p_nodetrienodeCurrent->m_member != m_defaultValue)
                    {
                      delete p_nodetrienodeCurrent->m_member;
                      -- m_numInfoNodes;
                    }
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
                    * ar_p_nodetrienode1LevelAbove = NULL;
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
                    //            DEBUGN_NODETRIE
                    //            //DEBUG_COUTN
                    //              ("deleting root array at address" << m_ar_p_byRoot)
                    //            m_ar_p_byRoot = NULL ;
                    //            delete [] m_ar_p_byRoot ;
                    //            -- m_dwNumberOfNodes ;
                    DEBUGN_NODETRIE("We are at the root node.")
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
      }

      void DeleteWithMember(size_type & numNodes)
      {
        DeleteWithMember();
        numNodes = m_dwNumberOfNodes;
      }

      void FreeMemory()
      {
          if (m_nodetrienodeRoot.m_arp_nodetrienode1LowerLevel)
        {
          NodeTrieNode<member_type> * p_nodetrienodeCurrent = NULL;
          //Arrays of pointers.
          NodeTrieNode<member_type> ** ar_p_nodetrienodeCurrent;
          NodeTrieNode<member_type> ** ar_p_nodetrienode1LevelAbove = NULL;
          //    WORD wSize ;
          DEBUGN_NODETRIE("data structure: FreeMemory")

          //    DEBUGN_NODETRIE("root node array address: %x", & m_ar_nodetrienodeRoot )

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

              //	  DEBUGN_NODETRIE("starting from array at root node array at address %x",
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
                      //				DEBUGN_NODETRIE("NodeTrie:array element at addr %x (content: %x ^= value: %u (' ') ) is assigned",
                      //					ar_p_nodetrienodeCurrent + wIndex,
                      //					ar_p_nodetrienodeCurrent[ wIndex ],
                      //					wIndex
                      //					)
                      //			else
                      //				DEBUGN_NODETRIE("NodeTrie:array element at addr %x (content: %x value: %u ('%c') ) is assigned",
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
                      //DEBUGN_NODETRIE
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
                              //				DEBUGN_NODETRIE
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
                              //            DEBUGN_NODETRIE
                              //            //DEBUG_COUTN
                              //              ("deleting root array at address" << m_ar_p_byRoot)
                              //            m_ar_p_byRoot = NULL ;
                              //            delete [] m_ar_p_byRoot ;
                              //            -- m_dwNumberOfNodes ;
                              DEBUGN_NODETRIE("We are at the root node.")
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
//          assert( m_dwNumberOfNodes == 0);
      }

      NodeTrieNode<member_type> *CreateNodes(
        NodeTrieNode<member_type> * p_nodetrienodeCurrent, 
        unsigned char *p_vBegin, 
        unsigned short  wBytesize)
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
            m_wNumberOfNodesPerHierarchyLevel, m_defaultValue);
        //Allocation succeeded.
        if ( //ar_nodetrienodeCurrent
            //p_nodetrienode
            p_nodetrienodeNew)
        {
          //Important when deleting node _and_ member: only members with value <> 0 are deleted.
          //TODO: necessary?
//              p_nodetrienodeNew->m_member = 0;

          //LOGN_NODETRIE
          // DEBUGN_NODETRIE("# nodes:" << m_dwNumberOfNodes << " overall size="
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
//                DEBUGN_NODETRIE("created new node at address %x, array address:%x for value %u ('%c') and assigned it to parent's array element %x",
//                  p_nodetrienodeNew,
//                  p_nodetrienodeNew->m_arp_nodetrienode1LowerLevel,
//                  (WORD) byValue, byValue,
//                  & p_nodetrienodeCurrent->m_arp_nodetrienode1LowerLevel[ byValue]
//                  )
//              else
//                DEBUGN_NODETRIE("created new node at address %x, array address:%x for value %u and assigned it to parent's array element %x",
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
              ++ m_dwNumberOfNodes;
              //  #endif
        }
        else
        {
          LOGN_NODETRIE("NodeTrie::insert_inline(...)--allocating a node failed--"
              "return NULL")
          return //false ;
          NULL;
        }
      }
          return p_nodetrienodeCurrent;
      }

      NodeTrieNode<member_type> *insert_inline(unsigned char *p_vBegin, unsigned  wBytesize)
      {
//          std::ostringstream strstream;
//          for(unsigned short wIndex = 0;wIndex < wBytesize;++wIndex){
//              strstream << (WORD)(p_vBegin[wIndex]) << " ";
//          }
//          std::string stdstr = strstream.str();
          if(m_nodetrienodeRoot.m_arp_nodetrienode1LowerLevel){
              NodeTrieNode<member_type> *p_nodetrienodeCurrent = &m_nodetrienodeRoot;
              BYTE byValue;
              for(WORD wIndex = 0;wIndex < wBytesize;++wIndex){
                  byValue = p_vBegin[wIndex];
                  if(p_nodetrienodeCurrent->m_arp_nodetrienode1LowerLevel[byValue])
                      p_nodetrienodeCurrent = p_nodetrienodeCurrent->m_arp_nodetrienode1LowerLevel[byValue];

                  else{
                      return CreateNodes(p_nodetrienodeCurrent, p_vBegin + wIndex, wBytesize - wIndex);
                  }
              }

              return p_nodetrienodeCurrent;
          }
          else{
              throw NS_NodeTrie::RootNodeNotInitalizedException();
          }
      }

      bool IsCreated()
      {
        return m_nodetrienodeRoot.m_arp_nodetrienode1LowerLevel != NULL;
      }
      
      NodeTrieNode<member_type> *insert_inline(unsigned char *p_vBegin,
        size_type wBytesize, member_type member_value
        /*,member_type defaultValue = 0*/)
      {
          NodeTrieNode<member_type> *p = insert_inline(
          p_vBegin, wBytesize);
      if (p)
      {
        p->m_member = member_value;
        ++ m_numInfoNodes;
      }
      return p;
    }
    /** This function is for easy transition from/to a std::map */
    NodeTrieNode<member_type> * insert(std::string & str, member_type member_value)
    {
      return insert_inline(str.c_str(), str.length(), member_value);
    }
//    std::pair<const _Key, _Tp>
//    /** This function is for easy transition from/to a std::map */
//    NodeTrieNode<member_type> * insert(std::pair<std::string str, member_type member_value> )
//    {
//      return insert_inline(str.c_str(), str.length(), member_value);
//    }

    size_type size() { return m_dwNumberOfNodes; }
  };

//class NodeTrie

//#ifndef COMPILE_NODETRIE_WITH_LOGGING
//  #ifdef DEBUGN
//    #undef DEBUGN
//  #endif //#ifdef DEBUGN
//  #ifdef LOGN
//    #undef LOGN
//  #endif //#ifdef LOGN
//#endif

#endif //#ifndef NODETRIE_HPP
