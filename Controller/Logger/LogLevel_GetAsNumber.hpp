/* 
 * File:   LogLevel_GetAsNumber.hpp
 * Author: mr.sys
 *
 * Created on 8. Oktober 2014, 22:31
 */

#ifndef LOGLEVEL_GETASNUMBER_HPP
#define	LOGLEVEL_GETASNUMBER_HPP

  static inline enum MessageType GetAsNumber(const std::string & c_r_std_strLogLevel)
  {
    //      if( c_r_std_strLogLevel == "info" )
    //        m_logLevel = LogLevel::log_message_typeINFO;
    //      else if( c_r_std_strLogLevel == "warning" )
    NodeTrieNode<BYTE> * p_ntn = s_nodetrieLogLevelStringToNumber.
      contains_inline( (BYTE *) c_r_std_strLogLevel.c_str(),
      c_r_std_strLogLevel.length(), true);
     if( p_ntn )
      return (MessageType) p_ntn->m_member;
//    std::exception ex;
//    ex.
    throw NS_NodeTrie::NotInContainerException(
      c_r_std_strLogLevel.c_str() /*, 
      & s_nodetrieLogLevelStringToNumber*/ );
//    return warning;
  }
  
  static void CreateLogLevelStringToNumberMapping();

#endif	/* LOGLEVEL_GETASNUMBER_HPP */

