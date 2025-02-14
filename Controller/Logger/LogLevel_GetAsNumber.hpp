/**@author Stefan Gebauer(TU Berlin matriculation number 361095)
 * Created on 8. Oktober 2014, 22:31(Berlin, Germany time zone)*/

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
 ! defined TU_Bln361095cmnSrc__Logger__LogLevel_GetAsNumber_hpp
   #define TU_Bln361095cmnSrc__Logger__LogLevel_GetAsNumber_hpp

  static inline enum MessageType GetAsNumber(
    const std::string & c_r_std_strLogLevel)
  {
    //      if( c_r_std_strLogLevel == "info" )
    //        m_logLevel = LogLevel::log_message_typeINFO;
    //      else if( c_r_std_strLogLevel == "warning" )
    NodeTrieNode<BYTE> * p_ntn = s_nodetrieLogLevelStringToNumber.
      contains_inline( (BYTE *) c_r_std_strLogLevel.c_str(),
      ///Cast to avoid MicroSoft Visual C "warning C4267"
      (NodeTrie<BYTE>::size_type) c_r_std_strLogLevel.length(), true);
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

#endif///include guard
