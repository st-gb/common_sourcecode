/*
 * AppendCurrentTimeToString.hpp
 *
 *  Created on: Nov 25, 2010
 *      Author: Stefan
 */

#ifndef APPENDCURRENTTIMETOSTRING_HPP_
#define APPENDCURRENTTIMETOSTRING_HPP_

//#include <string> //class std::string
#ifndef _MSC_VER
  //class MFC_Compatibility::CString
  #include <Controller/character_string/MFC_Compatibility/CString.hpp>
  using namespace MFC_Compatibility ;
#endif

void AppendCurrentTimeToString(
    CString & rstr
//    std::string & cr_stdstring
    ) ;

#endif /* APPENDCURRENTTIMETOSTRING_HPP_ */
