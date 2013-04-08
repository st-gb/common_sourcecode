/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */
/*
 * generic_string_compare.hpp
 *
 *  Created on: Oct 30, 2010
 *      Author: Stefan
 */

#ifndef GENERIC_STRING_COMPARE_HPP_
#define GENERIC_STRING_COMPARE_HPP_

namespace CharacterString
{
  enum template_character_type_string_compare_ret_val
  {
    both_strings_equal = 0,
    strings_differ
  };

  //This function can be used to compare C-strings (_arrays_ of characters)
  //of different types, e.g. "char" and "wchar_t" or "XMLCh" and "char".
  template <typename  T,typename T2> inline int
    template_character_type_string_compare(
    const T * cp_character_type1stString,
    const T2 * cp_character_type2ndString
    )
    {
//      char * p_ch = XERCES_CPP_NAMESPACE::XMLString::transcode(cpc_xmlch) ;
//      int n = strcmp(p_ch, cpc_ch ) ;
//      XERCES_CPP_NAMESPACE::XMLString::release( & p_ch ) ;
//      int n ;
      while( //char not NULL / no string end
        * cp_character_type1stString && * cp_character_type2ndString )
      {
        if( * cp_character_type1stString != * cp_character_type2ndString )
          return //1 ;
            strings_differ ;
        //Advance 1 character
        ++ cp_character_type1stString ;
        ++ cp_character_type2ndString ;
      }
      //If character value == 0 <=> at the end of both strings.
      if( ! * cp_character_type1stString && ! * cp_character_type2ndString  )
        return //0 ;
          both_strings_equal ;
      return //1 ;
        strings_differ ;
    //  #else //#ifdef __linux__
    //    /If strings equal.
    //  return wcscmp(
    //    //Explicitly cast to "wchar_t *" to avoid Linux g++ warning.
    //    (wchar_t *) cpc_xmlch, cpc_wch ) ;
//    #else
//      return 1 ;
//    #endif //#ifdef __linux__
  } //inline int ansi_or_wchar_string_compare(...)
}

#endif /* GENERIC_STRING_COMPARE_HPP_ */
