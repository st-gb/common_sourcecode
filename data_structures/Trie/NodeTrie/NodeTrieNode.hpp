#pragma once

typedef unsigned char BYTE;
#ifndef NULL
  #define NULL 0
#endif //#ifndef NULL
#include <string.h> // memset(...)

template <typename member_type>
class NodeTrieNode
{
//private:
public:
  //Using a template is more universal than using a pointer to the data:
  // e.g. a member function pointer (e.g. 8 bytes on 32 bit OS) does not
  //have the same size as a void pointer (4 bytes on 32 bit OS).
	member_type m_member;
	NodeTrieNode()
		: m_arp_nodetrienode1LowerLevel (NULL)
	{
	}
	void Create(unsigned wNumberOfNodesPerHierarchyLevel)
	{
		m_arp_nodetrienode1LowerLevel = new NodeTrieNode * [
		  wNumberOfNodesPerHierarchyLevel] ;
		//Value will have "abitrary" value -> set to NULL to mark the end.
		//cites from: http://www.cplusplus.com/reference/clibrary/cstring/memset/
		memset( //Pointer to the block of memory to fill.
	//          ar_nodetrienodeCurrent,
			m_arp_nodetrienode1LowerLevel ,
			//Value to be set.
			0 ,
			//Number of bytes to be set to the value.
			wNumberOfNodesPerHierarchyLevel * sizeof(NodeTrieNode *)
			) ;
	}
  NodeTrieNode(unsigned short wNumberOfNodesPerHierarchyLevel)
    :
    m_arp_nodetrienode1LowerLevel(NULL)
//    m_pv(NULL)
  {
	  Create(wNumberOfNodesPerHierarchyLevel);
  }
  //void Set1LevelLowerToNULL()
  //{
  //}
  void Delete()
  {
	if( m_arp_nodetrienode1LowerLevel)
	{
		delete [] m_arp_nodetrienode1LowerLevel ;
		m_arp_nodetrienode1LowerLevel = NULL ;
    }
  }
  ~NodeTrieNode()
  {
	Delete();
	//if( m_pv)
	//	delete m_pv;
  }
  NodeTrieNode ** m_arp_nodetrienode1LowerLevel ;
//  //pointer to specific attributes
//  void * m_pv ;
};
