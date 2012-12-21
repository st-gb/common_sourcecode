/*
 * LogLevel.hpp
 *
 *  Created on: 14.10.2012
 *      Author: Stefan
 */

#ifndef LOGLEVEL_HPP_
#define LOGLEVEL_HPP_

#include <data_structures/Trie/NodeTrie/NodeTrie.hpp> //class NodeTrie

namespace LogLevel
{
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
  extern //static
    NodeTrie<BYTE> s_nodetrieLogLevelStringToNumber;

//  LogLevel();
//  virtual
//  ~LogLevel();
  inline enum MessageType GetAsNumber(const std::string & c_r_std_strLogLevel)
  {
    //      if( c_r_std_strLogLevel == "info" )
    //        m_logLevel = LogLevel::log_message_typeINFO;
    //      else if( c_r_std_strLogLevel == "warning" )
    NodeTrieNode<BYTE> * p_ntn = s_nodetrieLogLevelStringToNumber.
      contains_inline( (BYTE *) c_r_std_strLogLevel.c_str(),
      c_r_std_strLogLevel.length(), true);
    if( p_ntn )
      return (MessageType) p_ntn->m_member;
    return warning;
  }
  void CreateLogLevelStringToNumberMapping();
};

#endif /* LOGLEVEL_HPP_ */
