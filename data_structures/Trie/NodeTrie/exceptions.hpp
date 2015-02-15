#pragma once //include guard

#include <string> //class std::string

//forward decl.
template<typename member_type> class NodeTrie;

namespace NS_NodeTrie
{
    class RootNodeNotInitalizedException
    {

    };

  class NotInContainerException
  {
    std::string m_stdstr;
//	NodeTrie * p_nt;
    void * m_p;
	public :
    NotInContainerException(const char * const ch
      //TODO , /*const NodeTrie & nt*/ void * p
      )
    {
      m_stdstr = ch;
      //p_nt(& nt);
      //m_p = p;
    }
    std::string GetErrorMessageA() const
    {
      return "\"" + m_stdstr + std::string("\" is not contained in NodeTrie")
        /* "at memory address ") + m_p*/ ;
    }
  };
}
