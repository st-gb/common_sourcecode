#pragma once

#include <OperatingSystem/multithread/nativeCriticalSectionType.hpp> //nativeCriticalSection_type

//for other ideas see http://stackoverflow.com/questions/26175588/how-to-implement-a-simple-event-queue

namespace curses
{
/*template <T>*/ class Node
{
public:
  typedef void (*FunctionPointer)();
private:
  FunctionPointer m_functionPointer;
  Node * m_next;
public:
  Node( FunctionPointer fp) : m_functionPointer(fp), m_next(NULL) { }
  Node * GetNext() const { return m_next; }
  void SetNext(Node * p_node) { m_next = p_node; }
  void Execute() { (*m_functionPointer)(); }
};

/*template <T>*/ class EventQueue
{
  Node/*<T>*/ * m_first;
  Node/*<T>*/ * m_last;
  nativeCriticalSection_type m_criticalSection;
  unsigned m_numberOfItems;
public:
  EventQueue() : m_first(NULL), m_last(NULL), m_numberOfItems(0) { }

  /*template <typename T>*/ void addEvent/*<T>*/ (//T t 
    Node::FunctionPointer fp );
  void Process();
};
}

