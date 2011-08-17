#pragma once //Include guard

//namespace SimpleLinkedList
//{	
	template <typename NodeContentType>
	class Node
	{
public:
		Node * m_p_nodeNext;
		NodeContentType m_node_content;
		Node(const NodeContentType & c_r_node_content)
			: m_p_nodeNext(NULL),
			m_node_content(c_r_node_content)
		{
		}
	};
//};

template <typename NodeContentType>
class SimpleLinkedList
{
	//NodeContentType m_nodet_ype;
	//SimpleLinkedList::
		Node<NodeContentType> * m_p_node1st;
	//SimpleLinkedList::
		Node<NodeContentType> * m_p_nodeLast;
	public:
	SimpleLinkedList():
		m_p_node1st(NULL),
		m_p_nodeLast(NULL)
	 {}
	void DeleteAll()
	{
		//SimpleLinkedList::
			Node<NodeContentType> * p_nodeCurrent = m_p_node1st;
		//SimpleLinkedList::
			Node<NodeContentType> * p_nodeNext = NULL;
		while(p_nodeCurrent)
		{
			p_nodeNext = p_nodeCurrent->m_p_nodeNext;
			delete p_nodeCurrent;
			p_nodeCurrent = p_nodeNext;
		}
	}
	Node<NodeContentType> * GetFirst()
	{
		return m_p_node1st;
	}
	Node<NodeContentType> * GetNext(Node<NodeContentType> * p_nodeCurrent)
	{
		if( p_nodeCurrent)
			return p_nodeCurrent->m_p_nodeNext;
		else
			return NULL;
	}
    ~SimpleLinkedList()
    {
		DeleteAll();
	}
	void AddElement(const NodeContentType & c_r_node_content)
	{
	  if( m_p_nodeLast)
	  {
		m_p_nodeLast->m_p_nodeNext = new //SimpleLinkedList::
			Node<NodeContentType>(c_r_node_content);
		m_p_nodeLast = m_p_nodeLast->m_p_nodeNext;
      }
		else
		{
			m_p_node1st = new //SimpleLinkedList::
				Node<NodeContentType>(c_r_node_content);
			m_p_nodeLast = m_p_node1st;
	    }
	}
	//void DeleteLast()
	//{
	//  if( m_p_nodeLast)
	//  {
	//	p_nodeLast->m_p_nodeNext = new SimpleLinkedList::Node<NodeContentType>(c_r_node_content);
	//	p_nodeLast = p_nodeLast->m_p_nodeNext;
 //     }
	//}
};
