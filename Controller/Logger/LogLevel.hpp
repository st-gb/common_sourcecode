/** LogLevel.hpp
 *  Created on: 14.10.2012
 * @author Stefan Gebauer(TU Berlin matriculation number 361095) */

///Include guard,see http://en.wikipedia.org/wiki/Include_guard :

/**Bln=BerLiN:http://www.acronymfinder.com/Berlin-(Bln).html
 * Prgm=PRaGMa
 * Incl=INCLude:http://www.abbreviations.com/abbreviation/include
 * Grd=GuaRD:http://www.abbreviations.com/abbreviation/guard */
#ifdef TU_Bln361095usePrgmInclGrd
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
  #pragma once
#endif
#if defined TU_Bln361095usePrgmInclGrd ||\
  /**Include guard supported by (nearly) all industry compilers:*/\
/**Bln=BerLiN:https://www.acronymfinder.com/Berlin-(Bln).html
 * cmn=CoMmoN:http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe:http://www.abbreviations.com/abbreviation/Source */\
 ! defined TU_Bln361095cmnSrc__Logger__LogLevel_hpp
   #define TU_Bln361095cmnSrc__Logger__LogLevel_hpp

///C(++) standard library header files:
 #include <string>///class std::string

///Stefan Gebauer's(TU Berlin matric. number 361095) ~"cmnSrc" repository files:
 #include <data_structures/Trie/NodeTrie/NodeTrie.hpp>///class NodeTrie
 ///TU_Bln361095LoggerNmSpcBgn, TU_Bln361095LoggerNmSpcEnd
 #include <Controller/Logger/Logger_ID_prefix.hpp>

  #define ASCII_CODE_FOR_LOW_Z_PLUS1 0x7B // 'z' + 1

TU_Bln361095LoggerNmSpcBgn

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

TU_Bln361095LoggerNmSpcEnd

#endif///Include guard
