/*
 * LogLevel.hpp
 *
 *  Created on: 14.10.2012
 *      Author: Stefan
 */

#ifndef LOGLEVEL_HPP_
#define LOGLEVEL_HPP_

#include <data_structures/Trie/NodeTrie/NodeTrie.hpp> //class NodeTrie

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
  static NodeTrie<BYTE> s_nodetrieLogLevelStringToNumber;
//  static NodeTrie<BYTE> s_nodetrieLogLevelStringToNumber;(
//    ASCII_CODE_FOR_LOW_Z_PLUS1,
//    LogLevel::beyondLastLogMessageType);
  
  LogLevel()
  {
//    if( LogLevel::s_nodetrieLogLevelStringToNumber.size() == 0)
//      LogLevel::CreateLogLevelStringToNumberMapping();
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
