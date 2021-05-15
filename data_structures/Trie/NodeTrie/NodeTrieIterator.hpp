/** File: NodeTrieIterator.hpp
 * Author: Stefan Gebauer, M.Sc. Comp.Sc.
 * Created on 16. November 2017, 16:42   */

#ifndef NODETRIEITERATOR_HPP
#define NODETRIEITERATOR_HPP

#include "NodeTrieNode.hpp"
//from https://codereview.stackexchange.com/questions/74609/custom-iterator-for-a-linked-list-class
#include <iterator> /** Base class std::iterator */
//#include <stack>///class std::stack
#include <vector>///class std::vector

template  <typename member_type>
class TrieNodeArrayAndArrayIndex
{
public:
  NodeTrieNode<member_type> * p_NodeTrie;
  fastestUnsignedDataType arrayIndex;
  TrieNodeArrayAndArrayIndex(
    NodeTrieNode<member_type> * p_NodeTrie,
    fastestUnsignedDataType arrayIndex)
    : p_NodeTrie(p_NodeTrie),
      arrayIndex(arrayIndex)
  {
  }
  NodeTrieNode<member_type> * GetPointer() const
  {
    return p_NodeTrie->m_arp_nodetrienode1LowerLevel[arrayIndex];
  }
  member_type & GetMember() const
  {
    return p_NodeTrie->m_arp_nodetrienode1LowerLevel[arrayIndex]->m_member;
  }
  bool operator ==(const TrieNodeArrayAndArrayIndex & rhs) const
  {
    return p_NodeTrie == rhs.p_NodeTrie && arrayIndex == rhs.arrayIndex;
  }
};

template  <typename member_type>
class NodeTrieIterator
  : public std::iterator<std::forward_iterator_tag,NodeTrieNode<member_type>* >
{
  /** The current info trie node with information appended (m_member != default )*/
  NodeTrieNode<member_type> * itr;
  NodeTrieNode<member_type> m_nodetrienodeRoot;
  const NodeTrie<member_type> & m_nodeTrie;
  NodeTrieNode<member_type> * superordinateNodeTrie;

  public :
    typedef std::/*stack*/vector</*NodeTrieNode<member_type> * */
      TrieNodeArrayAndArrayIndex<member_type> > visitedNodesType;
    visitedNodesType visitedNodes;
    NodeTrieIterator(
      const NodeTrie<member_type> & nodeTrie,
//      NodeTrieNode<member_type> & nodetrienodeRoot, 
      NodeTrieNode<member_type> * superordinateNodeTrie,
      NodeTrieNode<member_type> * temp) 
      : itr(temp), 
//        m_nodetrienodeRoot(nodetrienodeRoot),
        m_nodeTrie(nodeTrie),
        superordinateNodeTrie(superordinateNodeTrie)
        {}
//    NodeTrieIterator (const NodeTrieIterator & myitr) : itr(myitr.itr) {}
    
    void addVisitedNode(/* NodeTrieNode<member_type> * p_nodetrienodeRoot*/ 
      TrieNodeArrayAndArrayIndex<member_type> trieNodeArrayAndArrayIndex)
    {
      visitedNodes./*push*/push_back(/*p_nodetrienodeRoot*/
        trieNodeArrayAndArrayIndex);
    }
    /** https://stackoverflow.com/questions/9386266/overloading-the-operator-to-increment-an-iterator */
    NodeTrieIterator<member_type> operator++(int) /** post-increment */
    {
      return m_nodeTrie.GetNextInfoNode(/*visitedNodes*/ this);
    }
    bool operator== (const NodeTrieIterator& rhs) 
    {
//      return itr == rhs.itr;
      return this->visitedNodes != rhs.visitedNodes;
    }
    bool operator!= (const NodeTrieIterator& rhs) 
    {
//      return itr != rhs.itr;
      return this->visitedNodes != rhs.visitedNodes;
//      return false;
    }
    /** Dereferencing operator, */
    member_type & operator*()
    {
//      if(stack)
//      return /*itr*/->m_member;
      const TrieNodeArrayAndArrayIndex<member_type> & trieNodeArrayAndArrayIndex
        = visitedNodes./*top()*/back();///last element
      ///Returns the information attached to an info node.
      return trieNodeArrayAndArrayIndex.GetMember();//p_NodeTrie->m_member;
    }
};

#endif /* NODETRIEITERATOR_HPP */
