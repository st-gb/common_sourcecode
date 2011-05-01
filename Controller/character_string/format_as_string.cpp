/*
 * format_as_string.cpp
 *
 *  Created on: Aug 18, 2010
 *      Author: Stefan
 */

#include <preprocessor_macros/logging_preprocessor_macros.h> //for DEBUG etc.
#include <string> //for std::string
#include <windef.h> //for WORD, BYTE
#define MAX_BIT_INDEX_FOR_UL 31

std::string format_output_data(
  const BYTE ar_byData [] ,
  DWORD dwByteSize ,
  BYTE byCharactersPerColumn )
{
  std::string stdstrBytes ;
  std::ostringstream std_ostr_streamBytes ;
  for(WORD wIndex = 0 ; wIndex < dwByteSize ; ++ wIndex )
  {
    if( wIndex % byCharactersPerColumn == 0 )
//      stdstrBytes += "\n" ;
      std_ostr_streamBytes << "\n";
    if( ar_byData[wIndex] > 32 )
      //stdstrBytes += ar_byData[wIndex] ;
      std_ostr_streamBytes << ar_byData[wIndex];
    else
//      stdstrBytes += " " ;
      std_ostr_streamBytes <<
      //see http://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-3.4/classstd_1_1ios__base.html:
      std::ios_base::hex << (WORD) ar_byData[wIndex] << " ";
  }
  return //stdstrBytes ;
    std_ostr_streamBytes.str();
}

//Use an object class like std::string instead of "char *". Advantage:
//So there is no need to care about releasing memory.
//char * getBinaryRepresentation(char arch [],unsigned long ulValue//,long size
std::string getBinaryRepresentation(unsigned long ulValue//,long size
  )
{
//  char arch[65] ;
  std::string str;
  LOGN_VERBOSE("getBinaryRepresentation--begin");
  //char arch[
  //  //returns size in bytes.
  //  sizeof(unsigned long)
  //  //=size in BITS.
  //  * 8
  //  //for terminating NULL char.
  //  + 1 ] ;
  BYTE i = MAX_BIT_INDEX_FOR_UL ;
  for(; i !=
    //Value after value wrap when "0-1" .
    255 ; i --)
  {
    //DEBUG("getBinaryRepresentation--index: %u\n",(WORD) i);
    //arch[MAX_BIT_INDEX_FOR_UL-i] = (char) ( ((ulValue >> i )& 1) + '0' ) ;
    str+=(char) ( ((ulValue >> i )& 1) + '0' ) ;
    if(  i%8 == 0)
      str+=' ';
  }
  //arch[MAX_BIT_INDEX_FOR_UL+1] = '\0' ;
  //return arch ;

  //return std::string(arch) ;
  LOGN_VERBOSE("getBinaryRepresentation--end");
  return str;
}
