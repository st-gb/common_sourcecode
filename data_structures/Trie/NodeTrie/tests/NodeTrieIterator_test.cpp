#include <iostream> //std::cout
#include <data_structures/Trie/NodeTrie/NodeTrie.hpp> //class NodeTrie

int main(void)
{
  NodeTrie<int> nt(256, -1);
  nt.insert_inline( (unsigned char *) "ab", 2, 4);
  nt.insert_inline( (unsigned char *) "a", 1, 3);
  nt.insert_inline( (unsigned char *) "ac", 2, 5);
  nt.insert_inline( (unsigned char *) "c", 1, 6);
  nt.insert_inline( (unsigned char *) "cd", 2, 7);
  nt.insert_inline( (unsigned char *) "z", 1, 8);
  NodeTrie<int>::iterator iter = nt.begin();
    
  bool iteratorTestFailed = false;
  int lastValue = 0;
  while( iter != nt.end() )
  {
    std::cout << "value at iterator:" << * iter << std::endl;
    if( *iter <= lastValue)
    {
      iteratorTestFailed = true;
      break;
    }
    lastValue = * iter;
    iter ++;
  }
  std::cout << "iterator test " << (iteratorTestFailed ? "failed" : "succeeded" ) << std::endl;
}
