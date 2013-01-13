/*
 * LogLevel.cpp
 *
 *  Created on: 14.10.2012
 *      Author: Stefan
 */

#include "Controller/Logger/LogLevel.hpp"

#define ASCII_CODE_FOR_LOW_Z_PLUS1 0x7B // 'z' + 1

namespace LogLevel
{
  //static
  NodeTrie<BYTE> s_nodetrieLogLevelStringToNumber(ASCII_CODE_FOR_LOW_Z_PLUS1,
    LogLevel::beyondLastLogMessageType);
  /** Must be executed prior to calling "LogLevel::GetAsNumber()". */
  void CreateLogLevelStringToNumberMapping()
  {
    std::string str = "info";
  //  LogLevel::s_nodetrieLogLevelStringToNumber.Create(255);
    s_nodetrieLogLevelStringToNumber.insert_inline( (BYTE *) str.c_str(),
      str.length(), LogLevel::info);
    str = "debug";
    s_nodetrieLogLevelStringToNumber.insert_inline( (BYTE *) str.c_str(),
      str.length(), LogLevel::debug);
    str = "warning";
    s_nodetrieLogLevelStringToNumber.insert_inline( (BYTE *) str.c_str(),
      str.length(), LogLevel::warning);
  }
}
//
//LogLevel::LogLevel()
//{
//  // TODO Auto-generated constructor stub
//
//}
//
//LogLevel::~LogLevel()
//{
//  // TODO Auto-generated destructor stub
//}

