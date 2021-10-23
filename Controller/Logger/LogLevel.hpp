/** LogLevel.hpp
 *  Created on: 14.10.2012
 *  Author: Stefan Gebauer, M.Sc. Comp.Sc.*/

#ifndef LOGLEVEL_HPP_
#define LOGLEVEL_HPP_

#include <data_structures/Trie/NodeTrie/NodeTrie.hpp> //class NodeTrie
#include <string>///class std::string

  #define ASCII_CODE_FOR_LOW_Z_PLUS1 0x7B // 'z' + 1

/*namespace*/ class LogLevel
{
      
 public:
  /** Should be sorted so that the most messages get the lowest number:
   * e.g. level "info" outputs all messages of info and beyond info:
   * info, warning, error, ... */
  enum MessageType{
//    log_message_typeSUCCESS,
//    log_message_typeINFO,
//    log_message_typeWARNING,
//    log_message_typeERROR,
//    beyondLastLogMessageType
//  };
//  enum MessageType2{
    success,
    debug,
    info,
    warning,
    error,
    beyondLastLogMessageType
  };
  typedef BYTE logLevelTrieMemberType;
  typedef NodeTrie<logLevelTrieMemberType> logLevelTrieType;
  typedef NodeTrieIterator<logLevelTrieMemberType> nodeTrieIterType;
  static logLevelTrieType s_nodetrieLogLevelStringToNumber;
//  static NodeTrie<BYTE> s_nodetrieLogLevelStringToNumber;(
//    ASCII_CODE_FOR_LOW_Z_PLUS1,
//    LogLevel::beyondLastLogMessageType);
  
  LogLevel()
  {
//    if( LogLevel::s_nodetrieLogLevelStringToNumber.size() == 0)
//      LogLevel::CreateLogLevelStringToNumberMapping();
  }
  
  static std::string getLevelName(
    const logLevelTrieType::iterator::visitedNodesType & visitedNodes)
  {
    std::string lvlName;
    for(NodeTrieIterator<BYTE>::visitedNodesType::const_iterator iter2 =
      visitedNodes.begin(); iter2 != visitedNodes.end(); iter2 ++)
    {
      lvlName += (char) iter2->arrayIndex;
    }
    return lvlName;
  }
  
  static void getAllLogLevels(std::string & str)
  {
    for(logLevelTrieType::iterator iter = s_nodetrieLogLevelStringToNumber.
      begin(); iter != s_nodetrieLogLevelStringToNumber.end();
      /** calls GetNextInfoNode() */ iter ++ )
    {
      const logLevelTrieType::iterator::visitedNodesType & visitedNodes = iter.
        visitedNodes;
      const std::string lvlName = getLevelName(visitedNodes);
      str += lvlName;
      logLevelTrieType::iterator iter2 = iter;
      iter2++;
      if(iter2 != s_nodetrieLogLevelStringToNumber.end() )
        str += ";";
    }
  }
  #include "LogLevel_GetAsNumber.hpp"
};
//  extern //static
//    NodeTrie<BYTE> s_nodetrieLogLevelStringToNumber;

//  LogLevel();
//  virtual
//  ~LogLevel();
//};

#endif /* LOGLEVEL_HPP_ */
