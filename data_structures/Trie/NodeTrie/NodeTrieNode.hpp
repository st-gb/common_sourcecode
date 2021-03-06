#pragma once

typedef unsigned char BYTE;
#ifndef NULL
  #define NULL 0
#endif //#ifndef NULL
#include <string.h> // memset(...)

/** Using a template is more universal than using a pointer to the data:
* e.g. a member function pointer (e.g. 8 bytes on 32 bit OS) does not
* have the same size as a void pointer (4 bytes on 32 bit OS). */
template <typename member_type>
class NodeTrieNode
{
//private:
public:
//  static member_type s_defaultValue;
	//typedef fastestUnsignedDataType size_type;
	member_type m_member;
  NodeTrieNode ** m_arp_nodetrienode1LowerLevel ;
  
	NodeTrieNode()
		: m_arp_nodetrienode1LowerLevel (NULL)
	{
	}

  /** Use "unsigned" data type for performance
   * @param defaultValue if a value is <> this value then it marks a string
   * end*/
	void Create(unsigned wNumberOfNodesPerHierarchyLevel, member_type defaultValue)
	{
		m_arp_nodetrienode1LowerLevel = new NodeTrieNode * [
		  wNumberOfNodesPerHierarchyLevel] ; 
    const unsigned pointerSize = sizeof(NodeTrieNode *);
		//Value will have "abitrary" value -> set to NULL to mark the end.
		//cites from: http://www.cplusplus.com/reference/clibrary/cstring/memset/
		memset( //Pointer to the block of memory to fill.
	//          ar_nodetrienodeCurrent,
			m_arp_nodetrienode1LowerLevel ,
			//Value to be set.
			0 ,
			//Number of bytes to be set to the value.
			wNumberOfNodesPerHierarchyLevel * pointerSize
			) ;
		m_member = defaultValue;
	}

  /** Use "unsigned" (same bit size as CPU architecture) data type for performance
   * @param defaultValue if a value is <> this value then it marks a string
   * end*/
  NodeTrieNode(unsigned wNumberOfNodesPerHierarchyLevel, member_type defaultValue)
    :
    m_arp_nodetrienode1LowerLevel(NULL)
//    m_pv(NULL)
  {
	  Create(wNumberOfNodesPerHierarchyLevel, defaultValue);
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

  bool IsCreated() const
  {
    return m_arp_nodetrienode1LowerLevel != NULL;
  }
  
  ~NodeTrieNode()
  {
    Delete();
	//if( m_pv)
	//	delete m_pv;
  }
  
//  //pointer to specific attributes
//  void * m_pv ;
};
