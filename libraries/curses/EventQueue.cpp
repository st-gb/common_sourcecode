#include "EventQueue.hpp"

ncurses::EventQueue g_eventQueue;

namespace ncurses
{
/*template <typename T>*/ void EventQueue::addEvent(//T fp
  Node::FunctionPointer fp
  )
{
//  if( in_GUI_thread )
  m_criticalSection.Enter();
  if( m_last )
  {
    m_last->SetNext( new Node(fp) );
    m_last = m_last->GetNext();
  }
  else
  {
    m_last = new Node(fp);
    m_first = m_last;
  }
  m_criticalSection.Leave();
}

void EventQueue::Process()
{
//  if( in_GUI_thread )
  {/** Blocks here if called from a second call before "Leave" is called, */
    m_criticalSection.Enter();
    if( m_first )
    {
      m_first->Execute();
      if( m_first == m_last )
      {
        delete m_first;
        m_first = m_last = NULL;
      }
      else
      {
        Node * second = m_first->GetNext();
        delete m_first;
        m_first = second;
      }
    }
    m_criticalSection.Leave();
  }
}
}

