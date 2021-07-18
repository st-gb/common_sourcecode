#include <iostream> //std::cout
#include <data_structures/Trie/NodeTrie/NodeTrie.hpp> //class NodeTrie
#include <hardware/CPU/fastest_data_type.h>///fastestUnsignedDataType
//IDEA: also add to vector for every insertion into trie. Then when iterating
// through the trie add to another vector for every iterator (increment) step.
// And make equality comparison (vec1 == vec2) for vectors afterwards.
//#include <vector>

int main(void)
{
  NodeTrie<int> nt(256, -1);
  ///Insert elements whose numbers must be ascending when iterating over.
  nt.insert_inline( (unsigned char *) "ab", 2, 4);
  nt.insert_inline( (unsigned char *) "a", 1, 3);
  nt.insert_inline( (unsigned char *) "ac", 2, 5);
  nt.insert_inline( (unsigned char *) "c", 1, 6);
  nt.insert_inline( (unsigned char *) "cd", 2, 7);
  nt.insert_inline( (unsigned char *) "z", 1, 8);
    
  bool iteratorTestFailed = false;
  int lastValue = 2;
  fastestUnsignedDataType numIterIncrements = 0;
  for(NodeTrie<int>::iterator iter = nt.begin(); iter != nt.end(); iter ++,
    numIterIncrements ++)
  {
    std::cout << "value at iterator:" << * iter << std::endl;
    if( *iter != lastValue + 1)
    {
      iteratorTestFailed = true;
      break;
    }
    lastValue = * iter;
  }
  if(numIterIncrements != 6 || lastValue != 8)
    iteratorTestFailed = true;
  std::cout << "iterator test " << (iteratorTestFailed ? "failed" :
    "succeeded" ) << std::endl;
}
