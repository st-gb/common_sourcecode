/*
 * LogLevel.cpp
 *
 *  Created on: 14.10.2012
 *      Author: Stefan
 */

#include "Controller/Logger/LogLevel.hpp"

namespace LogLevel
{
  //static
  NodeTrie<BYTE> s_nodetrieLogLevelStringToNumber(255);
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

